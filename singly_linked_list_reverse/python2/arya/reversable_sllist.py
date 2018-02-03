#include <assert.h>
#include <iostream>

using namespace std;

template <class T> class Node {
public:
  Node() {}
  Node(const T &value);
  ~Node() {}

  const T &getValue() const { return value; }
  void setValue(const T &value) { this->value = value; }

  Node<T> *nextNode() { return next; }
  void setNextNode(Node<T> *node) { next = node; }

private:
  Node<T> *next;
  T value;
};

template <class T>
Node<T>::Node(const T &value) : value(value), next(nullptr) {}

template <class T> class SinglyLinkedList {
public:
  SinglyLinkedList();
  ~SinglyLinkedList() {}

  void add(int index, const T &value);
  T remove(int index);
  const T &get(int index);

protected:
  Node<T> *getNode(int index);

  int size;
  Node<T> *headNode, *tailNode;
};

template <class T> Node<T> *SinglyLinkedList<T>::getNode(int index) {
  if (index == size - 1) {
    return tailNode;
  }

  Node<T> *tmpNode = headNode;
  for (int i = 0; i < index; i++) {
    tmpNode = tmpNode->nextNode();
  }
  return tmpNode;
}

template <class T> void SinglyLinkedList<T>::add(int index, const T &value) {
  assert(index <= size && index >= 0);

  Node<T> *newNode = new Node<T>(value);
  size++;

  // Add to head
  if (index == 0) {
    newNode->setNextNode(headNode);
    headNode = newNode;
    if (size == 1) {
      tailNode = newNode;
    }
    return;
  }

  // Add to tail
  if (index == size) {
    tailNode->setNextNode(newNode);
    tailNode = newNode;
    if (size == 1) {
      headNode = newNode;
    }
    return;
  }

  // Other nodes
  Node<T> *previousNode = getNode(index - 1);
  newNode->setNextNode(previousNode->nextNode());
  previousNode->setNextNode(newNode);
}

template <class T> const T &SinglyLinkedList<T>::get(int index) {
  assert(index < size && index >= 0);

  // Tail node
  if (index == size - 1) {
    return tailNode->getValue();
  }

  return getNode(index)->getValue();
}

template <class T> T SinglyLinkedList<T>::remove(int index) {
  T removedValue;

  if (index == 0) {
    Node<T> *head = headNode;
    removedValue = head->getValue();
    head = headNode->nextNode();
    delete headNode;
  } else {
    Node<T> *previousNode = getNode(index - 1);
    Node<T> *removedNode = previousNode->nextNode();
    removedValue = removedNode->getValue();
    previousNode->setNextNode(previousNode->nextNode()->nextNode());
    if (index + 1 == size) {
      tailNode = previousNode;
    }
    delete removedNode;
  }

  size--;
  return removedValue;
}

template <class T>
SinglyLinkedList<T>::SinglyLinkedList()
    : headNode(nullptr), tailNode(nullptr), size(0) {}

template <class T> class ReversableStack : protected SinglyLinkedList<T> {
public:
  ReversableStack() : SinglyLinkedList<T>() {}
  ~ReversableStack() {}

  void addFirst(const T &value);
  void addLast(const T &value);
  void reverse(int first, int last);
  T removeLast();

  int getSize() { return SinglyLinkedList<T>::size; }
};

template <class T> void ReversableStack<T>::addFirst(const T &value) {
  SinglyLinkedList<T>::add(0, value);
}

template <class T> void ReversableStack<T>::addLast(const T &value) {
  SinglyLinkedList<T>::add(SinglyLinkedList<T>::size, value);
}

template <class T> void ReversableStack<T>::reverse(int first, int last) {
  if (first == last) {
    return;
  }

  Node<T> *firstNode = SinglyLinkedList<T>::getNode(first);
  Node<T> *previous, *current, *next;
  previous = next = nullptr;
  current = firstNode;

  for (int i = first; i <= last; i++) {
    next = current->nextNode();
    current->setNextNode(previous);
    previous = current;
    current = next;
  }

  if (last == SinglyLinkedList<T>::size - 1) {
    firstNode->setNextNode(nullptr);
    SinglyLinkedList<T>::tailNode = firstNode;
  } else {
    firstNode->setNextNode(current);
  }
  if (first == 0) {
    SinglyLinkedList<T>::headNode = previous;
  } else {
    SinglyLinkedList<T>::getNode(first - 1)->setNextNode(previous);
  }
}

template <class T> T ReversableStack<T>::removeLast() {
  return SinglyLinkedList<T>::remove(SinglyLinkedList<T>::size - 1);
}

int main() {
  ReversableStack<int> stack;

  int inputCount;
  cin >> inputCount;
  for (int i = 0; i < inputCount; i++) {
    string command;
    cin >> command;
    if (command == "removeLast") {
      if (stack.getSize() == 0) {
        cout << "empty" << endl;
      } else {
        cout << stack.removeLast() << endl;
      }
    } else if (command == "addLast") {
      int value;
      cin >> value;
      stack.addLast(value);
    } else if (command == "addFirst") {
      int value;
      cin >> value;
      stack.addFirst(value);
    } else if (command == "reverse") {
      int first, last;
      cin >> first >> last;
      stack.reverse(first - 1, last - 1);
    }
  }

  return 0;
}
