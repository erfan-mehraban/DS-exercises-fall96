# from collections import deque

class deque:
    def __init__(self,list):
        self.c = len(list) 
        self.size = len(list)
        self.first = 0
        self.item = [None] * self.c
        for i in range(self.size):
        	self.item[i] = list[i]

    def __len__(self):
        return self.size

    def __str__(self):
        string = ''
        for i in range(self.size):
            string += str(self[i]) + ' '
        return string

    def __getitem__(self, index):
        return self.item[(index + self.first) %
                            self.c]

    def __setitem__(self, index, item):
        self.item[(index + self.first) %
                     self.c] = item

    def resize(self):
        if (self.size + 1 <= self.c and self.size * 3 >= self.c):
            return

        c = max(1, 2 * self.size)
        newItem = [None] * c

        for i in range(self.size):
            newItem[i] = self[i]
        self.item = newItem
        self.c = c
        self.first = 0

    def is_empty(self):
        return self.size == 0

    def add(self, index, item):
        self.resize()

        if (index < self.size / 2):
            if self.first == 0:
                self.first = self.c - 1
            else:
                self.first -= 1

            for i in range(index - 1):
                self[i] = self[i + 1]
        else:
            for i in range(self.size, index, -1):
                self[i] = self[i - 1]
        self[index] = item
        self.size += 1

        return self

    def append(self, item):
        return self.add(self.size, item)

    def appendleft(self, item):
        return self.add(0, item)

    def remove(self, index):
        tmp = self[index]
        if (index < self.size / 2):
            for i in range(index, 0, -1):
                self[i] = self[i - 1]
            self.first = (
                self.first + 1) % self.c
        else:
            for i in range(index, self.size - 1):
                self[i] = self[i + 1]
        self.size -= 1
        self.resize()
        return tmp

    def pop(self):
        return self.remove(self.size - 1)

    def popleft(self):
        return self.remove(0)


i = input().split()
first = deque(i[:(len(i)+1)//2])
second = deque(i[(len(i)+1)//2:])

def shiftLeft():
	if ( len(second) > len(first) ):
		first.append(second.popleft())

def shiftRight():
	if ( len(first) - len(second) > 1 ):
		second.appendleft(first.pop())
# print (first, second)
i=input().split()
while (i[0] != "end"):
	if (i[1] == "m"):
		if (i[0] == "remove"):
			print (first.pop())
			shiftLeft()
		elif (i[0] == "add"):
			if ( len(first) != len (second) ):
				second.appendleft(first.pop())
			first.append(i[2])

	elif (i[1] == "t"):
		if (i[0] == "remove"):
			if (len (second) != 0):
				print(second.pop())
				shiftRight()
			else:
				print (first.pop())
		elif (i[0] == "add"):
			second.append(i[2])
			shiftLeft()

	elif (i[1] == "h"):
		if (i[0] == "remove"):
			print(first.popleft())
			shiftLeft()
		elif (i[0] == "add"):
			first.appendleft(i[2])
			shiftRight()
	# print (first, second)
	i = input().split()