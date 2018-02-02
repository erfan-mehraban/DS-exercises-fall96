#ifndef UTILS_H
#define UTILS_H

#include <iostream>

void printGheibiStyleDouble(const double &val) {
  if ((int)val == val) {
    std::cout << val << ".0";
  } else {
    std::cout << val;
  }
}

#endif // UTILS_H
