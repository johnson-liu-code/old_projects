
from subprocess import Popen, PIPE
import argparse

from linear_interpolater import *


parser = argparse.ArgumentParser()

parser.add_argument("file_name")
#parser.add_argument("-s", "--save", action = 'store_true')

args = parser.parse_args()

def execute_integrator(pressure, Rc):
    process = Popen(["./" + args.file_name, str(pressure), str(Rc), "r"], stdout = PIPE)
    (output, err) = process.communicate()

    final_radius = output.splitlines()[-1].split()[1]
    final_mass = output.splitlines()[-1].split()[-1]

    return float(final_radius), float(final_mass)

thresh_1 = 1.e-4
thresh_2 = 1.e-6

print('Finding best initial Pressure using radius as measure ... ')

pressure_list = [30, 50]
Rc = .5

final_radius_list = []
final_mass_list = []

for pressure in pressure_list:
    final_radius, final_mass = execute_integrator(pressure, Rc)
    final_radius_list.append(final_radius)
    final_mass_list.append(final_mass)

while abs(1 - final_radius) > thresh_1:
    next_pressure_guess = lin_inter(pressure_list, final_radius_list, 1)
    final_radius, final_mass = execute_integrator(next_pressure_guess, Rc)

    print('pressure: {}, Rc: {}, radius: {}, mass: {}'.format(next_pressure_guess, Rc, final_radius, final_mass))

    if abs(1 - final_radius_list[0]) < abs(1 - final_radius_list[1]):
        pressure_list = [ pressure_list[0] ]
        final_radius_list = [ final_radius_list[0] ]
        final_mass_list = [ final_mass_list[0] ]
    else:
        pressure_list = [ pressure_list[1] ]
        final_radius_list = [ final_radius_list[1] ]
        final_mass_list = [ final_mass_list[1] ]

    pressure_list.append(next_pressure_guess)
    final_radius_list.append(final_radius)
    final_mass_list.append(final_mass)

print('Finding best Rc using mass as measure ... ')

pressure = next_pressure_guess
Rc_list = [.5, .4]

final_radius_list = []
final_mass_list = []

# The first one is redundant from the final_radius and final_mass from above.
for Rc in Rc_list:
    final_radius, final_mass = execute_integrator(pressure, Rc)
    final_radius_list.append(final_radius)
    final_mass_list.append(final_mass)

while abs(1 - final_mass) > thresh_1:
    next_Rc_guess = lin_inter(Rc_list, final_mass_list, 1)
    final_radius, final_mass = execute_integrator(pressure, next_Rc_guess)

    print('pressure: {}, Rc: {}, radius: {}, mass: {}'.format(pressure, next_Rc_guess, final_radius, final_mass))

    if abs(1 - final_mass_list[0]) < abs(1 - final_mass_list[1]):
        Rc_list = [ Rc_list[0] ]
        final_radius_list = [ final_radius_list[0] ]
        final_mass_list = [ final_mass_list[0] ]
    else:
        Rc_list = [ Rc_list[1] ]
        final_radius_list = [ final_radius_list[1] ]
        final_mass_list = [ final_mass_list[1] ]

    Rc_list.append(next_Rc_guess)
    final_radius_list.append(final_radius)
    final_mass_list.append(final_mass)

print('Finding best initial Pressure using mass as measure ... ')

Rc = next_Rc_guess

final_radius_list = []
final_mass_list = []

for pressure in pressure_list:
    final_radius, final_mass = execute_integrator(pressure, Rc)
    final_radius_list.append(final_radius)
    final_mass_list.append(final_mass)

while abs(1 - final_mass) > thresh_2:
    next_pressure_guess = lin_inter(pressure_list, final_mass_list, 1)
    final_radius, final_mass = execute_integrator(next_pressure_guess, Rc)

    print('pressure: {}, Rc: {}, radius: {}, mass: {}'.format(next_pressure_guess, Rc, final_radius, final_mass))

    if abs(1 - final_mass_list[0]) < abs(1 - final_mass_list[1]):
        pressure_list = [ pressure_list[0] ]
        final_radius_list = [ final_radius_list[0] ]
        final_mass_list = [ final_mass_list[0] ]
    else:
        pressure_list = [ pressure_list[1] ]
        final_radius_list = [ final_radius_list[1] ]
        final_mass_list = [ final_mass_list[1] ]

    pressure_list.append(next_pressure_guess)
    final_radius_list.append(final_radius)
    final_mass_list.append(final_mass)

print('Finding best Rc using radius as measure ... ')

pressure = next_pressure_guess

final_radius_list = []
final_mass_list = []

# The first one is redundant from the final_radius and final_mass from above.
for Rc in Rc_list:
    final_radius, final_mass = execute_integrator(pressure, Rc)
    final_radius_list.append(final_radius)
    final_mass_list.append(final_mass)

while abs(1 - final_radius) > thresh_2:
    next_Rc_guess = lin_inter(Rc_list, final_radius_list, 1)
    final_radius, final_mass = execute_integrator(pressure, next_Rc_guess)

    print('pressure: {}, Rc: {}, radius: {}, mass: {}'.format(pressure, next_Rc_guess, final_radius, final_mass))

    if abs(1 - final_radius_list[0]) < abs(1 - final_radius_list[1]):
        Rc_list = [ Rc_list[0] ]
        final_radius_list = [ final_radius_list[0] ]
        final_mass_list = [ final_mass_list[0] ]
    else:
        Rc_list = [ Rc_list[1] ]
        final_radius_list = [ final_radius_list[1] ]
        final_mass_list = [ final_mass_list[1] ]

    Rc_list.append(next_Rc_guess)
    final_radius_list.append(final_radius)
    final_mass_list.append(final_mass)
