from collections import deque
from functools import total_ordering


class Node:
    data = None
    left = None
    right = None
    y = None
    
    def __init__(self, x):
        self.data = x
    def __getitem__(self, index):
        return self.data[index]
    def __repr__(self):
        return str(self.data)

class RangeTree:
    root = None

    def __init__(self, sorted_data):
        self.root = self.build(sorted_data)

    def build(self, sorted_data):
        if len(sorted_data) == 1:
            return sorted_data[0]
        middle_index = int( (len(sorted_data) + 1) / 2)
        current = Node(sorted_data[middle_index-1])
        current.left = self.build(sorted_data[:middle_index])
        current.right = self.build(sorted_data[middle_index:])
        current.y = self.build_y( sorted(sorted_data, key=lambda x: x[1]) )
        return current

    def build_y(self, sorted_data):
        if len(sorted_data) == 1:
            return sorted_data[0]
        middle_index = int( (len(sorted_data) + 1) / 2)
        current = Node(sorted_data[middle_index-1])
        current.left = self.build_y(sorted_data[:middle_index])
        current.right = self.build_y(sorted_data[middle_index:])
        return current

    def find(self, dl, ur):
        sep= self.find_seperate(dl[0],ur[0], self.root)
        # print ("sep is"+str(sep))
        if sep is None:
            return []
        elif isinstance(sep, tuple):
            if self.find_seperate_y(dl[1], ur[1], sep) == sep:
                return [sep]
            else:
                return []

        result = []
        result += self._find_gr(dl, ur, sep.right)
        result += self._find_lo(dl, ur, sep.left )
        return result

    def find_seperate(self, a, b, node):
        if a <= node[0] and node[0] <= b:
            return node
        if isinstance(node, tuple):
            return None
        if a > node[0]:
            return self.find_seperate(a, b, node.right)
        else:
            return self.find_seperate(a, b, node.left)

    def _find_gr(self, dl, ur, node):
        if isinstance(node, tuple):
            if node[0] <= ur[0] and dl[1] <= node[1] <= ur[1]:
                # print ("returning gr"+str(node))
                return [node]
            return []
        if node[0] < ur[0]:
            # print ("going right in gr")
            return self.findy(dl[1], ur[1], node.left)+(self._find_gr(dl, ur, node.right))
        else:
            # print ("going left in gr")
            return self._find_gr(dl, ur, node.left)

    def _find_lo(self, dl, ur, node):
        if isinstance(node, tuple):
            if dl[0] <= node[0] and dl[1] <= node[1] <= ur[1]:
                # print ("returning lo"+str(node))
                return [node]
            return []
        if dl[0] > node[0]:
            # print ("going right in lo")
            return self._find_lo(dl, ur, node.right)
        else:
            # print ("going left in lo")
            return self.findy(dl[1], ur[1], node.right)+(self._find_lo(dl, ur, node.left))

    def findy(self, a, b, node):
        if isinstance(node, tuple):
            if a <= node[1] <= b:
                # print ("it is good point for y"+str(node))
                return [node]
            return []
        else:
            result = []
            sep = self.find_seperate_y(a, b, node.y)
            if sep is None:
                return []
            elif isinstance(sep, tuple):
                return [sep]
            # print ("sep y is:"+str(sep))
            result += self._find_gr_y(b, sep.right)
            result += self._find_lo_y(a, sep.left)
            return result

    def find_seperate_y(self, a, b, node):
        if a <= node[1] and node[1] <= b:
            return node
        if isinstance(node, tuple):
            return None
        if a > node[1]:
            return self.find_seperate_y(a, b, node.right)
        else:
            return self.find_seperate_y(a, b, node.left)

    def _find_gr_y(self, b, node):
        if isinstance(node, tuple):
            if node[1] <= b:
                # print ("returning y gr"+str(node))
                return [node]
            else:
                return []
        if node[1] < b:
            # print ("going right in gr_y")
            return self.all_node(node.left) + self._find_gr_y(b, node.right)
        else:
            # print ("going left in gr_y")
            return self._find_gr_y(b, node.left)

    def _find_lo_y(self, a, node):
        if isinstance(node, tuple):
            if a <= node[1] :
                # print ("returning y lo"+str(node))
                return [node]
            else:
                return []
        if a > node[1]:
            # print ("going right in lo_y")
            return self._find_lo_y(a, node.right)
        else:
            # print ("going left in lo_y")
            return self.all_node(node.right) + self._find_lo_y(a, node.left)

    def all_node(self, node):
        if isinstance(node, tuple):
            return [node]
        return self.all_node(node.left) + self.all_node(node.right)

    def __str__(self):
        d =  deque([self.root])
        while len(d) > 0:
            u = d.popleft()
            if isinstance(u, Node):
                print (u)
                print (u.left,u.right)
                # print ("::"+str(u.y)+"::")
                d.append(u.left)
                d.append(u.right)
        return ""

input()
data = []
xs = input().split()
ys = input().split()
for index, x in enumerate(xs):
    data.append((float(x),float(ys[index])))
data = sorted(data, key=lambda x: x[0])
tree = RangeTree(data)
# print(tree)
c = int(input())
for _ in range(c):
    rec = input().split()
    points = tree.find( (float(rec[0]),float(rec[1])), (float(rec[2]),float(rec[3])))
    if len(points):
        points = sorted(points, key=lambda x: x[1])
        xs = ""
        ys = ""
        for item in points:
            xs += ('%f' % item[0]).rstrip('0').rstrip('.') + " "
            ys += ('%f' % item[1]).rstrip('0').rstrip('.') + " "
        print (xs)
        print (ys)
    else:
        print ("None")
