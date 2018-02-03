#include <iostream>

#include "headers/avl_tree.h"
#include "headers/utils.h"

using namespace std;

int main() {
  AVLTree<double> tree;

  int inputCount;
  cin >> inputCount;

  double value;
  string command;
  for (int i = 0; i < inputCount; i++) {
    cin >> command >> value;

    const double *findResult = tree.find(value);
    if (command == "add") {
      if (findResult != nullptr && *findResult == value) {
        cout << "already in there" << endl;
      } else {
        cout << "added" << endl;
        tree.add(value);
      }
    } else if (command == "find") {
      if (findResult != nullptr) {
        printGheibiStyleDouble(*findResult);
        cout << endl;
      } else {
        cout << "not found" << endl;
      }
    } else if (command == "remove") {
      if (findResult != nullptr && *findResult == value) {
        cout << "removed" << endl;
        tree.remove(value);
      } else {
        cout << "does not exist" << endl;
      }
    } else {
      cout << "What The Heck?!" << endl;
      i--;
    }
  }

  return 0;
}
