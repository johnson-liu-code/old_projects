
import sys
import numpy as np
import matplotlib.pyplot as plt


file_name_1 = sys.argv[1]
#file_name_2 = sys.argv[2]

with open(file_name_1, 'r') as fil:
    lines = fil.readlines()
    points_1 = [x for x in lines if 'radius' in x and 'pressure' not in x]


#with open(file_name_2, 'r') as fil:
#    lines = fil.readlines()
#    points_2 = [x for x in lines if 'radius' in x and 'pressure' not in x]

earth_radius = 6.3781e8
earth_mass = 5.972e27

#print points

points_1 = [( float(x.split()[1]), float(x.split()[3]) ) for x in points_1]
radius_1, mass_1 = zip(*points_1)
radius_1 = np.array(radius_1)/earth_radius
mass_1 = np.array(mass_1)/earth_mass

#points_2 = [( float(x.split()[1]), float(x.split()[3]) ) for x in points_2]
#radius_2, mass_2 = zip(*points_2)
#radius_2 = np.array(radius_2)/earth_radius
#mass_2 = np.array(mass_2)/earth_mass

fig, ax = plt.subplots()

plt.scatter(mass_1, radius_1, label = 'solid')
#plt.scatter(mass_2, radius_2, label = 'liquid')

#plt.scatter(radius_1, mass_1/mass_2)

#ax.set_xscale('log')
#ax.set_yscale('log')

plt.xlabel('Mass (in Earth units)')
plt.ylabel('Radius (in Earth units)')

#plt.xlabel('Radius')
#plt.ylabel('Msolid / Mliquid')

plt.grid()

plt.legend(loc = 'upper left')

plt.show()
