import matplotlib.pyplot as plt
import sys

x = 0
y = 1
z = 5

L = 42305

with open('indata.csv') as f:
  data = f.readlines()[:L]

with open(f'{sys.argv[1]}/outdata') as f:
  cluster = f.readlines()[:L]

data = list(map(lambda a: a.split(','), data))
data = list(map(lambda a: list(map(float, a)), data))
data = list(map(lambda a: [a[x], a[y], a[z]], data))

cluster = list(map(lambda a: int(a.strip()), cluster))

fig = plt.figure()

ax = fig.add_subplot(projection='3d')
x, y, z = zip(*data)
ax.scatter(x,y,z, c=cluster)
  
ax.set_xlabel('danceability')
ax.set_ylabel('energy')
ax.set_zlabel('speechines')

plt.show()
