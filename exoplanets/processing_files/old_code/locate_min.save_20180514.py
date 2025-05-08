
#from subprocess import Popen, PIPE
import argparse

from run_integrator import *
from linear_interpolater import *


parser = argparse.ArgumentParser()
parser.add_argument("file_name")
parser.add_argument("integration_method")
args = parser.parse_args()

thresh = 1.e-10
variables = ['Initial Pressure', 'Rc', 'Radius', 'Mass']
step_size = 1e4

algorithm = args.integration_method

num_layers = '3'
#radii_list = '330x.676'

if num_layers == '3':
    interface_pressure = '330x'
elif num_layers == '2':
    interface_pressure = ''

rho_list = '7.85x7.05x3.98'
K_list = '255x201x206'
#pressure = '500'
Rp = '6.3781e8'
Mp = '5.972e27'




def find_min(data_list, inde_index, depe_index):
    print('\nFinding best {} for {} ...\n'.format( variables[inde_index], variables[depe_index] ) )

    data_list[2] = []    # radius
    data_list[3] = []    # mass

    if inde_index == 0:
        other_inde_index = 1
    elif inde_index == 1:
        other_inde_index = 0

    for i in data_list[inde_index]:
        if inde_index == 0:
            radii_list = interface_pressure + str( data_list[other_inde_index][-1] )
            pressure = str(i)

            final_radius, final_mass = execute_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, Rp, Mp, algorithm )
        elif inde_index == 1:
            radii_list = interface_pressure + str(i)
            pressure = str( data_list[other_inde_index][-1] )

            final_radius, final_mass = execute_integrator( args.file_name, data_list[other_inde_index][-1], i, step_size, args.integration_method )

        data_list[2].append(final_radius)    # radius
        data_list[3].append(final_mass)      # mass

    while abs( 1 - data_list[depe_index][-1] ) > thresh:
        if data_list[depe_index][0] - data_list[depe_index][1] == 0:
            break

        next_inde_guess = lin_inter( data_list[inde_index], data_list[depe_index], 1 )

        if inde_index == 0:
            radii_list = interface_pressure + str( data_list[other_inde_index][-1] )
            pressure = str(i)

            final_radius, final_mass = execute_integrator( args.file_name, next_inde_guess, data_list[other_inde_index][-1], step_size, args.integration_method )
            print('pressure: {}, Rc: {}, radius: {}, mass: {}'.format(next_inde_guess, data_list[other_inde_index][-1], final_radius, final_mass))

        elif inde_index == 1:
            radii_list = interface_pressure + str(i)
            pressure = str( data_list[other_inde_index][-1] )

            final_radius, final_mass = execute_integrator( args.file_name, data_list[other_inde_index][-1], next_inde_guess, step_size, args.integration_method )
            print('pressure: {}, Rc: {}, radius: {}, mass: {}'.format(data_list[other_inde_index][-1], next_inde_guess, final_radius, final_mass))

        if abs(1 - data_list[depe_index][0]) < abs(1 - data_list[depe_index][1]):
            data_list[inde_index] = [ data_list[inde_index][0] ]
            data_list[2] = [ data_list[2][0] ]    # radius
            data_list[3] = [ data_list[3][0] ]    # mass
        else:
            data_list[inde_index] = [ data_list[inde_index][1] ]
            data_list[2] = [ data_list[2][1] ]    # radius
            data_list[3] = [ data_list[3][1] ]    # mass

        data_list[inde_index].append(next_inde_guess)
        data_list[2].append(final_radius)
        data_list[3].append(final_mass)

    return data_list


# 0: Pressure, 1: Rc, 2: radius, 3: mass
#data_list = [ [30, 50], [.4, .5], [], [] ]
data_list = [ [10, 11], [.8, .9], [], [] ]
#group_list = [ (0, 2), (1, 3), (0, 3), (1, 2), (0, 3), (1, 2), (0, 2), (1, 3) ]
#group_list = [ (0, 2), (1, 3), (0, 2), (1, 3), (1, 2), (0, 3), (1, 2), (0, 3) ]
group_list = [ (0, 3), (1, 2) ]
#group_list = [ (0, 2), (1, 3)]

found_min = False

while found_min == False:
    for g in group_list:
        data_list = find_min(data_list, g[0], g[1])
    if abs(1 - data_list[2][-1]) < thresh and abs(1 - data_list[3][-1]) < thresh:
        found_min = True
