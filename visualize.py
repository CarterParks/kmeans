#!/bin/python3
import matplotlib.pyplot as plt
import sys

L = 42305

with open('indata3col.csv') as f:
  data = f.readlines()[:L]

data = list(map(lambda a: a.split(','), data))
data = list(map(lambda a: list(map(float, a)), data))
data = list(map(lambda a: a[:3], data))

fig = plt.figure()
for i, m in enumerate(sys.argv[1:]):
  with open(f'{m}/outdata') as f:
    cluster = f.readlines()[:L]

  cluster = list(map(lambda a: int(a.strip()), cluster))

  ax = fig.add_subplot(1,len(sys.argv)-1,i+1, projection='3d')
  ax.set_title(m)
  x, y, z = zip(*data)
  ax.scatter(x,y,z, c=cluster)
    
  ax.set_xlabel('danceability')
  ax.set_ylabel('energy')
  ax.set_zlabel('speechines')

plt.show()
