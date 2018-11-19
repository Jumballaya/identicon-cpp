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
    std::vector<int> hashMatrix;
    std::string toString();

    void save(std::string out);
    void generate();
  private:
    int width;
    int height;
    int padding;
    std::string color;

    void buildHashMatrix();
};

#endif
