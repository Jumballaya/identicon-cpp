/**
 * Config
 */
#include <iostream>
#include <sstream>
#include "Config.h"

// itoa converts int to string
std::string itoa(int i) {
  std::ostringstream oss;
  oss << i;
  return oss.str();
}

// Constructor
Config::Config(char **argv) {
  this
    ->setDir(argv[0])
    ->setInput(argv[1])
    ->setOutput(argv[2])
    ->setHeight(atoi(argv[3]))
    ->setWidth(atoi(argv[4]))
    ->setPadding(atoi(argv[5]));
}

Config* Config::setOutput(std::string o) {
  this->output = o;
  return this;
};

Config* Config::setDir(std::string d) {
  this->dir = d;
  return this;
};

Config* Config::setWidth(int w) {
  this->width = w;
  return this;
};

Config* Config::setHeight(int h) {
  this->height = h;
  return this;
};

Config* Config::setInput(std::string i) {
  this->input = i;
  return this;
};

Config* Config::setPadding(int p) {
  this->padding = p;
  return this;
};

std::string Config::toString() {
  std::string out = "";

  // Input
  out += "Input: ";
  out += this->input;
  out += "\n";

  // Output
  out += "Output: ";
  out += this->output;
  out += "\n";

  // Dir
  out += "Directory: ";
  out += this->dir;
  out += "\n";

  // Width
  out += "Width: ";
  out += itoa(this->width);
  out += "\n";

  // Height
  out += "Height: ";
  out += itoa(this->height);
  out += "\n";

  // Padding
  out += "Padding: ";
  out += itoa(this->padding);
  out += "\n";

  return out;
}
