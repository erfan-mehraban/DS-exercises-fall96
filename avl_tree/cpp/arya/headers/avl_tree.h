#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "node.h"

#include <cmath>

template <typename T>
class AVLTree {
 public:
  AVLTree() : root(nullptr) {}

  void add(const T &value);
  void remove(const T &value);
  const T *find(const T &value) const;

  void printTree();

 private:
  Node<T> *remove(Node<T> *localRoot, const T &value);
  Node<T> *add(Node<T> *localRoot, const T &value);
  Node<T> *balance(Node<T> *localRoot);

  Node<T> *leftRotate(Node<T> *localRoot);
  Node<T> *rightRotate(Node<T> *localRoot);

  Node<T> *findMinValueNode(Node<T> *localRoot);

  int height(Node<T> *node);
  int heightDiff(Node<T> *node);
  void updateHeight(Node<T> *node);

  void printTree(Node<T> *root);

  Node<T> *root;
};

// include implementation
#include "impl/avl_tree.hpp"

#endif // AVL_TREE_H
