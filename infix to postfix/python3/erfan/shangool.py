class Stack():
    def __init__(self, iter=[]):
        self.a = []
        self.size = 0
        for x in iter:
            self.append(x)

    def __getitem__(self, index):
        return self.a[index]

    def __setitem__(self, index, item):
        self.a[index] = item

    def __len__(self):
        return self.size

    def __str__(self):
        return str(self.a[0:self.size])

    def append(self, x):
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


i = list(input())
pr = {
    "*": 2, "/": 2,
    "+": 1, "-": 1,
    "(": 0, ")": 0
}

op = Stack()
for c in i:
    if c not in pr:
        print(c, end="")
    else:
        if c is "(":
            op.append(c)
        elif c is ")":
            while (op.peek() is not '('):
                print(op.pop(), end="")
            op.pop()
        else:
            if len(op) > 0:
                while pr[c] <= pr[op.peek()]:
                    print(op.pop(), end="")
                    if (len(op) == 0):
                        break
            op.append(c)

while len(op) > 0:
    print(op.pop(), end="")
