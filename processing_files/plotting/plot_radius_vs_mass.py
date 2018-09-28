import argparse
import os
import numpy as np
import pickle
import matplotlib.pyplot as plt


parser = argparse.ArgumentParser()
parser.add_argument('file_01')
parser.add_argument('file_02')
parser.add_argument('file_03')
#parser.add_argument('earth_like_dir')
args = parser.parse_args()

earth_radius = 6.3781e8			# cm
earth_mass = 5.972e27			# g

with open(args.file_01, 'rb') as fil:
    curve_01 = pickle.load(fil)
with open(args.file_02, 'rb') as fil:
    curve_02 = pickle.load(fil)
with open(args.file_03, 'rb') as fil:
    curve_03 = pickle.load(fil)


Pi_curve_01, Rc_curve_01, R_curve_01, M_curve_01 = zip(*curve_01)
Pi_curve_02, Rc_curve_02, R_curve_02, M_curve_02 = zip(*curve_02)
Pi_curve_03, Rc_curve_03, R_curve_03, M_curve_03 = zip(*curve_03)


M_curve_01 = np.array(M_curve_01) / earth_mass
R_curve_01 = np.array(R_curve_01) / earth_radius
M_curve_02 = np.array(M_curve_02) / earth_mass
R_curve_02 = np.array(R_curve_02) / earth_radius
M_curve_03 = np.array(M_curve_03) / earth_mass
R_curve_03 = np.array(R_curve_03) / earth_radius

'''
earth_like_data = []

for fil in os.listdir(args.earth_like_dir):
    if 'mass_radius' in fil:
        with open(args.earth_like_dir + '/' + fil) as dat:
            lines = dat.readlines()
            mass = float( lines[3].split()[2] )
            radius = float( lines[3].split()[5] )
            earth_like_data.append( (mass, radius) )

earth_like_mass, earth_like_radius = zip(*earth_like_data)
earth_like_mass = np.array(earth_like_mass) / earth_mass
earth_like_radius = np.array(earth_like_radius) / earth_radius
'''

def mass_radius_relation(M, rmf):
    return (.0592 * rmf + .0975)*np.log10(M)**2. + (.2337 * rmf + .4938)*np.log10(M) + (.3102 * rmf + .7932)

#earth_rmf = 0.7946250334

M_range = np.linspace(0, 32, 1000)
#earth_R = mass_radius_relation(M_range, earth_rmf)

#curve_01_rmf = 1.
#curve_01_R = mass_radius_relation(M_range, curve_01_rmf)

curve_02_rmf = 0.
curve_02_R = mass_radius_relation(M_range, curve_02_rmf)


fig, ax = plt.subplots()

#plt.scatter(M_curve_01, R_curve_01, label = 'curve_01y Planet')
#plt.scatter(M_curve_01, R_curve_01, label = 'curve_02\n(Seager Equation of State)')
#plt.plot(M_range, curve_01_R, color = 'blue', label = 'Mass-Radius Relation (curve_01)')

#plt.scatter(M_curve_02, R_curve_02, label = 'curve_02 Planet')
plt.plot(M_range, curve_02_R, color = 'red', label = 'Mass-Radius Relation (Iron)')

plt.scatter(M_curve_01, R_curve_01, label = 'Iron\n(Zeng Equation of State)')
plt.scatter(M_curve_02, R_curve_02, label = 'Iron\n(Vinet Equation of State)')
plt.scatter(M_curve_03, R_curve_03, label = 'Iron\n(BME Equation of State)')


#plt.scatter(earth_like_mass, earth_like_radius, label = 'Earth-like Planet')
#plt.plot(M_range, earth_R, color = 'green', label = 'Mass-Radius Relation (Earth-like)')


plt.xlabel("Mass (Relative to the Earth's)" + r"(log$_{10}$ scale)")
plt.ylabel("Radius\n(Relative to\nthe Earth's)\n" + r"(log$_{10}$ scale)", rotation = 0, labelpad = 40)
plt.grid(linestyle = '--')

ax.set_xscale('log')
ax.set_yscale('log')


plt.legend()
plt.tight_layout()
plt.show()
