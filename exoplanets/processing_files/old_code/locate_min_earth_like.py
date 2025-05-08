

import argparse
import numpy as np
from decimal import Decimal

from run_integrator_earth_like import *
from linear_interpolater import *

parser = argparse.ArgumentParser()
parser.add_argument('file_name')
parser.add_argument('pressure', type = float)
parser.add_argument('Rc_01', type = float)
parser.add_argument('Rc_02', type = float)
args = parser.parse_args()

thresh = 1.e-4
step_size = 1e4
algorithm = 'r'

num_layers = '2'
rho_list = '7.85x3.98'
K_list = '255x206'

# Earth
Rp = 6.3781e8
Mp = 5.972e27
mass_frac_iron = 0.2053749666
mass_frac_rock = 0.7946250334


def compute_frac_mass_frac_iron(pressure, radii_list):
    frac_mass_frac_iron = run_integrator(args.file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, mass_frac_iron, mass_frac_rock, algorithm)
    return frac_mass_frac_iron

#pressure_list = [5000]
pressure_list = [args.pressure]
desired_y = 1.

def find_next_guess(pressure, Rc_guess_list, frac_mass_frac_iron_list):
    next_Rc_guess = lin_inter(Rc_guess_list, frac_mass_frac_iron_list, desired_y)
    frac_mass_frac_iron = compute_frac_mass_frac_iron(pressure, str(next_Rc_guess))

    print('next Rc guess: {0:.5E}'.format( Decimal(next_Rc_guess) ) )
    print('frac_mass_frac_iron: {}'.format( frac_mass_frac_iron ) )
    print('\n')

    if np.abs(next_Rc_guess - Rc_guess_list[0]) < np.abs(next_Rc_guess - Rc_guess_list[1]):
        Rc_guess_list[1] = next_Rc_guess
        frac_mass_frac_iron_list[1] = frac_mass_frac_iron
    else:
        Rc_guess_list[0] = next_Rc_guess
        frac_mass_frac_iron_list[0] = frac_mass_frac_iron

    return Rc_guess_list, frac_mass_frac_iron_list


for pressure in pressure_list:
    print('Finding best Rc for pressure: {}'.format(pressure) )

#    Rc_guess_list = [4.9e8, 5e8]
    Rc_guess_list = [args.Rc_01, args.Rc_02]
    frac_mass_frac_iron_list = []

    for Rc in Rc_guess_list:
        frac_mass_frac_iron = compute_frac_mass_frac_iron(pressure, str(Rc))
        frac_mass_frac_iron_list.append(frac_mass_frac_iron)

    Rc_guess_list, frac_mass_frac_iron_list = find_next_guess(pressure, Rc_guess_list, frac_mass_frac_iron_list)

    while np.abs(desired_y - frac_mass_frac_iron_list[1]) > thresh:
        Rc_guess_list, frac_mass_frac_iron_list = find_next_guess(pressure, Rc_guess_list, frac_mass_frac_iron_list)

        if frac_mass_frac_iron_list[0] == 0 or frac_mass_frac_iron_list[1] == 0:
            break
