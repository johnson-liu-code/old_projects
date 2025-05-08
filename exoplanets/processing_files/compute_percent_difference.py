
import numpy as np


with open('earthlike_solid_core.txt', 'r') as fil:
    lines = fil.readlines()
    earthlike_solid_points = [x for x in lines if 'expected' in x]

with open('earthlike_liquid_core.txt', 'r') as fil:
    lines = fil.readlines()
    earthlike_liquid_points = [x for x in lines if 'expected' in x]

earth_radius = 6.3781e8
earth_mass = 5.972e27

earthlike_solid_points = [ (float(x.split()[1]), float(x.split()[5])) for x in earthlike_solid_points]
earthlike_solid_radius, earthlike_solid_mass = zip(*earthlike_solid_points)
earthlike_solid_radius = np.array(earthlike_solid_radius)/earth_radius
earthlike_solid_mass = np.array(earthlike_solid_mass)/earth_mass

earthlike_liquid_points = [ (float(x.split()[1]), float(x.split()[5])) for x in earthlike_liquid_points]
earthlike_liquid_radius, earthlike_liquid_mass = zip(*earthlike_liquid_points)
earthlike_liquid_radius = np.array(earthlike_liquid_radius)/earth_radius
earthlike_liquid_mass = np.array(earthlike_liquid_mass)/earth_mass

#per = earthlike_solid_mass / earthlike_liquid_mass
#per = earthlike_liquid_mass / earthlike_solid_mass
per1 = (earthlike_solid_mass - earthlike_liquid_mass)/earthlike_solid_mass
per2 = np.abs(earthlike_liquid_mass - earthlike_solid_mass)/earthlike_liquid_mass

per1_mean = np.mean(per1)
per2_mean = np.mean(per2)

#print per
print per1_mean
print per2_mean
