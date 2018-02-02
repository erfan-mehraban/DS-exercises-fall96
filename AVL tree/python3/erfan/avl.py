from functools import total_ordering
from collections import deque

@total_ordering
class ext_node():
    parent = None
    height = 0
    right = None
    left = None
    def __init__(self, par):
        self.parent = par

    def __eq__(self, other):
        if type(other) == type(None):
            return True
        return False

    def __ne__(self, other):
        return not self.__eq__(other)

    def __gt__(self, other):
        return False

    def __repr__(self):
        return "ext"

@total_ordering
class Node():
    value = None
    parent = None
    height = 1
    def __init__(self, val):
        self.value = val
        self.left = ext_node(self)
        self.right = ext_node(self)
    
    def update_height(self):
        self.height = max(self.right.height, self.left.height) + 1
        return self.height

    def balance_factor(self):
        return self.left.height - self.right.height

    def __eq__(self, other):
        if type(other) == Node:
            return other.value == self.value
        else:
            return other == self.value
    
    def __gt__(self, other):
        if type(other) == Node:
            # return other.value < self.value
            return float(other.value) < float(self.value)
        elif type(other) == ext_node:
            return True
        else:
            # return other < self.value
            return float(other) < float(self.value)

    def __repr__(self):
        return str(self.value)

class Avl():

    def __init__(self):
        self.root = ext_node(None)

    def __str__(self):
        p = deque()
        p.append(self.root)
        while len(p) > 0:
            c = p.popleft()
            print(" "+c.__repr__()+":"+c.parent.__repr__()+" ", end="")
            if c.left != None:
                p.append(c.left)
            if c.right!= None:
                p.append(c.right)
        return (" END")

    def find(self, val, current = None):
        if current is None:
            current = self.root
        suc = None
        while current != None:
            if current == val:
                return current
            elif current < val:
                current = current.right
            elif current > val:
                suc = current
                current = current.left
        return suc

    def remove(self, val):
        current = self.find(val)
        if current == None or current != val:
            return False
        isRoot = False
        if current == self.root:
            isRoot = True
        left_child = False
        if current < current.parent:
            left_child = True
        if current.left == None: # no left for current
            if current.right == None: # current is a leaf
                # if current == self.root:
                #     self.root = self.root.parent
                #     self.root.left = ext_node(self.root)
                #     self.root.right = ext_node(self.root)
                current = current.parent
                if left_child:
                    del current.left
                    current.left = ext_node(current)
                else:
                    del current.right
                    current.right = ext_node(current)
            else: # current has only right
                current = current.parent
                if left_child:
                    current.left = current.left.right
                    current.left.parent = current
                    current = current.left
                else:
                    current.right = current.right.right
                    current.right.parent = current
                    current = current.right
        elif current.right == None: # current has only left
            current = current.parent
            if left_child:
                current.left = current.left.left
                current.left.parent = current
                current = current.left
            else:
                current.right = current.right.left
                current.right.parent = current
                current = current.right
        else: # current has 2 child : replace with suc
            suc = self.find(val,current.right)
            suc_parent = suc.parent
            #correct parent of removed node
            if left_child:
                current.parent.left = suc
            else:
                current.parent.right = suc
            suc.parent = current.parent
            if current is self.root:
                self.root = suc #if removed node  is root, change tree root to suc
            #correct childs
            current.left.parent = suc
            suc.left = current.left
            if current.right != suc:
                current.right.parent = suc
                suc.right = current.right
                suc_parent.left = ext_node(suc_parent)
            #put current on original postion
            del current
            current = suc
        
        print ("removed")
        self.balance(current)
        if isRoot:
            self.root = current 
        return True

    def add(self, val):
        current = self.root
        left_child = False
        while current != None:
            if current == val:
                return False
            elif current < val:
                current = current.right
                left_child = False
            elif current > val:
                current = current.left
                left_child = True
        if current is self.root: #current is root
            self.root = Node(val)
            self.root.parent = current
            self.root.parent.right = self.root
            # self.root.parent.left = self.root
            print ("added")
        else:
            if left_child:
                par = current.parent
                par.left = Node(val)
                par.left.parent = par
                current = par.left
            else:
                par = current.parent
                par.right = Node(val)
                par.right.parent = par
                current = par.right
            print ("added")
            self.balance(current)
        return True

    def balance(self, current):
        while(current != None):
            current.update_height()
            b = current.balance_factor()
            if b > 1: #left
                print ("balancing "+ current.__repr__() )
                if current.left.balance_factor() < 1 : #left right
                    self.left_rotation(current.left)
                # also for left left
                self.right_rotation(current)

            elif b < -1: # right
                print ("balancing "+ current.__repr__() )
                if current.right.balance_factor() > 1 : # right left
                    self.right_rotation(current.right)
                # also for right right
                self.left_rotation(current)

            current = current.parent

    def right_rotation(self, lroot):
        pivot = lroot.left
        lroot.left = pivot.right
        lroot.left.parent = lroot
        pivot.right = lroot
        par = lroot.parent
        lroot.parent = pivot
        pivot.parent = par
        '''
        if par != None: # its not root of tree
            if lroot > par: # so lroot is right child
                par.right = pivot
            else: # so lroot is left child
                par.left = pivot
        else: # change tree root because root has been rotated
            self.root = pivot
        '''
        if lroot > par: # so lroot is right child
            par.right = pivot
        else: # so lroot is left child
            par.left = pivot
        if par == None: # change tree root because root has been rotated
            self.root = pivot

        lroot.update_height()
        pivot.update_height()

    def left_rotation(self, lroot): # same as right_rotation
        pivot = lroot.right
        lroot.right = pivot.left
        lroot.right.parent = lroot
        pivot.left = lroot
        par = lroot.parent
        lroot.parent = pivot
        pivot.parent = par
        '''
        if par != None: # its not root of tree
            if lroot > par: # so lroot is right child
                par.right = pivot
            else: # so lroot is left child
                par.left = pivot
        else: # change tree root because root has been rotated
            self.root = pivot
        '''
        if lroot > par: # so lroot is right child
            par.right = pivot
        else: # so lroot is left child
            par.left = pivot
        if par == None: # change tree root because root has been rotated
            self.root = pivot
        
        lroot.update_height()
        pivot.update_height()

'''
t = Avl()
t.add(1)
t.add(2)
t.add(3)
t.add(4)
t.add(5)
t.add(6)
t.add(7)
t.add(8)
t.add(9)
t.add(10)
t.add(11)
t.add(12)
t.add(13)
t.add(14)
t.remove(1)
t.remove(2)
t.remove(3)
t.remove(4)
t.remove(5)
t.remove(6)
t.remove(7)
t.remove(8)
t.remove(9)
t.remove(10)
t.remove(11)
t.remove(12)
t.remove(13)
t.remove(14)
t.remove(15)
'''
'''
t = Avl()
t.add(3)
t.add(2)
t.add(1)
t.add(0)

print (t)
t.remove(2)
print (t)
''' 
t = Avl()
x = int(input())
for _ in range(x):
    order = input().split()
    if order[0] == "find":
        f = t.find(order[1])
        if f:
            print (f)
        else:
            print ("not found")
    elif order[0] == "add":
        a = t.add(order[1])
        if not a:
            print ("already in there")
    elif order[0] == "remove":
        r = t.remove(order[1])
        if not r:
            print ("does not exist")
    # print (t)
