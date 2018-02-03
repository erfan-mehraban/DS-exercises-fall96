from collections import deque

class Map():

    class Location():

        def __init__(self, x=None, y=None, tup=None):
            if x is not None and y is not None:
                self.x = x
                self.y = y
            if tup is not None:
                self.x ,self.y = tup
        
        def __eq__(self, other):
            if self.x == other.x and self.y == other.y:
                return True
            return False

        def __repr__(self):
            return str(self.x)+" "+str(self.y)
            
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.parents = dict()
        self.target = self.Location(self.width-1, self.height-1)

    def set_map(self, m):
        self.map = m

    def __getitem__(self, tup):
        x, y = tup
        if x > -1 and y > -1 and x < self.width and y < self.height:
            return self.map[y][x]
        return None

    def valid_neighbors(self, x, y):
        if self[x + 1, y + 1]:
            yield self.Location(tup=(x + 1, y + 1))
        if self[x + 1, y]:
            yield self.Location(tup=(x + 1, y))
        if self[x, y + 1]:
            yield self.Location(tup=(x, y + 1))
        if self[x - 1, y + 1]:
            yield self.Location(tup=(x - 1, y + 1))
        if self[x + 1, y - 1]:
            yield self.Location(tup=(x + 1, y - 1))
        if self[x, y - 1]:
            yield self.Location(tup=(x, y - 1))
        if self[x - 1, y]:
            yield self.Location(tup=(x - 1, y))
        if self[x - 1, y - 1]:
            yield self.Location(tup=(x - 1, y - 1))
        
    def mark(self, location):
        self.map[location.y][location.x] = 0

    def set_parent(self, child, parent):
        self.parents[str(child.x)+","+str(child.y)]=parent

    def result_path_maker(self):
        
        # path = Stack()
        path = []
        path.append(self.Location(x=self.target.x,y=self.target.y))
        parent = self.parents[str(self.target.x)+","+str(self.target.y)]
        path.append(parent)
        while parent != self.Location(0,0):
            parent = self.parents[str(parent.x)+","+str(parent.y)]
            path.append(parent)
        return path
        '''
        result = str(self.target.x)+" "+str(self.target.y)
        parent = self.parents[str(self.target.x)+","+str(self.target.y)]
        counter = 1
        while parent != self.Location(0,0):
            parent = self.parents[str(parent.x)+","+str(parent.y)]
            result = "%s %s\n%s" % (str(parent.x), str(parent.y), result)
            counter += 1
        return str(counter)+"\n"+result
        '''

    def DFS(self):
        # search = Stack()
        search = [self.Location(x=0, y=0)]
        # current_vector = self.Location(x=0, y=0)
        self.mark(search[0])
        while ( len(search) ):
            
            # self.map[current_vector.x][current_vector.y] = 2
            # print(self)
            
            current_vector = search.pop()
            for vector in self.valid_neighbors(current_vector.x, current_vector.y):
                self.mark(vector)
                search.append(vector)
                self.set_parent(vector, current_vector)
                if vector == self.target:
                    return self.result_path_maker()
        return []

    def BFS(self):
        search = deque([self.Location(x=0, y=0)])
        # current_vector = self.Location(x=0, y=0)
        self.mark(search[0])
        while ( len(search) ):
            current_vector = search.popleft()
            
            for vector in self.valid_neighbors(current_vector.x, current_vector.y):
                self.mark(vector)
                search.append(vector)
                self.set_parent(vector, current_vector)
                if vector == self.target:
                    return self.result_path_maker()
        return []


    def __str__(self):
        result = ""
        for row in self.map:
            for cell in row:
                result+=str(cell)+" , "
            result+="\n"
        return result

'''
test = Map(4, 4)
test.set_map([
    [1, 1, 1, 1],
    [1, 1, 0, 1],
    [1, 0, 0, 0],
    [1, 1, 1, 1]
])
print (test)
path = test.BFS()
while path.size > 0:
    node = path.pop()
    print (node.x+1,node.y+1)
'''
size = input().split()
main_map = Map(int(size[1]), int(size[0]))
input_map = []
for _ in range(int(size[0])):
    row = input()
    row_map = []
    for cell in row:
        row_map.append(int(not int(cell)))
    # print (row_map)
    input_map.append(row_map)
main_map.set_map(input_map)
# print (main_map)

path = main_map.BFS()
answer_size = len(path)(23 + 3 * 4) / 6 - 2
if answer_size:
    print (answer_size)
    while len(path) > 0:
        node = path.pop()
        print (node.y+1, node.x+1)
else:
    print ("That's a dead end!")