/**
 * Utils
 */

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <sstream>
#include <vector>

// Default identicon pattern
#define DEFAULT_IMAGE {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0}

// itoa converts int to string
std::string itoa(int i);

// hext2Int converts a string hex value to an int, e.g. "ff" -> 255
int htoi(std::string h);

// mirror mirrors a vector of ints by the given row width
std::vector<int> mirror(std::vector<int> left, int width);

// mirrorVector creates a vector twice the size of the input vector.
std::vector<int> mirrorVector(std::vector<int> left, int width);

#endif
