import sys
import numpy as np
import matplotlib.pyplot as plt

file_name = sys.argv[1]

with open(file_name, 'r') as fil:
    lines = fil.readlines()[3:-4]

r = [float(line.split()[1]) for line in lines]
density = [float(line.split()[3]) for line in lines]
pressure = [float(line.split()[5]) for line in lines]
mass = [float(line.split()[7]) for line in lines]

density = np.array(density) / max(density)
pressure = np.array(pressure) / max(pressure)
mass = np.array(mass) / max(mass)

plt.plot(r, density, label = 'density')
plt.plot(r, pressure, label = 'pressure')
plt.plot(r, mass, label = 'mass')

plt.legend()

plt.show()
