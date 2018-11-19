/**
 * Identicon.h
 */
#ifndef IDENTICON_H
#define IDENTICON_H

#include <Magick++.h>
#include "Config.h"

class Identicon {
  public:
    Identicon(char** argv);

    Config           cfg;
    std::string       input;
    Magick::Image     image;
    std::vector<int>  hashMatrix;

    std::string toString();

    void save(std::string out);
    void generate();
  private:
    int         width;
    int         height;
    int         padding;
    std::string color;

    void buildHashMatrix();
};

#endif
