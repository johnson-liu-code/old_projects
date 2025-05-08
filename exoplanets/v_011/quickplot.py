import sys
import numpy as np
import matplotlib.pyplot as plt

file_name_1 = sys.argv[1]
file_name_2 = sys.argv[2]

with open(file_name_1, 'r') as fil:
    lines_1 = fil.readlines()[3:-6]
with open(file_name_2, 'r') as fil:
    lines_2 = fil.readlines()[3:-6]

r_1 = [float(line.split()[1]) for line in lines_1]
density_1 = [float(line.split()[3]) for line in lines_1]
pressure_1 = [float(line.split()[5]) for line in lines_1]
mass_1 = [float(line.split()[7]) for line in lines_1]

r_2 = [float(line.split()[1]) for line in lines_2]
density_2 = [float(line.split()[3]) for line in lines_2]
pressure_2 = [float(line.split()[5]) for line in lines_2]
mass_2 = [float(line.split()[7]) for line in lines_2]

max_density = max(max(density_1), max(density_2))
max_pressure = max(max(pressure_1), max(pressure_2))
max_mass = max(max(mass_1), max(mass_2))

#max_density = max(density_1)
#max_pressure = max(pressure_1)
#max_mass = max(mass_1)

'''
density_1 = np.array(density_1) / max(density_1)
pressure_1 = np.array(pressure_1) / max(pressure_1)
mass_1 = np.array(mass_1) / max(mass_1)

density_2 = np.array(density_2) / max(density_2)
pressure_2 = np.array(pressure_2) / max(pressure_2)
mass_2 = np.array(mass_2) / max(mass_2)
'''

density_1 = np.array(density_1) / max_density
pressure_1 = np.array(pressure_1) / max_pressure
mass_1 = np.array(mass_1) / max_mass

density_2 = np.array(density_2) / max_density
pressure_2 = np.array(pressure_2) / max_pressure
mass_2 = np.array(mass_2) / max_mass

plt.plot(r_1, density_1, label = 'density (1)')
plt.plot(r_1, pressure_1, label = 'pressure (1)')
plt.plot(r_1, mass_1, label = 'mass (1)')

plt.plot(r_2, density_2, label = 'density (2)')
plt.plot(r_2, pressure_2, label = 'pressure (2)')
plt.plot(r_2, mass_2, label = 'mass (2)')


plt.grid()

plt.legend()

plt.show()
