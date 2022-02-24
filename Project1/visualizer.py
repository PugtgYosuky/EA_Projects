import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle

import random
r_c = lambda: random.randint(0,255)

f = plt.figure(figsize=(8, 8))
plt.show(block=False)
plt.pause(1)

r, c = map(int, input().split())

seconds_between_frames = 1 # Use 3 for small inputs, Use 0.001 for huge inputs

unique_colors = {}
used = []

for i in range(1, 1000):
    color = '#%02X%02X%02X' % (r_c(),r_c(),r_c())
    while color in used:
        color = '#%02X%02X%02X' % (r_c(),r_c(),r_c())
    used.append(color)
    unique_colors[i] = color

class Piece():

    def __init__(self, x, y, values):
        self.x = x
        self.y = y
        self.values = values
    
    def draw(self):
        plt.gca().add_patch(Rectangle((self.x, self.y), 1, 1, facecolor='none', edgecolor='black'))
        plt.gca().add_patch(Rectangle((self.x+0.5, self.y+0.5), 0.5, 0.5, color=unique_colors[self.values[1]]))
        plt.gca().add_patch(Rectangle((self.x, self.y+0.5), 0.5, 0.5, color=unique_colors[self.values[0]]))
        plt.gca().add_patch(Rectangle((self.x+0.5, self.y), 0.5, 0.5, color=unique_colors[self.values[2]]))
        plt.gca().add_patch(Rectangle((self.x, self.y), 0.5, 0.5, color=unique_colors[self.values[3]]))

plt.gca().add_patch(Rectangle((0, 0), r/r, c/c, facecolor='none'))
while True:
    try:
        n = int(input())
        plt.clf()
        plt.xlim([0, c])
        plt.ylim([0, r])
        pieces = []
        for i in range(n):
            x, y, x1, x2, x3, x4 = map(int, input().split())
            pieces.append(Piece(y, c-1-x, [x1, x2, x3, x4]))
        for piece in pieces:
            piece.draw()
        plt.show(block=False)
        plt.pause(seconds_between_frames)
    except Exception:
        plt.pause(20)
