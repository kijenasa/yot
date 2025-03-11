#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// MACROS

#define USAGE                                                                                                          \
   "Usage: %s [options] <package_name>\n"                                                                              \
   "-S    Install packages\n"                                                                                          \
   "-Q    Query packages\n"                                                                                            \
   "-h    Display this help message\n"

// STRUCTS

typedef struct package package;

struct package {
   char *name;
   package *dependencies;
   int dependencies_count;
};

// PACKAGE MANAGMENT

static char *clone_repo(const char *git_url) { return NULL; }

static int build_package(const char *pkgbuild) { return -1; }

static package *get_package(const char *package_name) { return NULL; }

// ENTRY

int main(int argc, char *argv[]) {
   int opt;
   while((opt = getopt(argc, argv, "S:R:U:Q:h")) != -1) {
      switch(opt) {
      case 'S':
         // TODO
         break;
      case 'R':
      case 'U':
         fprintf(stderr, "You probably meant to use pacman\n");
         break;
      case 'Q':
         printf("%s", get_package(optarg)->name);
         break;
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
