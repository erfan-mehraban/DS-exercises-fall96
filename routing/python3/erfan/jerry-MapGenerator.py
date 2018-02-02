import random
start = 300
end = 300
print (str(start) +" "+str(end))
for _ in range(start):
     for __ in range(end):
             print(random.randint(0,1),end="")
     print()
