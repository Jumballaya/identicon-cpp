/**
 * Utils
 */
#include "util.h"

using namespace std;

// itoa converts int to string
string itoa(int i) {
  ostringstream oss;
  oss << i;
  return oss.str();
}

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
