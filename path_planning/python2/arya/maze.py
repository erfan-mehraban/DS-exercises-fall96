
class Deque:
    def __init__(self):
        self.__capacity = 1
        self.__deque_size = 0
        self.__first_item_index = 0
        self.__items = [None] * self.__capacity

    def __len__(self):
        return self.__deque_size

    def __str__(self):
        string = ''
        for i in range(self.__deque_size):
            string += str(self[i]) + ' '
        return string

    def __getitem__(self, index):
        return self.__items[(index + self.__first_item_index) %
                            self.__capacity]

    def __setitem__(self, index, item):
        self.__items[(index + self.__first_item_index) %
                     self.__capacity] = item

    def _resize(self):
        if self.__deque_size + 1 <= self.__capacity and \
                self.__deque_size * 3 >= self.__capacity:
            return

        new_capacity = max(1, 2 * self.__deque_size)
        new_items = [None] * new_capacity

        for i in range(self.__deque_size):
            new_items[i] = self[i]
        self.__items = new_items
        self.__capacity = new_capacity
        self.__first_item_index = 0

    def is_empty(self):
        return self.__deque_size == 0

    def add(self, index, item):
        self._resize()

        if index < self.__deque_size / 2:
            if self.__first_item_index == 0:
                self.__first_item_index = self.__capacity - 1
            else:
                self.__first_item_index -= 1

            for i in range(index - 1):
                self[i] = self[i + 1]
        else:
            for i in range(self.__deque_size, index, -1):
                self[i] = self[i - 1]
        self[index] = item
        self.__deque_size += 1

        return self

    def add_right(self, item):
        return self.add(self.__deque_size, item)

    def add_left(self, item):
        return self.add(0, item)

    def remove(self, index):
        tmp = self[index]
        if index < self.__deque_size / 2:
            for i in range(index, 0, -1):
                self[i] = self[i - 1]
            self.__first_item_index = (
                self.__first_item_index + 1) % self.__capacity
        else:
            for i in range(index, self.__deque_size - 1):
                self[i] = self[i + 1]
        self.__deque_size -= 1
        self._resize()
        return tmp

    def remove_right(self):
        return self.remove(self.__deque_size - 1)

    def remove_left(self):
        return self.remove(0)


class ArrayStack:
    def __init__(self):
        self.__stack_size = 0
        self.__capacity = 1
        self.__items = [None] * self.__stack_size

    def __len__(self):
        return self.__stack_size

    def _resize(self):
        if self.__stack_size + 1 <= self.__capacity and \
                self.__stack_size * 3 >= self.__capacity:
            return

        new_capacity = max(1, 2 * self.__stack_size)
        new_items = [None] * new_capacity

        for i in range(self.__stack_size):
            new_items[i] = self.__items[i]
        self.__items = new_items
        self.__capacity = new_capacity

    def pop(self):
        if self.__stack_size == 0:
            return None

        tmp = self.__items[self.__stack_size - 1]
        self.__stack_size -= 1
        self._resize()
        return tmp

    def peek(self):
        return self.__items[self.__stack_size - 1]

    def push(self, value):
        self._resize()
        self.__items[self.__stack_size] = value
        self.__stack_size += 1


def dfs_pathfinding(maze, initial_point, target_point):
    marked = [[False for x in maze[0]] for y in maze]
    previous_point = [[None for x in maze[0]] for y in maze]
    path_found = False
    stack = ArrayStack()
    stack.push(initial_point)

    while stack:
        current_point = stack.pop()
        if current_point == target_point:
            path_found = True
            break
        marked[current_point[0]][current_point[1]] = True

        for y in range(1, -2, -1):
            for x in range(1, -2, -1):
                neighbor_point = (current_point[0] + y, current_point[1] + x)
                if 0 <= neighbor_point[0] < len(maze) and \
                        0 <= neighbor_point[1] < len(maze[0]):
                    if maze[neighbor_point[0]][neighbor_point[1]] == 0 and \
                            not marked[neighbor_point[0]][neighbor_point[1]]:
                        stack.push(neighbor_point)
                        previous_point[neighbor_point[0]
                                       ][neighbor_point[1]] = current_point
                        marked[neighbor_point[0]][neighbor_point[1]] = True

    if not path_found:
        return None

    path = ArrayStack()
    current_point = target_point
    while current_point is not None:
        path.push(current_point)
        current_point = previous_point[current_point[0]][current_point[1]]
    return path


def main():
    height, width = raw_input().split()
    height = int(height)
    width = int(width)
    maze = []

    for row_idx in range(height):
        row = raw_input()
        row_array = []
        for block in row:
            row_array.append(int(block))
        maze.append(row_array)

    way = dfs_pathfinding(maze, (0, 0), (height - 1, width - 1))
    if way is None:
        print "That's a dead end!"
    else:
        print len(way)
        while way:
            point = way.pop()
            print str(point[0] + 1) + " " + str(point[1] + 1)


if __name__ == "__main__":
    main()
