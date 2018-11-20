/**
 * Identicon builder
 */
#include <Magick++.h>
#include <iostream>

#include "Config.h"
#include "Identicon.h"
#include "util.h"
#include "md5.h"

using namespace std;
using namespace Magick;

// Identicon constructor
Identicon::Identicon(Config* cfg) {
  this->cfg = cfg;

  string dimensions;
  dimensions += itoa(cfg->getWidth());
  dimensions += "x";
  dimensions += itoa(cfg->getHeight());

  Image image(dimensions.c_str(), "white");
  this->width = cfg->getWidth();
  this->height = cfg->getHeight();
  this->padding = cfg->getPadding();
  this->input = cfg->getInput();
  this->hashMatrix = vector<int>(DEFAULT_IMAGE);

  InitializeMagick(cfg->getDir().c_str());

  this->image = image;
  this->generate();
}

// Identicon::generate builds the hashMatrix and uses it to create the image
void Identicon::generate() {
  this->buildHashMatrix();
  int sLength = (this->width / 6.0);
  int sWidth = (this->height / 5.0);
  int width = 6;

  for (int i = 0; i < (int) this->hashMatrix.size(); i++) {
    int row = i / width;
    int col = (i) % width;
    if (this->hashMatrix[i] == 1) {

      // Starting points for the color block
      int jStart = col * sLength;
      int kStart = row * sWidth;

      for (int j = 0; j < sLength; j++) {
        for (int k = 0; k < sWidth; k++) {
          this->image.pixelColor(j + jStart, k + kStart, Color(this->color));
        }
      }

    }

  }

}

// Identicon::save saves the image the output file
void Identicon::save() {
  this->image.write(this->cfg->getOutput());
}

// Identicon::toString converts the hash matrix to a formatted string
string Identicon::toString() {
  vector<int> v = this->hashMatrix;
  string s;
  for (int i = 0; (unsigned int)i < v.size(); i++) {
    s += itoa(v[i]);
    s += " ";
    if ((i + 1) % 6 == 0) {
      s += "\n";
    }
  }

  return s;
}

// Identicon::buildHashMatrix parses the input's md5 hash and creates the color
// of the image and the hash matrix.
void Identicon::buildHashMatrix() {
  string hashed = md5(this->input);
  vector<string> hexVector(15);
  vector<int> left(15);

  int count = 0;
  for (int i = 0; i < 30; i += 2) {
    string h;
    h += hashed.at(i);
    h += hashed.at(i + 1);
    int val = htoi(h);
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
