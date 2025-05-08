
import argparse
import numpy as np

from run_integrator_earth_like import *
from linear_interpolater import *

parser = argparse.ArgumentParser()
parser.add_argument("file_name")
args = parser.parse_args()

thresh = 1.e-3
step_size = 1e4
algorithm = 'r'

num_layers = '2'
rho_list = '7.85x3.98'
K_list = '255x206'

# Earth
Rp = 6.3781e8
Mp = 5.972e27

per_iron = (4./3)*np.pi*(0.477695691907 * Rp)**3. / Mp
per_rock = 1. - per_iron

#factor = [1., 5., 10.]
factor = [15., 20., 25.]

desired_pressure = 0.


for f in factor:
    initial_pressure_list = [f * 200, (f+2) * 200]
    final_pressure_list = [0, 0]

    total_mass = f * Mp

    print initial_pressure_list
    print ('initializing\n')
    for c, pressure in enumerate(initial_pressure_list):
        final_pressure = execute_integrator( args.file_name, num_layers, rho_list, K_list, pressure, step_size, algorithm, per_iron, per_rock, total_mass)
        final_pressure_list[c] = final_pressure

    print ('done with initialization\n')

    while abs( desired_pressure - final_pressure_list[-1] ) > thresh:
        next_pressure_guess = lin_inter(initial_pressure_list, final_pressure_list, desired_pressure)
        print('done with interpolation\n')
        print ('next pressure guess: ', next_pressure_guess)
        final_pressure = execute_integrator( args.file_name, num_layers, rho_list, K_list, next_pressure_guess, step_size, algorithm, per_iron, per_rock, total_mass)
        print ('final pressure: ', final_pressure)
        print ('\n')

        if abs(desired_pressure - final_pressure_list[0]) < abs(desired_pressure - final_pressure_list[1]):
            initial_pressure_list[1] = next_pressure_guess
            final_pressure_list[1] = final_pressure
        else:
            initial_pressure_list[0] = initial_pressure_list[1]
            final_pressure_list[0] = final_pressure_list[1]

            initial_pressure_list[1] = next_pressure_guess
            final_pressure_list[1] = final_pressure

    print ('optimal initial pressure for ' + str(f) + ' times the Earth mass is: ', next_pressure_guess)


