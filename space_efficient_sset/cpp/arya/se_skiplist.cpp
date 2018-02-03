#include <assert.h>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string>

#define MAX_HEIGHT 64

using namespace std;

int generateNewHeight() { return rand() % MAX_HEIGHT; }

template <class K, class V>
class Pair {
 public:
  Pair(K key, V value) : key(key), value(value) {}
  Pair() {}
  ~Pair() {}

  K getKey() const { return key; }
  V getValue() const { return value; }

  void setKey(const K &key) { this->key = key; }
  void setValue(const V &value) { this->value = value; }
  friend bool operator<(const Pair<K, V> &lhs, const Pair<K, V> &rhs) {
    return lhs.key < rhs.key;
  }
  friend bool operator>(const Pair<K, V> &lhs, const Pair<K, V> &rhs) {
    return lhs.key > rhs.key;
  }
  friend bool operator==(const Pair<K, V> &lhs, const Pair<K, V> &rhs) {
    return lhs.key == rhs.key;
  }
  friend bool operator!=(const Pair<K, V> &lhs, const Pair<K, V> &rhs) {
    return lhs.key != rhs.key;
  }
  friend bool operator>=(const Pair<K, V> &lhs, const Pair<K, V> &rhs) {
    return lhs.key >= rhs.key;
  }
  friend bool operator<=(const Pair<K, V> &lhs, const Pair<K, V> &rhs) {
    return lhs.key <= rhs.key;
  }

 private:
  K key;
  V value;
};

template <class T>
class BoundedDeque {
 public:
  BoundedDeque(int capacity);
  ~BoundedDeque();

  const T &get(int index) const;
  const T &getLast() const { return get(size - 1); }
  const T &getFirst() const { return get(0); }
  T set(int index, const T &value);

  void add(int index, const T &value);
  void addFirst(const T &value);
  void addLast(const T &value);

  T remove(int index);
  T removeFirst();
  T removeLast();

  int getSize() const { return size; }
  int getCapacity() const { return capacity; }

 private:
  T *array;
  int size, capacity, dequeStartIndex;
};

template <class T>
BoundedDeque<T>::BoundedDeque(int capacity)
    : capacity(capacity), dequeStartIndex(0), size(0) {
  array = new T[capacity];
}

template <class T>
BoundedDeque<T>::~BoundedDeque() {
  // delete[] array;
}

template <class T>
const T &BoundedDeque<T>::get(int index) const {
  assert(index >= 0);
  assert(index < size);
  return array[(dequeStartIndex + index) % capacity];
}

template <class T>
T BoundedDeque<T>::set(int index, const T &value) {
  T lastValue = get(index);
  array[(index + dequeStartIndex) % capacity] = value;
  return lastValue;
}

template <class T>
void BoundedDeque<T>::add(int index, const T &value) {
  assert(capacity >= size + 1);
  if (index < size / 2) {
    dequeStartIndex =
        (dequeStartIndex == 0) ? capacity - 1 : dequeStartIndex - 1;
    for (int i = 0; i < index; i++) {
      array[(i + dequeStartIndex) % capacity] =
          array[(i + 1 + dequeStartIndex) % capacity];
    }
  } else {
    for (int i = size; i > index; i--) {
      array[(i + dequeStartIndex) % capacity] =
          array[(i - 1 + dequeStartIndex) % capacity];
    }
  }
  array[(index + dequeStartIndex) % capacity] = value;
  size++;
}

template <class T>
void BoundedDeque<T>::addFirst(const T &value) {
  add(0, value);
}

template <class T>
void BoundedDeque<T>::addLast(const T &value) {
  add(size, value);
}

template <class T>
T BoundedDeque<T>::remove(int index) {
  assert(index < size);
  T removedValue = get(index);
  if (index < size / 2) {
    for (int i = index; i > 0; i--) {
      array[(i + dequeStartIndex) % capacity] =
          array[(i - 1 + dequeStartIndex) % capacity];
    }
    dequeStartIndex = (dequeStartIndex + 1) % capacity;
  } else {
    for (int i = index; i < size - 1; i++) {
      array[(i + dequeStartIndex) % capacity] =
          array[(i + 1 + dequeStartIndex) % capacity];
    }
  }
  size--;
  return removedValue;
}

template <class T>
T BoundedDeque<T>::removeFirst() {
  return remove(0);
}

template <class T>
T BoundedDeque<T>::removeLast() {
  return remove(size - 1);
}

template <class T>
class Node {
 public:
  Node(int height, int dequeSize);
  ~Node() {}

  BoundedDeque<T> &getData() { return data; }
  const BoundedDeque<T> &getData() const { return data; }

  Node *nextNode(int index = 0) { return next[index]; }
  Node *previousNode() { return previous; }
  const Node *nextNode(int index = 0) const { return next[index]; }
  const Node *previousNode() const { return previous; }

  void setNextNode(Node *node, int index = 0) { next[index] = node; }
  void setPreviousNode(Node *node) { previous = node; }

  int getHeight() const { return height; }

 private:
  int height;
  BoundedDeque<T> data;
  Node *previous;
  Node **next;
};

template <class T>
Node<T>::Node(int height, int dequeSize) : height(height), data(dequeSize) {
  assert(height <= MAX_HEIGHT);

  next = new Node *[height + 1];
  for (int i = 0; i < height + 1; i++) {
    next[i] = nullptr;
  }
  previous = nullptr;
}

template <class T>
class SpaceEfficientSkiplistSSet {
 public:
  SpaceEfficientSkiplistSSet(int maxHeight, int blockSize);
  ~SpaceEfficientSkiplistSSet() {}

  bool add(const T &value);
  bool remove(const T &value);
  const T *find(const T &value) const;

  void logVerbose();

 private:
  void gather(Node<T> *node);
  bool addToNode(const T &value, Node<T> *node);
  bool removeFromNode(const T &value, Node<T> *node);
  void removeNodeLinks(Node<T> *node);
  Node<T> *createNewNodeBefore(Node<T> *node, const T &initValue);
  const Node<T> *findPredecessorNode(const T &value) const;

  Node<T> *sentinel;
  const int maxHeight, blockSize;
  int height;
};

template <class T>
SpaceEfficientSkiplistSSet<T>::SpaceEfficientSkiplistSSet(int maxHeight,
                                                          int blockSize)
    : maxHeight(maxHeight), blockSize(blockSize), height(0) {
  sentinel = new Node<T>(MAX_HEIGHT, blockSize + 1);
  for (int i = MAX_HEIGHT; i >= 0; i--) {
    sentinel->setNextNode(sentinel, i);
  }
  sentinel->setPreviousNode(sentinel);
}

template <class T>
void SpaceEfficientSkiplistSSet<T>::removeNodeLinks(Node<T> *node) {
  Node<T> *searchNode = sentinel;
  for (int level = height; level >= 1; level--) {
    while (searchNode->nextNode(level) != sentinel &&
           searchNode->nextNode(level)->getData().getLast() <
               node->getData().getLast()) {
      searchNode = searchNode->nextNode(level);
    }
    if (searchNode->nextNode(level) == node) {
      searchNode->setNextNode(node->nextNode(level), level);
      if (searchNode == sentinel && searchNode->nextNode(level) == sentinel) {
        height--;
      }
    }
  }
}

template <class T>
void SpaceEfficientSkiplistSSet<T>::gather(Node<T> *node) {
  Node<T> *tmpNode = node;
  for (int b = 0; b < blockSize; b++) {
    while (tmpNode->getData().getSize() < blockSize) {
      tmpNode->getData().addLast(tmpNode->nextNode()->getData().removeFirst());
    }
    tmpNode = tmpNode->nextNode();
  }
  tmpNode->previousNode()->setNextNode(tmpNode->nextNode());
  tmpNode->nextNode()->setPreviousNode(tmpNode->previousNode());
  delete tmpNode;
}

template <class T>
bool SpaceEfficientSkiplistSSet<T>::removeFromNode(const T &value,
                                                   Node<T> *node) {
  int removeIndex = -1;
  for (int i = 0; i < node->getData().getSize(); i++) {
    if (node->getData().get(i) == value) {
      removeIndex = i;
      break;
    }
  }
  if (removeIndex == -1) {
    return false;
  }

  int block = 0;
  Node<T> *tmpNode = node;
  while (block < blockSize && tmpNode->nextNode() != sentinel &&
         tmpNode->getData().getSize() == blockSize - 1) {
    tmpNode = tmpNode->nextNode();
    block++;
  }

  // Gather
  if (block == blockSize) {
    removeNodeLinks(tmpNode->previousNode());
    gather(node);
  }

  if (tmpNode->getData().getSize() == 1) {
    removeNodeLinks(tmpNode);
  }
  node->getData().remove(removeIndex);

  tmpNode = node;
  while (tmpNode->getData().getSize() < blockSize - 1 &&
         tmpNode->nextNode() != sentinel) {
    tmpNode->getData().addLast(tmpNode->nextNode()->getData().removeFirst());
    tmpNode = tmpNode->nextNode();
  }

  if (tmpNode->getData().getSize() == 0) {
    tmpNode->previousNode()->setNextNode(tmpNode->nextNode());
    tmpNode->nextNode()->setPreviousNode(tmpNode->previousNode());
    delete tmpNode;
  }

  return true;
}

template <class T>
bool SpaceEfficientSkiplistSSet<T>::addToNode(const T &value, Node<T> *node) {
  int addIndex = node->getData().getSize();
  for (int i = 0; i < node->getData().getSize(); i++) {
    if (node->getData().get(i) == value) {
      return false;
    }
    if (node->getData().get(i) > value) {
      addIndex = i;
      break;
    }
  }

  Node<T> *validNode = node;
  int block = 0;
  for (; block < blockSize; block++) {
    if (blockSize + 1 > validNode->getData().getSize()) {
      break;
    }
    if (validNode->nextNode() != sentinel) {
      validNode = validNode->nextNode();
    } else {
      break;
    }
  }

  if (blockSize + 1 == validNode->getData().getSize()) {
    if (block == blockSize) {
      Node<T> *block = createNewNodeBefore(validNode->nextNode(),
                                           validNode->getData().removeLast());
      while (block != node) {
        while (block->getData().getSize() < blockSize) {
          block->getData().addFirst(
              block->previousNode()->getData().removeLast());
        }
        block = block->previousNode();
      }
    } else {
      createNewNodeBefore(sentinel, validNode->getData().removeLast());
    }
  }

  while (validNode != node) {
    validNode->getData().addFirst(
        validNode->previousNode()->getData().removeLast());
    validNode = validNode->previousNode();
  }
  node->getData().add(addIndex, value);

  return true;
}

template <class T>
Node<T> *SpaceEfficientSkiplistSSet<T>::createNewNodeBefore(
    Node<T> *node, const T &initValue) {
  Node<T> *newNode = new Node<T>(generateNewHeight(), blockSize + 1);
  for (int i = 0; i <= newNode->getHeight(); i++) {
    newNode->setNextNode(sentinel, i);
  }
  newNode->getData().addLast(initValue);

  // Update search path
  Node<T> *searchNode = sentinel;
  for (int level = height; level >= 0; level--) {
    while (searchNode->nextNode(level) != sentinel &&
           searchNode->nextNode(level)->getData().getFirst() <
               newNode->getData().getFirst()) {
      searchNode = searchNode->nextNode(level);
    }
    if (level <= newNode->getHeight()) {
      searchNode->setNextNode(newNode, level);
    }
  }
  for (int level = height + 1; level <= newNode->getHeight(); level++) {
    sentinel->setNextNode(newNode, level);
    height++;
  }

  newNode->setNextNode(node);
  newNode->setPreviousNode(node->previousNode());
  node->previousNode()->setNextNode(newNode);
  node->setPreviousNode(newNode);
  return newNode;
}

template <class T>
bool SpaceEfficientSkiplistSSet<T>::add(const T &value) {
  Node<T> *node = sentinel;
  for (int level = height; level >= 0; level--) {
    while (node->nextNode(level) != sentinel &&
           node->nextNode(level)->getData().getSize() > blockSize - 1 &&
           node->nextNode(level)->getData().getLast() < value) {
      node = node->nextNode(level);
    }
  }

  if (node->nextNode() == sentinel) {
    createNewNodeBefore(sentinel, value);
    return true;
  } else {
    return addToNode(value, node->nextNode());
  }
}

template <class T>
bool SpaceEfficientSkiplistSSet<T>::remove(const T &value) {
  Node<T> *node = sentinel;
  for (int level = height; level >= 0; level--) {
    while (node->nextNode(level) != sentinel &&
           node->nextNode(level)->getData().getLast() < value) {
      node = node->nextNode(level);
    }
  }
  if (node->nextNode() == sentinel) {
    return false;
  }
  return removeFromNode(value, node->nextNode());
}

template <class T>
const Node<T> *SpaceEfficientSkiplistSSet<T>::findPredecessorNode(
    const T &value) const {
  Node<T> *node = sentinel;
  for (int level = height; level >= 0; level--) {
    while (node->nextNode(level) != sentinel &&
           node->nextNode(level)->getData().getLast() < value) {
      node = node->nextNode(level);
    }
  }
  return node;
}

template <class T>
const T *SpaceEfficientSkiplistSSet<T>::find(const T &value) const {
  const Node<T> *node = findPredecessorNode(value)->nextNode();
  for (int i = 0; i < node->getData().getSize(); i++) {
    if (node->getData().get(i) >= value) {
      return &(node->getData().get(i));
    }
  }
  return nullptr;
}

template <class T>
void SpaceEfficientSkiplistSSet<T>::logVerbose() {
  Node<T> *node = sentinel;
  cout << "[VERBOSE] " << height << " / ";
  while (node->nextNode() != sentinel) {
    BoundedDeque<T> deque = node->nextNode()->getData();
    for (int i = 0; i < deque.getSize(); i++) {
      cout << deque.get(i).getKey() << " ";
    }
    cout << "- ";
    node = node->nextNode();
  }
  cout << endl;
}

int main() {
  // srand(time(NULL));
  SpaceEfficientSkiplistSSet<Pair<string, double> > sset(MAX_HEIGHT, 100);

  int inputCount = 0;
  cin >> inputCount;
  for (int i = 0; i < inputCount; i++) {
    string command, key;
    cin >> command >> key;
    if (command == "add") {
      double value;
      cin >> value;
      Pair<string, double> pair(key, value);
      if (sset.add(pair)) {
        cout << "added" << endl;
      } else {
        cout << "already in there" << endl;
      }
    } else if (command == "remove") {
      if (sset.remove(Pair<string, double>(key, 0))) {
        cout << "removed" << endl;
      } else {
        cout << "does not exist" << endl;
      }
    } else if (command == "find") {
      const Pair<string, double> *val = sset.find(Pair<string, double>(key, 0));
      if (val == nullptr) {
        cout << "not found" << endl;
      } else {
        if (val->getValue() == (int)val->getValue()) {
          cout << fixed << setprecision(1) << val->getValue() << endl;
        } else {
          cout << std::defaultfloat << val->getValue() << endl;
        }
      }
    }
    // sset.logVerbose();
  }
  return 0;
}
