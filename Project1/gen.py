import random as rnd

t = 1
n = 2500
r = 50
c = 50

print(t)
print(n, r, c)
for i in range(n):
    a = rnd.randint(1, 25)
    b = rnd.randint(1, 25)
    c = rnd.randint(1, 25)
    d = rnd.randint(1, 25)
    print(a, b, c, d)

