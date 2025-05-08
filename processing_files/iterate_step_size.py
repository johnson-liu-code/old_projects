
import argparse
import numpy as np
import matplotlib.pyplot as plt

from run_integrator import *


parser = argparse.ArgumentParser()
parser.add_argument("file_name")
args = parser.parse_args()

#step_size = ['1e3', '5e3', '1e4', '5e4', '1e5', '5e5', '1e6', '5e6']
step_size = ['1e3', '3e3', '5e3', '9e3', '1e4', '2e4', '3e4', '5e4', '1e5', '3e5', '5e5', '1e6', '3e6', '5e6']

#step_size = np.linspace(1e3, 5e6, 20)
#step_size = ['1e4']
#step_size = [1e2, 5e2]
#step_size = [1e1]
#step_size = [5e1]

#print step_size

pressure = '40.1415507194'
radii_list = '0.675567506625'
#radius = 1.000082001
#mass = 1.000077104

num_layers = '2'
rho_list = '7.85x3.98'
K_list = '255x206'
#step_size = '1e4'
Rp = '2.439e8'
Mp = '3.302e26'
algorithm = 'e'

#data_list = []

for step in step_size:
    final_radius, final_mass = run_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure, step, Rp, Mp, algorithm)
    print step, final_radius, final_mass
    #data_list.append( (step, final_radius, final_mass) )

#step, final_radius, final_mass = zip(*data_list)


#fig, ax = plt.subplots()

#plt.plot(step, final_radius)

#plt.show()
