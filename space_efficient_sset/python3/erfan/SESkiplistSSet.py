from functools import total_ordering
import random

@total_ordering
class Element():

    def __init__(self, key, value):
        self.key = key
        self.value = value

    def __eq__(self, other):
        if isinstance(other, str):
            return self.key == other
        return self.key == other.key

    def __lt__(self, other):
        if isinstance(other, str):
            return self.key < other
        return self.key < other.key

class Deque():
    data = []
    def __init__(self, iterable=[]):
        self.start = 0
        self.length = 0
        for item in iterable:
            self.push(item)

    def __iter__(self):
        for i in range(self.size()):
            yield self[i]

    def __getitem__(self, key):
        return self.data[(key + self.start) % len(self.data)]

    def __setitem__(self, index, input_data):
        removed_data = self.data[(index + self.start) % len(self.data)]
        self.data[(index + self.start) % len(self.data)] = input_data
        return removed_data

    def __delitem__(self, index):
        self.remove(index)

    def __len__(self):
        return self.size()

    def size(self):
        return self.length

    def insert(self, index, item): 
        if index < self.size()/2:
            self.start = (self.start-1) % len(self.data)
            for k in range(index):
                self.data[(self.start+k)%len(self.data)] =\
                        self.data[(self.start+k+1)%len(self.data)]
        else:
            for k in range(self.size(), index, -1):
                self.data[(self.start+k)%len(self.data)] =\
                        self.data[(self.start+k-1)%len(self.data)]
        self.data[(self.start+index)%len(self.data)] = item
        self.length += 1


    def push(self, x):
        self.add(self.size(), x)

    def push_first(self, x):
        return self.add(0, x)

    def pop_first(self):
        return self.remove(0)

    def pop(self):
        return self.remove(self.size() - 1)

    def peek(self):
        return self[self.size() - 1]

    def add(self, i, x):
        # if self.length == len(self.data):
        #     self._resize()
        if i < self.length / 2:
            self.start = (self.start - 1) % len(self.data)
            for k in range(i):
                self.data[(self.start + k) % len(self.data)
                          ] = self.data[(self.start + k + 1) % len(self.data)]
        else:
            for k in range(self.length, i, -1):
                self.data[(self.start + k) % len(self.data)
                          ] = self.data[(self.start + k - 1) % len(self.data)]
        self.data[(self.start + i) % len(self.data)] = x
        self.length += 1

    def remove(self, i):
        removed_data = self.data[(self.start + i) % len(self.data)]
        if i < self.length / 2:
            for k in range(i, 0, -1):
                self.data[(self.start + k) % len(self.data)
                          ] = self.data[(self.start + k - 1) % len(self.data)]
            self.start = (self.start + 1) % len(self.data)
        else:
            for k in range(i, self.length - 1):
                self.data[(self.start + k) % len(self.data)
                          ] = self.data[(self.start + k + 1) % len(self.data)]
        self.length -= 1
        return removed_data


class SESkipSSet():

    block_size = 100

    class Node(Deque):
        """A node in a skip list"""
        previous = None

        def __init__(self, h, iterable=[]):
            self.data = [Element("",0)] * (SESkipSSet.block_size + 1)
            super().__init__(iterable)
            self.next = [None] * (h + 1)
            self.next_length = [0] * (h + 1)

        def height(self):
            return len(self.next) - 1

    def __init__(self ):
        self.max_height = 0
        self.block_count = 0
        self.size = 0 #count of all data
        self.sentinel = self.Node(32,[Element("",0)]*(self.block_size+1))
        self.sentinel.previous = self.sentinel

    def find_pre_node(self, index):
        current_node = self.sentinel
        current_height = self.max_height
        current_index = -1
        while current_height >= 0:
            while current_node.next[current_height] is not None and\
                        current_index + current_node.next_length[current_height] < index:
                current_index += current_node.next_length[current_height]
                # go right
                current_node = current_node.next[current_height]
            current_height -= 1  # go down
        return current_node


    def _add_node(self, index, new_node):
        current_node = self.sentinel
        new_node_height = new_node.height()
        current_height = self.max_height
        current_index = -1
        previous_node = self.sentinel
        while current_height >= 0:
            #go right
            while (current_node.next[current_height] is not None) and\
                    (current_index + current_node.next_length[current_height] < index):
                current_index += current_node.next_length[current_height]
                current_node = current_node.next[current_height]
            previous_node = current_node
            #update pointers
            current_node.next_length[current_height] += 1
            if current_height <= new_node_height:
                new_node.next[current_height] = current_node.next[current_height]
                current_node.next[current_height] = new_node
                new_node.next_length[current_height] = current_node.next_length[current_height] - (index - current_index)
                current_node.next_length[current_height] = index-current_index
            #go down
            current_height -= 1
        self.block_count += 1
        #update previous pointers
        new_node.previous = previous_node
        if new_node.next[0] is not None:
            new_node.next[0].previous = new_node
        else: # last node
            self.sentinel.previous = new_node

    def add_node(self, block_index, data_list=[]):
        new_node = self.Node(self.pick_height(), data_list)
        if new_node.height() > self.max_height:
            self.max_height = new_node.height()
        self._add_node(block_index, new_node)
        return new_node

    def remove_node(self, index):
        current_node = self.sentinel
        current_height = self.max_height
        current_index = -1
        while current_height >= 0:
            while current_node.next[current_height] is not None and\
                    current_index + current_node.next_length[current_height] < index:
                #go right
                current_index += current_node.next_length[current_height]
                current_node = current_node.next[current_height]
            #update lenth
            current_node.next_length[current_height] -= 1
            if current_index + current_node.next_length[current_height] + 1 == index and\
                                current_node.next[current_height] is not None:
                current_node.next_length[current_height] += current_node.next[current_height].next_length[current_height]
                current_node.next[current_height] = current_node.next[current_height].next[current_height]
                if current_node == self.sentinel and current_node.next[current_height] is None:
                    self.max_height -= 1
            #go down
            current_height -= 1
        self.block_count -= 1

    def pick_height(self):
        z = random.getrandbits(32)
        k = 0
        while z & 1:
            k += 1
            z = z // 2
        return k

    def get_location(self, item):
        ''' return node , index in node deque, and node index, exsitance '''
        current_node = self.sentinel
        current_height = self.max_height
        current_node_index = -1
        while current_height >= 0:
            while (current_node.next[current_height] is not None) and\
                    ( current_node.next[current_height].peek() < item):
                # go right
                current_node_index += current_node.next_length[current_height]
                current_node = current_node.next[current_height]
            current_height -= 1  # go down

        # item should be in last element of current node
        if current_node.next[0] is None:
            return current_node, current_node.size(), current_node_index, False
        # item is in next node
        else:
            if item < (current_node.next[0])[0]:
                # return current_node, current_node.size(), current_node_index, False
                return current_node.next[0], 0, current_node_index+1, False
            elif item == (current_node.next[0])[0]:
                return current_node.next[0], 0, current_node_index+1, True

        current_node = current_node.next[0]
        index_in_node = 0
        while index_in_node < current_node.size() and\
                item > current_node[index_in_node]:
                index_in_node += 1
        if item == current_node[index_in_node]:
            return current_node, index_in_node, current_node_index+1, True
        return current_node, index_in_node, current_node_index+1, False

    def _spread(self, start_node, start_node_index): #can be optimized
        current_node = self.find_pre_node(start_node_index+self.block_size).next[0]
        current_node_index = start_node_index+self.block_size
        current_node = self.add_node(current_node_index)
        while current_node is not start_node:
            while current_node.size() < self.block_size:
                current_node.push_first(current_node.previous.pop())
            current_node = current_node.previous

    def _gather(self, start_node):
        current_node = start_node
        for _ in range(self.block_size-1):
            while current_node.size() < self.block_size:
                current_node.push(current_node.next.pop_first())
            current_node = current_node.next[0]
        self.remove_node(current_node)


    def add(self, input_data):
        if input_data > self.sentinel.previous.peek():
            self.append(input_data)
            return True
        node, index_in_node, current_node_index, exist = self.get_location(input_data)
        if exist:
            return False
        current_index = 0
        current_node = node
        while current_index < self.block_size and\
                current_node is not None and\
                current_node.size() == self.block_size+1:
            current_node = current_node.next[0]
            current_index += 1
        if current_index == self.block_size:  # b blocks, each with b+1 elements
            self._spread(node, current_node_index)
            current_node = node
        if current_node is None: # ran off the end - add new node
            current_node = self.add_node(self.block_count)
        while current_node is not node: # work backwards, shifting elements as we go
            current_node.push_first(current_node.previous.pop())
            current_node = current_node.previous
        current_node.insert(index_in_node, input_data)
        self.size += 1
        return True

    def append(self, x):
        last = self.sentinel.previous
        if last is self.sentinel or last.size() == self.block_size+1:
            last = self.add_node(self.block_count)
        last.push(x)
        self.size += 1
        
    def find(self, key):
        node, index_in_node, _, exist = self.get_location(key)
        if not exist and index_in_node >= node.size():
            return False
        return node[index_in_node].value

    def remove(self, key):
        node, index_in_node, node_index, exist = self.get_location(key)
        if not exist:
            return False
        current_node = node
        full_node_counter = 0
        while full_node_counter < self.block_size and\
                current_node.next[0] is not None and\
                current_node.size() == self.block_size-1:
            current_node = current_node.next[0]
            full_node_counter += 1
        if full_node_counter == self.block_size: # b blocks, each with b-1 elements
            self._gather(node)
        node.remove(index_in_node)
        while node.size() < self.block_size-1 and node.next[0] is not None:
            node.push(node.next[0].pop_first())
            node = node.next[0]
            node_index += 1
        if node.size() == 0:
            self.remove_node(node_index)
        self.size -= 1
        return True

main_list = SESkipSSet()
for _ in range(int(input())):
    orders = input().split()
    if orders[0] == "add":
        element = Element(orders[1],orders[2])
        if main_list.add(element):
            print ("added")
        else:
            print("already in there")
    elif orders[0] == "find":
        val = main_list.find(orders[1])
        if val:
            print (val)
        else:
            print("not found")
    elif orders[0] == "remove":
        if main_list.remove(orders[1]):
            print ("removed")
        else:
            print("does not exist")