import random as rnd

t = 1
n = 2500
r = 10
c = 10

no_repeat = []

def use(poss):
    can_use = True
    for pos in poss:
        if pos in no_repeat:
            can_use = False
            break
    return can_use

print(t)
print(n, r, c)
for i in range(n):
    a = rnd.randint(1, 25)
    b = rnd.randint(1, 25)
    c = rnd.randint(1, 25)
    d = rnd.randint(1, 25)
    possibilities = [[a, b, c, d], [b, c, d, a], [c, d, a, b], [d, c, a, b]]

    while not use(possibilities):
        a = rnd.randint(1, 25)
        b = rnd.randint(1, 25)
        c = rnd.randint(1, 25)
        d = rnd.randint(1, 25)
        possibilities = [[a, b, c, d], [b, c, d, a], [c, d, a, b], [d, c, a, b]]
    
    for pos in possibilities:
        no_repeat.append(pos)
    print(a, b, c, d)

