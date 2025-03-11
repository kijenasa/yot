#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <git2.h>
#include <git2/clone.h>

#include "config.h"

const char entry_path[256];

/* MACROS */

#define USAGE                                                                                                          \
   "Usage: %s [options] <package_name>\n"                                                                              \
   "-S    Install packages\n"                                                                                          \
   "-h    Display this help message\n"

/* PACKAGE MANAGMENT */

// Caller must free
static char *get_package_dir(const char *package_name) {
   char *buf = malloc(256);
   snprintf(buf, 256, CLONE_DIR, package_name);

   return buf;
}

// Caller must free
static char *get_package_url(const char *package_name) {
   char *buf = malloc(256);
   snprintf(buf, 256, PACKAGE_URL, package_name);

   return buf;
}

static int clone_repo(const char *git_url, const char *path) {
   git_repository *repo = NULL;
   git_libgit2_init();

   int ret = git_clone(&repo, git_url, path, NULL);

   git_libgit2_shutdown();
   return ret;
}

static int build_package(const char *pkgbuild_dir) {
   if(chdir(pkgbuild_dir) == 0)
      return system("makepkg -si");
   return -1;
}

static int install_package(const char *package_name) {
   char *package_url = get_package_url(package_name);
   char *package_dir = get_package_dir(package_name);

   printf("Cloning %s from %s\n", package_name, package_url);
   if(clone_repo(package_url, package_dir) == 0) {
      printf("Running 'makepkg -si'\n");

      free(package_url);
      free(package_dir);
      return build_package(package_dir);
   }

   free(package_url);
   free(package_dir);
   return -1;
}

int main(int argc, char *argv[]) {
   int opt;
   while((opt = getopt(argc, argv, "S:R:U:Q:h")) != -1) {
      switch(opt) {
      case 'S':
         exit(install_package(optarg));
      case 'R':
      case 'U':
      case 'Q':
         fprintf(stderr, "You probably meant to use pacman\n");
         exit(EXIT_FAILURE);
      case 'h':
         printf(USAGE, argv[0]);
         exit(EXIT_SUCCESS);
      case '?':
         fprintf(stderr, USAGE, argv[0]);
         exit(EXIT_FAILURE);
      default:
         fprintf(stderr, USAGE, argv[0]);
         exit(EXIT_FAILURE);
      }
   }

   return EXIT_SUCCESS;
}
