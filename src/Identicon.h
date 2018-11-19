/**
 * Identicon.h
 */
#ifndef IDENTICON_H
#define IDENTICON_H

#include <Magick++.h>

class Identicon {
  public:
    std::string input;
    Identicon(char **argv);
    Magick::Image image;
    int hashMatrix[30];

    void save(std::string out);
    void generate();
  private:
    int length;
    int width;
    int padding;
    std::string color;

    void buildHashMatrix();
};

#endif
