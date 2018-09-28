import sys
from run_integrator import *


file_name = sys.argv[1]
num_layers = '2'
radii_list = '1.64838471e8'
rho_list = '7.85x3.98'
K_list = '255x206'
pressure = '10'
step_size = '1e4'
algorithm = 'r'
eos = 'z'

radius, mass, core_mass = run_integrator(file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, algorithm, eos)
print("{0}, {1}, {2}".format(radius, mass, core_mass))

