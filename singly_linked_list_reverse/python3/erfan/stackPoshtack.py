class Stack():
    def __init__(self, iter=[]):
        self.a = []
        self.size = 0
        for x in iter:
            self.push(x)

    def __getitem__(self, index):
        return self.a[index]

    def __setitem__(self, index, item):
        self.a[index] = item

    def __len__(self):
        return self.size

    def __repr__(self):
        return self[0:self.size]

    def push(self, x):
        if (self.size == len(self.a)):
            self.resize()
        self.a[self.size] = x
        self.size += 1

    def pop(self):
        temp = self.a[self.size - 1]
        self.size -= 1
        if (len(self.a) >= 3 * self.size):
            self.resize()
        return temp

    def peek(self):
        return self.a[self.size - 1]

    def resize(self):
        temp = [None] * max(1, 2 * self.size)
        temp[0:self.size] = self.a[0:self.size]
        self.a = temp


class SLList():

    class Node():
        def __init__(self, data):
            self.data = data
            self.next = None

        def __repr__(self):
            return str(self.data)

    def __init__(self, iterable=[]):
        self.size = 0
        self.head = None
        self.tail = None
        for item in iterable:
            self.push(item)

    def _add(self, data):
        new_node = self.Node(data)
        if self.size == 0:
            self.head = new_node
        else:
            self.tail.next = new_node
        self.tail = new_node
        self.size += 1
        return True

    def push_first(self, data):
        new_node = self.Node(data)
        new_node.next = self.head
        self.head = new_node
        if self.size == 0:
            self.tail = new_node
        self.size += 1
        return data

    def push(self, data):
        new_node = self.Node(data)
        if self.size == 0:
            self.head = new_node
        else:
            self.tail.next = new_node
        self.tail = new_node
        self.size += 1
        return True

    def get_node(self, index):
        current_node = self.head
        for _ in range(index):
            current_node = current_node.next
        return current_node

    def get(self, index):
        return self.get_node(index).data

    def set(self, index, data):
        change_node = self.get_node(index)
        removed_data, change_node.data = change_node.data, data
        return removed_data

    def add(self, index, data):
        if index == 0:
            self.push_first(data)
            return True
        current_node = self.head
        for _ in range(index - 1):
            current_node = current_node.next
        new_node = self.Node(data)
        new_node.next = current_node.next
        current_node.next = new_node
        self.size += 1
        return True

    def remove(self, i):
        if i == 0:
            return self.pop_first()
        if i < 0:
            return None
        current_node = self.head
        for _ in range(i - 1):
            current_node = current_node.next
        removed_node = current_node.next
        if i == self.size-1:
            self.tail = current_node
        current_node.next = current_node.next.next
        self.size -= 1
        return removed_node.data

    def pop_first(self):
        if self.size == 0:
            return None
        remode_data = self.head.data
        self.head = self.head.next
        self.size -= 1
        if self.size == 0:
            self.tail = None
        return remode_data

    def pop(self):
        return self.remove(self.size-1)

    def __str__(self):
        s = "["
        u = self.head
        while u is not None:
            s += "%r" % u.data
            u = u.next
            if u is not None:
                s += ","
        return s + "]"

    def __len__(self):
        return self.size

    def __repr__(self):
        result = "SL "
        current_node = self.head
        for _ in range(self.size):
            result += str(current_node.data.__repr__()) + " , "
            current_node = current_node.next
        return result[:-3]

    def reverse(self, start, end):
        current_node = self.head
        for _ in range(start-1):
            first = current_node
            current_node = current_node.next
        reverse_stack = Stack()
        for _ in range(end - start+1):
            reverse_stack.push(current_node)
            current_node = current_node.next
        if start > 1:
            reverse_stack.push(first)
        else:
            self.head = reverse_stack.peek()
        while reverse_stack.size > 1:
            reverse_stack.pop().next = reverse_stack[reverse_stack.size-2]
        last = reverse_stack.pop()
        last.next = current_node
        if end == self.size:
            self.tail = last

main_list = SLList()
for _ in range(int(input())):
    # print (main_list.__repr__())
    orders = input().split()
    if orders[0] == "removeLast":
        result = main_list.pop()
        if result is not None:
            print (result)
        else:
            print ("empty")
    if orders[0] == "addFirst":
        main_list.push_first(int(orders[1]))
    if orders[0] == "addLast":
        main_list.push(int(orders[1]))
    if orders[0] == "reverse":
        main_list.reverse(int(orders[1]), int(orders[2]))
