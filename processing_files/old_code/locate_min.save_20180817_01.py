
import argparse

from run_integrator import *
from linear_interpolater import *


parser = argparse.ArgumentParser()
parser.add_argument("file_name")
parser.add_argument("integration_method")
parser.add_argument("eos")
args = parser.parse_args()

thresh = 1.e-4
variables = ['Initial Pressure', 'Rc', 'Radius', 'Mass']
step_size = 1e4

algorithm = args.integration_method
eos = args.eos

#num_layers = '3'
num_layers = '2'

core_state = 'solid'

if num_layers == '3':
    interface_pressure = '330x'
    rho_list = '7.85x7.05x3.98'
    K_list = '255x201x206'

elif num_layers == '2':
    interface_pressure = ''
    # solid iron
    if core_state == 'solid':
        rho_list = '7.85x3.98'
        K_list = '255x206'
    # liquid iron
    elif core_state == 'liquid':
        rho_list = '7.05x3.98'
        K_list = '201x206'

# Mercury
Rp = 2.439e8
Mp = 3.302e26

# Earth
#Rp = 6.3781e8
#Mp = 5.972e27

actual_values = [0, 0, Rp, Mp]

# 0: Pressure, 1: Rc, 2: radius, 3: mass
def find_min(data_list, inde_index, depe_index, desired_y):
    print('\nFinding best {} for {} ...\n'.format( variables[inde_index], variables[depe_index] ) )

    data_list[2] = []    # radius
    data_list[3] = []    # mass

    other_inde_index = int(np.abs(1. - inde_index))  # determine the other independent index

    for i in data_list[inde_index]:
        if inde_index == 0:                          # if the current inde index is Pressure
            radii_list = interface_pressure + str( data_list[other_inde_index][-1] ) # extract the previous Rc
            pressure = str(i)

        elif inde_index == 1:
            radii_list = interface_pressure + str(i) # if the current inde index is Rc
            pressure = str( data_list[other_inde_index][-1] )                        # extract the previous Pressure

        final_radius, final_mass, core_mass = run_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, algorithm, eos)

        #final_radius = final_radius/actual_values[depe_index]
        #final_mass = final_mass/actual_values[depe_index]

        data_list[2].append(final_radius)    # radius
        data_list[3].append(final_mass)      # mass

#    print('depe_variable: ', depe_index, ', inde_variable: ', inde_index)

    while abs( desired_y - data_list[depe_index][-1]/actual_values[depe_index] ) > thresh:       # while the error in the results is above a threshold
        if data_list[depe_index][0] - data_list[depe_index][1] == 0:   # break the cycle if we get the same Pressure or Rc consecutively
            print 'break'
            break
        # determine the next value for the inde variable
        next_inde_guess = lin_inter( data_list[inde_index], data_list[depe_index], desired_y )

        # run the simulation with the new guess for Pressure or Rc
        if inde_index == 0:
            radii_list = interface_pressure + str( data_list[other_inde_index][-1] )
            pressure = str(next_inde_guess)

            final_radius, final_mass, core_mass = run_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, algorithm, eos)

            #final_radius = final_radius/actual_values[depe_index]
            #final_mass = final_mass/actual_values[depe_index]

            print('pressure: {}, Rc: {}, radius: {}, mass: {}'.format(next_inde_guess, data_list[other_inde_index][-1], final_radius, final_mass))

        elif inde_index == 1:
            radii_list = interface_pressure + str(next_inde_guess)
            pressure = str( data_list[other_inde_index][-1] )

            final_radius, final_mass, core_mass = run_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, algorithm, eos)

            #final_radius = final_radius/actual_values[depe_index]
            #final_mass = final_mass/actual_values[depe_index]

            print('pressure: {}, Rc: {}, radius: {}, mass: {}'.format(data_list[other_inde_index][-1], next_inde_guess, final_radius, final_mass))

        # Take the value that is closer to the desired value
        if abs(desired_y - data_list[depe_index][0]/actual_values[depe_index]) < abs(desired_y - data_list[depe_index][1]/actual_values[depe_index]):
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

        print(abs( 1 - data_list[depe_index][-1]/actual_values[depe_index] ), thresh)
        (abs( 1 - data_list[depe_index][-1]/actual_values[depe_index] ) < thresh)

    return data_list


# 0: Pressure, 1: Rc, 2: radius, 3: mass
data_list = [ [10, 90], [.5*Rp, .6*Rp], [], [] ]
group_list = [ (0, 3), (1, 2) ]
#group_list = [ (0, 2), (1, 3)]
#group_list = [ (1, 2), (0, 3) ]

found_min = False
desired_y = 1.

while found_min == False:
    for g in group_list:
        data_list = find_min(data_list, g[0], g[1], desired_y)
    if abs(desired_y - data_list[2][-1]/actual_values[2]) < thresh and abs(desired_y - data_list[3][-1]/actual_values[3]) < thresh:
        found_min = True
