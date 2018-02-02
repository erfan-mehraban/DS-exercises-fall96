#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
 public:
  Node(const T &value)
      : left(nullptr), right(nullptr), height(1), value(value) {}

  Node<T> *getLeft() { return left; }
  Node<T> *getRight() { return right; }
  const Node<T> &getLeft() const { return *left; }
  const Node<T> &getRight() const { return *right; }

  void setLeft(Node<T> *left) { this->left = left; }
  void setRight(Node<T> *right) { this->right = right; }

  int getHeight() const { return height; }
  void setHeight(int height) { this->height = height; }

  const T &getValue() const { return value; }
  void setValue(const T &value) { this->value = value; }

 private:
  Node<T> *left, *right;
  int height;
  T value;
};

#endif // NODE_H
