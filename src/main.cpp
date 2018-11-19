/**
 * Identicon Maker
 */
#include <iostream>
#include "Identicon.h"

int main(int argc, char **argv) {

  if (argc < 2) {
    printf("Error: please enter output path.");
    return 1;
  }

  Identicon ident(argv);
  ident.save(argv[2]);

  return 0;
}
