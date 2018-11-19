/**
 * Identicon builder
 */
#include <Magick++.h>
#include <iostream>
#include <sstream>
#include "Config.h"

#include "Identicon.h"
#include "md5.h"

#define DEFAULT_IMAGE {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0}

using namespace std;
using namespace Magick;

// hext2Int converts a string hex value to an int, e.g. "ff" -> 255
int hex2Int(string h) {
  int x;
  stringstream ss;
  ss << hex << h;
  ss >> x;
  return x;
}

// mirror mirrors a vector of ints by the given row width
// examples:
//    mirror({1, 1, 0}, 3) -> {0, 1, 1}
//    mirror({1, 1, 0, 0, 0, 1}, 3) -> {0, 1, 1, 1, 0, 0}
vector<int> mirror(vector<int> left, int width) {
  vector<int> right(15);

  // flip left into right
  int row = 0;
  int col = 0;
  for (int i = 0; (unsigned int)i < left.size(); i++) {
    int offset = row * width;

    // r[0] = r[width], r[1] = r[width - 1] ... etc
    // This mirrors the left row into the right row
    right[offset + col] = left[(offset + (width - col)) - 1];

    col++;
    if (col >= width) col = 0;
    if ((i + 1) % width == 0) row++;
  }

  return right;
}

// mirrorVector creates a vector twice the size of the input vector.
// example:
//    vector<int> left({ 1, 1, 0, 0, 0, 1 });
//                      |        |       |
//                        row 1    row 2
//
//    mirrorVector(left) = { 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 }
//                          |        |        |        |       |
//                             left     right    left    right
//                          |                 |                |
//                                 row 1            row 2
//
vector<int> mirrorVector(vector<int> left, int width) {
  vector<int> right = mirror(left, width);
  vector<int> full(left.size() * 2);

  int row = 0;
  for (int i = 0; i < 30; i += (width * 2)) {
    for (int j = 0; j < (width * 2); j++) {
      if (j >= width) {
        full[i + j] = right[(row * width) + (j - width)];
      } else {
        full[i + j] = left[(row * width) + j];
      }
    }
    row++;
  }

  return full;
}

// Identicon constructor
Identicon::Identicon(char **argv) {
  //Config cfg(argv);
  //this->cfg = cfg;

  //string dimensions;
  //dimensions += cfg.getWidth();
  //dimensions += "x";
  //dimensions += cfg.getHeight();

  //std::cout << dimensions << std::endl;

  //Image image(dimensions, "white");
  //this->width = cfg.getWidth();
  //this->height = cfg.getHeight();
  //this->padding = cfg.getPadding();
  //this->input = cfg.getInput();
  //this->hashMatrix = vector<int>(DEFAULT_IMAGE);

  //InitializeMagick(cfg.getDir().c_str());

  //this->image = image;
  //this->generate();
}

// Identicon::generate builds the hashMatrix and uses it to create the image
void Identicon::generate() {
  this->buildHashMatrix();
  int sLength = (this->width / 6.0);
  int sWidth = (this->height / 5.0);
  int width = 6;

  for (int i = 0; i < (int) this->hashMatrix.size(); i++) {
    int row = i / width;
    int col = (i + 1) % width;
    string color = this->hashMatrix[i] == 1 ? this->color : "white";

    // Starting points for the color block
    int iStart = col * sLength;
    int jStart = row * sWidth;

    for (int i = 0; i < sLength; i++) {
      for (int j = 0; j < sWidth; j++) {
        this->image.pixelColor(i + iStart, j + jStart, Color(color));
      }
    }

  }

}

void Identicon::save(string out) {
  this->image.write(out);
}

string Identicon::toString() {
  vector<int> v = this->hashMatrix;
  string s;
  for (int i = 0; (unsigned int)i < v.size(); i++) {
    s += v[i];
    s += " ";
    if ((i + 1) % 6 == 0) {
      s += "\n";
    }
  }

  return s;
}

void Identicon::buildHashMatrix() {
  string hashed = md5(this->input);
  vector<string> hexVector(15);
  vector<int> left(15);

  int count = 0;
  for (int i = 0; i < 30; i += 2) {
    string h;
    h += hashed.at(i);
    h += hashed.at(i + 1);
    int val = hex2Int(h);
    hexVector[count] = h;
    left[count] = val > 125 ? 1 : 0;
    count++;
  }

  string r = hexVector.front();
  string g = hexVector.at(hexVector.size() / 2);
  string b = hexVector.back();

  this->color = "#" + r + g + b;
  this->hashMatrix = mirrorVector(left, 3);
}
