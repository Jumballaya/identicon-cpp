/**
 * Identicon builder
 */
#include <Magick++.h>
#include <iostream>
#include <sstream>

#include "Identicon.h"
#include "md5.h"

using namespace std;
using namespace Magick;


vector<string> string_split(const string& s) {
  vector<string> tokens;
  string token;
  for (unsigned int i = 0; i < s.size(); i += 2) {
    token = s.at(i) + s.at(i + 1);
    tokens.push_back(token);
  }
  return tokens;
}

Identicon::Identicon(char **argv) {
  Image image("1000x1000", "white");
  this->length = 1001;
  this->width = 1001;
  this->padding = 10;
  this->input = argv[1];

  auto init = initializer_list<int>({1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0});
  copy(init.begin(), init.end(), this->hashMatrix);

  InitializeMagick(*argv);

  this->image = image;
  this->generate();
}

void Identicon::generate() {
  int sLength = (this->length / 6.0);
  int sWidth = (this->width / 5.0);
  this->buildHashMatrix();

  for (int w = 0; w < this->width; w += sLength) {
    for (int l = 0; l < this->length; l += sWidth) {
      string white = "white";

      int col = (((double)l / this->length) * 6.0);
      int row = ((double)w / this->width) * 5.0;

      int index = (row * 6) + col;

      if (this->hashMatrix[index] == 1) {
        color = this->color;
      } else {
        color = white;
      }

      int iStart = col * sLength;
      int jStart = row * sWidth;

      for (int i = 0; i < sLength; i++) {
        for (int j = 0; j < sWidth; j++) {
          this->image.pixelColor(i + iStart, j + jStart, Color(color));
        }
      }

    }
  }
}

void Identicon::save(string out) {
  this->image.write(out);
}

void Identicon::buildHashMatrix() {
  string hashed = md5(this->input);
  vector<string> split = string_split(hashed);
  cout << split.size() << endl;
  int len = split.size();

  string r = split[0] + split[1];
  string g = split.at((len / 2) - 1) + split.at(len / 2);
  string b = split[len - 1] + split[len];

  printf("%s %s %s", r.c_str(), g.c_str(), b.c_str());
  this->color = "#ff0000";
  //this->color = split[0] + split[1] + split.at(split.size() / 2) + split[split.size() - 2] + split[split.size() - 1];
}
