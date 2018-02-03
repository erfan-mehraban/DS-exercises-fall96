#include <assert.h>
#include <cstring>
#include <iostream>

using namespace std;

template <class T> class Deque {
public:
  Deque(int capacity = 1);
  ~Deque();

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
  void resize();

  T *array;
  int size, capacity, dequeStartIndex;
};

template <class T>
Deque<T>::Deque(int capacity)
    : capacity(capacity), dequeStartIndex(0), size(0) {
  array = new T[capacity];
}

template <class T> Deque<T>::~Deque() {}

template <class T> const T &Deque<T>::get(int index) const {
  assert(index >= 0);
  assert(index < size);
  return array[(dequeStartIndex + index) % capacity];
}

template <class T> T Deque<T>::set(int index, const T &value) {
  T lastValue = get(index);
  array[(index + dequeStartIndex) % capacity] = value;
  return lastValue;
}

template <class T> void Deque<T>::add(int index, const T &value) {
  resize();

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

template <class T> void Deque<T>::addFirst(const T &value) { add(0, value); }

template <class T> void Deque<T>::addLast(const T &value) { add(size, value); }

template <class T> T Deque<T>::remove(int index) {
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

  resize();

  return removedValue;
}

template <class T> T Deque<T>::removeFirst() { return remove(0); }

template <class T> T Deque<T>::removeLast() { return remove(size - 1); }

template <class T> void Deque<T>::resize() {
  if (size + 1 <= capacity && size * 3 >= capacity) {
    return;
  }

  int newCapacity = max(1, 2 * size);
  T *newArray = new T[newCapacity];
  for (int i = 0; i < size; i++) {
    newArray[i] = get(i);
  }
  // delete array;
  array = newArray;
  capacity = newCapacity;
  dequeStartIndex = 0;
}

struct Point {
  Point(int x = -1, int y = -1) : x(x), y(y) {}
  int x, y;
};

bool operator==(const Point &lhs, const Point &rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}
bool operator!=(const Point &lhs, const Point &rhs) { return !(lhs == rhs); }

Deque<Point> pathfindingDFS(bool **maze, int height, int width,
                            Point initialPoint, Point targetPoint) {
  // Visited blocks
  bool **marked = new bool *[height];
  for (int y = 0; y < height; y++) {
    marked[y] = new bool[width];
    memset(marked[y], 0, sizeof(bool) * width);
  }

  Point **previous = new Point *[height];
  for (int y = 0; y < height; y++) {
    previous[y] = new Point[width];
  }

  Deque<Point> traverseQueue;
  traverseQueue.addLast(initialPoint);
  marked[initialPoint.y][initialPoint.x] = true;
  bool pathFoundFlag = false;

  while (traverseQueue.getSize() > 0) {
    Point currentPoint = traverseQueue.removeLast();
    if (currentPoint == targetPoint) {
      pathFoundFlag = true;
      break;
    }

    for (int y = 1; y >= -1; --y) {
      for (int x = 1; x >= -1; --x) {
        Point neighborPoint(currentPoint.x + x, currentPoint.y + y);
        if (neighborPoint.x >= 0 && neighborPoint.x < width &&
            neighborPoint.y >= 0 && neighborPoint.y < height) {
          if (!marked[neighborPoint.y][neighborPoint.x] &&
              maze[neighborPoint.y][neighborPoint.x]) {
            marked[neighborPoint.y][neighborPoint.x] = true;
            traverseQueue.addFirst(neighborPoint);
            previous[neighborPoint.y][neighborPoint.x] = currentPoint;
          }
        }
      }
    }
  }

  Deque<Point> path;
  if (!pathFoundFlag) {
    return path;
  }

  Point currentPoint = targetPoint;
  while (currentPoint != Point(-1, -1)) {
    path.addFirst(currentPoint);
    currentPoint = previous[currentPoint.y][currentPoint.x];
  }
  return path;
}

int main() {
  int height, width;
  cin >> height >> width;

  bool **maze = new bool *[height];
  char mazeBlock = '0';
  for (int y = 0; y < height; y++) {
    maze[y] = new bool[width];
    for (int x = 0; x < width; x++) {
      cin >> mazeBlock;
      maze[y][x] = (mazeBlock == '0') ? true : false;
    }
  }

  Deque<Point> path = pathfindingDFS(maze, height, width, Point(0, 0),
                                     Point(width - 1, height - 1));
  if (path.getSize() == 0) {
    cout << "That\'s a dead end!" << endl;
  } else {
    cout << path.getSize() << endl;
    for (int i = 0; i < path.getSize(); i++) {
      cout << path.get(i).y + 1 << " " << path.get(i).x + 1 << endl;
    }
  }

  return 0;
}
