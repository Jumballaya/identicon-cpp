/**
 * Identicon Maker
 */
#include <iostream>
#include "Identicon.h"
#include "Config.h"

int main(int argc, char **argv) {

  if (argc < 4) {
    printf("Usage: \n");
    printf("identicon <input> <output> <length> <width> <padding>\n");
    return 1;
  }

  Config cfg(argv);
  Identicon ident(&cfg);
  ident.save();

  return 0;
}
