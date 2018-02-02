#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "../utils.h"

#include <type_traits>

template <typename T>
void AVLTree<T>::add(const T &value) {
  root = add(root, value);
}

template <typename T>
void AVLTree<T>::remove(const T &value) {
  root = remove(root, value);
}

template <typename T>
const T *AVLTree<T>::find(const T &value) const {
  Node<T> *successor = nullptr;
  Node<T> *currentNode = root;
  while (currentNode != nullptr) {
    if (value > currentNode->getValue()) {
      currentNode = currentNode->getRight();
    } else if (value < currentNode->getValue()) {
      successor = currentNode;
      currentNode = currentNode->getLeft();
    } else {
      return &(currentNode->getValue());
    }
  }

  if (successor != nullptr) {
    return &(successor->getValue());
  }

  return nullptr;
}

template <typename T>
Node<T> *AVLTree<T>::remove(Node<T> *localRoot, const T &value) {
  if (localRoot == nullptr) {
    return localRoot;
  } else if (value < localRoot->getValue()) {
    localRoot->setLeft(remove(localRoot->getLeft(), value));
  } else if (value > localRoot->getValue()) {
    localRoot->setRight(remove(localRoot->getRight(), value));
  } else {
    if (localRoot->getRight() == nullptr || localRoot->getLeft() == nullptr) {
      Node<T> *successor = localRoot->getLeft();
      if (successor == nullptr) {
        successor = localRoot->getRight();
      }

      if (successor == nullptr) {
        delete localRoot;
        localRoot = nullptr;
      } else {
        *localRoot = *successor;
        delete successor;
      }
    } else {
      Node<T> *minValueChild = findMinValueNode(localRoot->getRight());
      localRoot->setValue(minValueChild->getValue());
      localRoot->setRight(
          remove(localRoot->getRight(), minValueChild->getValue()));
    }
  }

  if (localRoot == nullptr) {
    return localRoot;
  }

  updateHeight(localRoot);

  localRoot = balance(localRoot);
  return localRoot;
}

template <typename T>
Node<T> *AVLTree<T>::add(Node<T> *localRoot, const T &value) {
  if (localRoot == nullptr) {
    localRoot = new Node<T>(value);
    return localRoot;
  }

  if (value > localRoot->getValue()) {
    localRoot->setRight(add(localRoot->getRight(), value));
  } else if (value < localRoot->getValue()) {
    localRoot->setLeft(add(localRoot->getLeft(), value));
  } else {
    return localRoot;
  }

  updateHeight(localRoot);

  localRoot = balance(localRoot);
  return localRoot;
}

template <typename T>
Node<T> *AVLTree<T>::balance(Node<T> *localRoot) {
  int balanceFactor = heightDiff(localRoot);
  if (balanceFactor > 1) {
    if (std::is_same<T, double>::value) {
      std::cout << "balancing ";
      printGheibiStyleDouble((double)localRoot->getValue());
      std::cout << std::endl;
    }

    if (heightDiff(localRoot->getLeft()) >= 0) {
      localRoot = rightRotate(localRoot);
    } else {
      localRoot->setLeft(leftRotate(localRoot->getLeft()));
      localRoot = rightRotate(localRoot);
    }
  } else if (balanceFactor < -1) {
    if (std::is_same<T, double>::value) {
      std::cout << "balancing ";
      printGheibiStyleDouble((double)localRoot->getValue());
      std::cout << std::endl;
    }

    if (heightDiff(localRoot->getRight()) > 0) {
      localRoot->setRight(leftRotate(localRoot->getRight()));
      localRoot = leftRotate(localRoot);
    } else {
      localRoot = leftRotate(localRoot);
    }
  }
  return localRoot;
}

template <typename T>
Node<T> *AVLTree<T>::leftRotate(Node<T> *localRoot) {
  Node<T> *newLocalRoot = localRoot->getRight();
  localRoot->setRight(newLocalRoot->getLeft());
  newLocalRoot->setLeft(localRoot);

  updateHeight(localRoot);
  updateHeight(newLocalRoot);

  return newLocalRoot;
}

template <typename T>
Node<T> *AVLTree<T>::rightRotate(Node<T> *localRoot) {
  Node<T> *newLocalRoot = localRoot->getLeft();
  localRoot->setLeft(newLocalRoot->getRight());
  newLocalRoot->setRight(localRoot);
  return newLocalRoot;
}

template <typename T>
Node<T> *AVLTree<T>::findMinValueNode(Node<T> *localRoot) {
  Node<T> *currentNode = localRoot;
  while (currentNode->getLeft() != nullptr) {
    currentNode = currentNode->getLeft();
  }
  return currentNode;
}

template <typename T>
int AVLTree<T>::height(Node<T> *node) {
  if (node == nullptr) {
    return 0;
  }
  return node->getHeight();
}

template <typename T>
int AVLTree<T>::heightDiff(Node<T> *node) {
  return height(node->getLeft()) - height(node->getRight());
}

template <typename T>
void AVLTree<T>::updateHeight(Node<T> *node) {
  node->setHeight(1 + std::max(height(node->getLeft()), height(node->getRight())));
}

template <typename T>
void AVLTree<T>::printTree() {
  printTree(root);
}

template <typename T>
void AVLTree<T>::printTree(Node<T> *root) {
  if (root != nullptr) {
    std::cout << root->getValue() << "(" << root->getHeight() << ") ";
    printTree(root->getLeft());
    printTree(root->getRight());
  }
}

#endif // AVL_TREE_HPP
