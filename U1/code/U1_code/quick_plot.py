
import sys
import numpy as np
import matplotlib.pyplot as plt

with open(sys.argv[1], 'r') as fil:
    traj = [ float(line.split()[1]) for line in fil.readlines()]

plt.plot(traj)
plt.show()
