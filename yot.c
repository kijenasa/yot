#include <git2/global.h>
#include <git2/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <git2.h>
#include <git2/clone.h>

#include "config.h"

const char *entry_path;

// MACROS

#define USAGE                                                                                                          \
   "Usage: %s [options] <package_name>\n"                                                                              \
   "-S    Install packages\n"                                                                                          \
   "-h    Display this help message\n"

// STRUCTS

typedef struct package package_t;

struct package {
   char *name;
   // package *dependencies; // TODO: this should probably be a graph
   int dependencies_count;
};

// PACKAGE MANAGMENT

static int clone_repo(const char *git_url) { // TODO: make it create a new dir under CLONE_DIR
   git_repository *repo = NULL;
   git_libgit2_init();

   int ret = git_clone(&repo, git_url, CLONE_DIR, NULL);

   git_libgit2_shutdown();
   return ret;
}

static int build_package(const char *pkgbuild_dir) {
   if(chdir(pkgbuild_dir))
      return system("makepkg -si");
   return -1;
}

// TODO: use cJSON and convert it to package struct
static package_t *get_package(const char *package_name) { return NULL; }

static void clean_up() {
   remove(CLONE_DIR);
   chdir(entry_path);
}

// ENTRY

int main(int argc, char *argv[]) {
   int opt;
   while((opt = getopt(argc, argv, "S:R:U:Q:h")) != -1) {
      switch(opt) {
      case 'S':
         // TODO
         clean_up();
         exit(EXIT_SUCCESS);
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
