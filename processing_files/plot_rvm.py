
import sys
import numpy as np
import matplotlib.pyplot as plt


#file_name_1 = sys.argv[1]
#file_name_2 = sys.argv[2]

with open('rocky_planets_02.txt', 'r') as fil:
    lines = fil.readlines()
    points_1 = [x for x in lines if 'radius' in x and 'pressure' not in x]

with open('iron_planets_02.txt', 'r') as fil:
    lines = fil.readlines()
    points_2 = [x for x in lines if 'radius' in x and 'pressure' not in x]

with open('earthlike_solid_core.txt', 'r') as fil:
    lines = fil.readlines()
    earthlike_solid_points = [x for x in lines if 'expected' in x]

with open('earthlike_liquid_core.txt', 'r') as fil:
    lines = fil.readlines()
    earthlike_liquid_points = [x for x in lines if 'expected' in x]

earth_radius = 6.3781e8
earth_mass = 5.972e27

#print points

#points_1 = [( float(x.split()[3]), float(x.split()[5]) ) for x in points_1]
#points_1 = [( float(x.split()[1]), float(x.split()[5]) ) for x in points_1]
points_1 = [( float(x.split()[1]), float(x.split()[3]), float(x.split()[5]) ) for x in points_1]
expected_radius_1, radius_1, mass_1 = zip(*points_1)
radius_1 = np.multiply(expected_radius_1, radius_1)/earth_radius
#mass_1 = np.array(mass_1)/earth_mass

#points_2 = [( float(x.split()[3]), float(x.split()[5]) ) for x in points_2]
#points_2 = [( float(x.split()[1]), float(x.split()[5]) ) for x in points_2]
points_2 = [( float(x.split()[1]), float(x.split()[3]), float(x.split()[5]) ) for x in points_2]
expected_radius_2, radius_2, mass_2 = zip(*points_2)
radius_2 = np.multiply(expected_radius_2, radius_2)/earth_radius
#mass_2 = np.array(mass_2)/earth_mass

earthlike_solid_points = [ (float(x.split()[1]), float(x.split()[5])) for x in earthlike_solid_points]
earthlike_solid_radius, earthlike_solid_mass = zip(*earthlike_solid_points)
earthlike_solid_radius = np.array(earthlike_solid_radius)/earth_radius
earthlike_solid_mass = np.array(earthlike_solid_mass)/earth_mass

earthlike_liquid_points = [ (float(x.split()[1]), float(x.split()[5])) for x in earthlike_liquid_points]
earthlike_liquid_radius, earthlike_liquid_mass = zip(*earthlike_liquid_points)
earthlike_liquid_radius = np.array(earthlike_liquid_radius)/earth_radius
earthlike_liquid_mass = np.array(earthlike_liquid_mass)/earth_mass


def mass_radius_relation(rmf, x):
    return (.0592*rmf + .0975)*(np.log10(x))**2. + (.2337*rmf + .4938)*(np.log10(x)) + (.3102*rmf + .7932)

x_range = np.linspace(min(mass_1), max(mass_2), 1000)
#x_range = np.linspace(min(mass_1), 35, 100)

all_iron_curve = mass_radius_relation(0, x_range)
all_rock_curve = mass_radius_relation(1, x_range)
earth_like_curve = mass_radius_relation(0.295896, x_range)

mercury_mass = 3.30104e26
moon_mass = 7.34767309e25


with open('mercury.txt', 'r') as mer:
    fields = mer.readlines()[0].split()
    mer_radius = float(fields[1])/earth_radius
    mer_mass = ( float(fields[5])*mercury_mass ) /earth_mass

with open('moon.txt', 'r') as moon:
    fields = moon.readlines()[0].split()
    moon_radius = float(fields[1])/earth_radius
    moon_mass = ( float(fields[5])*moon_mass ) /earth_mass

with open('venus.txt', 'r') as venus:
    fields = venus.readlines()[0].split()
    venus_radius = float(fields[1])/earth_radius
    venus_mass = float(fields[5])

with open('mars.txt', 'r') as mars:
    fields = mars.readlines()[0].split()
    mars_radius = float(fields[1])/earth_radius
    mars_mass = float(fields[5])

with open('ceres.txt', 'r') as ceres:
    fields = ceres.readlines()[0].split()
    ceres_radius = float(fields[1])/earth_radius
    ceres_mass = float(fields[5])

with open('pluto.txt', 'r') as pluto:
    fields = pluto.readlines()[0].split()
    pluto_radius = float(fields[1])/earth_radius
    pluto_mass = float(fields[5])


fig, ax = plt.subplots()

#plt.scatter(mass_1, radius_1, label = 'rocky')
#plt.scatter(mass_2, radius_2, label = 'iron')
#plt.scatter(mer_mass, mer_radius, label = 'Mercury')
#plt.scatter(moon_mass, moon_radius, label = 'Moon')
#plt.scatter(venus_mass, venus_radius, label = 'Venus')
#plt.scatter(mars_mass, mars_radius, label = 'Mars')
plt.scatter(ceres_mass, ceres_radius, label = 'Ceres')
#plt.scatter(pluto_mass, pluto_radius, label = 'Pluto')
#plt.scatter(1, 1, label = 'Earth')
#plt.scatter(earthlike_solid_mass, earthlike_solid_radius, label = 'Earth-like solid core')
#plt.scatter(earthlike_liquid_mass, earthlike_liquid_radius, label = 'Earth-like liquid core')
plt.xscale('log')
plt.yscale('log')

#plt.plot(x_range, all_rock_curve, label = 'Mass-Radius Relation (Rocky)')
#plt.plot(x_range, all_iron_curve, label = 'Mass-Radius Relation (Iron)')
#plt.plot(x_range, earth_like_curve, label = 'Mass-Radius Relation (Earth-like)')

#plt.scatter(radius_1, mass_1/mass_2)
#plt.scatter(radius_2, mass_1/mass_2)

#ax.set_xscale('log')
#ax.set_yscale('log')

plt.xlabel('Mass (in Earth units)')
plt.ylabel('Radius\n(in Earth\nunits)', rotation = 0)

#plt.xlabel('Radius')
#plt.ylabel('Msolid / Mliquid')

plt.grid(b = True, which = 'major', color = 'k', linestyle = '-')
plt.grid(b = True, which = 'minor', color = 'k', linestyle = '--')

plt.legend(loc = 'upper left')

plt.show()
