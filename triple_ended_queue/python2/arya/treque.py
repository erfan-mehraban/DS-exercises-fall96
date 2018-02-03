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


class Treque:
    def __init__(self):
        self.left_deque = Deque()
        self.right_deque = Deque()

    def __len__(self):
        return len(self.left_deque) + len(self.right_deque)

    def __str__(self):
        return str(self.left_deque) + ' | ' + str(self.right_deque)

    def is_empty(self):
        return len(self) == 0

    def add_right(self, item):
        self.right_deque.add_right(item)
        if len(self.left_deque) < len(self.right_deque):
            self.left_deque.add_right(self.right_deque.remove_left())
        return self

    def add_middle(self, item):
        if len(self.left_deque) - len(self.right_deque) >= 1:
            self.right_deque.add_left(self.left_deque.remove_right())
        self.left_deque.add_right(item)
        return self

    def add_left(self, item):
        self.left_deque.add_left(item)
        if len(self.left_deque) - len(self.right_deque) > 1:
            self.right_deque.add_left(self.left_deque.remove_right())
        return self

    def remove_right(self):
        if self.right_deque:
            val = self.right_deque.remove_right()
            if self and len(self.left_deque) - len(self.right_deque) > 1:
                self.right_deque.add_left(self.left_deque.remove_right())
            return val

        return self.left_deque.remove_right()

    def remove_middle(self):
        val = self.left_deque.remove_right()
        if self and len(self.left_deque) - len(self.right_deque) < 0:
            self.left_deque.add_right(self.right_deque.remove_left())
        return val

    def remove_left(self):
        if self.left_deque:
            val = self.left_deque.remove_left()
            if len(self.left_deque) - len(self.right_deque) < 0 and self:
                self.left_deque.add_right(self.right_deque.remove_left())
            return val
        return None


treque = Treque()
input_queue = raw_input()
if input_queue:
    for num in input_queue.split(' '):
        treque.add_right(num)

while True:
    input_command = raw_input().split(' ')

    if input_command[0] == 'end':
        break

    if input_command[0] == 'remove':
        if input_command[1] == 't':
            print treque.remove_right()
        elif input_command[1] == 'm':
            print treque.remove_middle()
        elif input_command[1] == 'h':
            print treque.remove_left()

    if input_command[0] == 'add':
        if input_command[1] == 't':
            treque.add_right(input_command[2])
        elif input_command[1] == 'm':
            treque.add_middle(input_command[2])
        elif input_command[1] == 'h':
            treque.add_left(input_command[2])
