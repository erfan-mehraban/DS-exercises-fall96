import random
import matplotlib.pyplot as plt

def h():
    z = random.randint(0,1024)
    k = 0
    m = 1
    while (z&m) != 0:
        k += 1
        m <<= 1
    return k
d = []
x = [0]*30
for _ in range (0,100000):
    hh = h()
    x[hh]+=1
    d.append(hh)
print (x)
plt.hist(d,bins=30)
plt.savefig("randomHeight.png")
