
import argparse
import numpy as np


from run_integrator import *
from linear_interpolater import *


parser = argparse.ArgumentParser()
parser.add_argument("file_name")
parser.add_argument("integration_method")
parser.add_argument("eos")
args = parser.parse_args()

thresh = 1.e-3
variables = ['Central Pressure', 'Rc', 'Radius', 'Core Mass Frac Ratio']

algorithm = args.integration_method
eos = args.eos

#num_layers = '3'
num_layers = '2'

#core_state = 'solid'
core_state = 'liquid'

if num_layers == '3':
    #core_boundary = ''
    rho_list = '7.85x7.05x3.98'
    K_list = '255x201x206'

elif num_layers == '2':
    #core_boundary = ''
    # solid iron
    if core_state == 'solid':
        rho_list = '7.85x3.98'
        K_list = '255x206'
    # liquid iron
    elif core_state == 'liquid':
        rho_list = '7.05x3.98'
        K_list = '201x206'

# Earth
earth_radius = '6.3781e8'
earth_mass = '5.972e27'

CMFR_thresh = 1e-3
reduction_factor = .5

def initialize_data(data_list, inde_index, other_inde_index, step_size):
    for c, i in enumerate( data_list[inde_index] ):
        if inde_index == 0:
            radii_list = str( data_list[other_inde_index][1] )
            pressure = str(i)

        elif inde_index == 1:
            radii_list = str(i)
            pressure = str( data_list[other_inde_index][1] )

        final_radius, final_mass, core_mass_frac_ratio = run_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, algorithm, eos, radius_p, mass_p, expected_core_mass_frac)
        #print final_radius, final_mass, core_mass_frac_ratio
        ##################################################
        data_list[2].append(final_radius)          # radius
        ##################################################
        #data_list[2].append(core_mass_frac_ratio) # CMFR
        ##################################################
        #data_list[3].append(final_mass)           # mass
        data_list[3].append(core_mass_frac_ratio)  # CMFR

    return data_list

def find_min(data_list, inde_index, depe_index, desired_y, expected_core_mass_frac, radius_p, mass_p):
    print('\nFinding best {} for {} ...\n'.format( variables[inde_index], variables[depe_index] ) )

    data_list[2] = []    # radius / core_mass_frac_ratio
    data_list[3] = []    # mass

    other_inde_index = int(np.abs(1 - inde_index))

    step_size = '1e4'

    data_list = initialize_data(data_list, inde_index, other_inde_index, step_size)

    while abs( desired_y - data_list[depe_index][1] ) > thresh:

        while np.abs(data_list[1][0] - data_list[1][1]) < float(step_size):
            step_size = str(.5*float(step_size))

            if float(step_size) < 1e1:
                print 'break'
                break

            data_list[2] = []
            data_list[3] = []

            data_list = initialize_data(data_list, inde_index, other_inde_index, step_size)

        print data_list

        next_inde_guess = lin_inter( data_list[inde_index], data_list[depe_index], desired_y )
        print 'next_inde_guess: {0:.10f}'.format(next_inde_guess)

        step_size = '1e4'

#        print 'inde_index: ', inde_index

        if inde_index == 0:
            radii_list = str( data_list[other_inde_index][1] )
            pressure = str(next_inde_guess)

            final_radius, final_mass, core_mass_frac_ratio = run_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, algorithm, eos, radius_p, mass_p, expected_core_mass_frac )

        elif inde_index == 1:
            radii_list = str(next_inde_guess)
            pressure = str( data_list[other_inde_index][1] )

            final_radius, final_mass, core_mass_frac_ratio = run_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, algorithm, eos, radius_p, mass_p, expected_core_mass_frac )

        if abs(desired_y - data_list[depe_index][0]) < abs(desired_y - data_list[depe_index][1]):
            data_list[inde_index] = [ data_list[inde_index][0], next_inde_guess ]
            data_list[2] = [ data_list[2][0], final_radius ]
            data_list[3] = [ data_list[3][0], core_mass_frac_ratio ]

        else:
            data_list[inde_index] = [ data_list[inde_index][1], next_inde_guess ]
            data_list[2] = [ data_list[2][1], final_radius ]
            data_list[3] = [ data_list[3][1], core_mass_frac_ratio ]

    if inde_index == 1:
        while abs( core_mass_frac_ratio - 1) > CMFR_thresh:
            print ('hello, ', abs( core_mass_frac_ratio - 1) )
            step_size = str( float(step_size) * reduction_factor )
            print ('step_size: ', step_size )

            final_radius, final_mass, core_mass_frac_ratio = run_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, algorithm, eos, radius_p, mass_p, expected_core_mass_frac )

    return data_list, final_radius, final_mass, core_mass_frac_ratio


# 0: pressure, 1: Rc, 2: radius, 3: mass
# 0: pressure, 1: Rc, 2: core_mass_frac_ratio, 3: mass

group_list = [ (0, 2), (1, 3)]

found_min = False
desired_y = 1.

expected_core_mass_frac_list = ['0.295896']

mass_p = earth_mass

#Rp_list = np.arange(.2, 1.4, .1)
Rp_list = np.arange(.25, 1.45, .1)
#print Rp_list
#Rp_list = np.arange(1.4, 2.3, .1)
#Rp_list = np.arange(1.45, 2.35, .1)

for expected_core_mass_frac in expected_core_mass_frac_list:
    for Rp in Rp_list:
        radius_p = str(float(Rp)*float(earth_radius))   # expected planet radius
        data_list = [ [10., 20.], [2e7, 3e7], [], [] ]
        #data_list = [ [390, 400], [335480418.12338907, 334875284.3009298], [], [] ]

        while found_min == False:
            for g in group_list:
                data_list, final_radius, final_mass, core_mass_frac_ratio = find_min(data_list, g[0], g[1], desired_y, expected_core_mass_frac, radius_p, mass_p)

            if abs(desired_y - data_list[2][-1]) < thresh and abs(desired_y - data_list[3][-1]) < thresh:
                found_min = True
                #final_radius = float(final_radius) * float(earth_radius) # this is wrong
                final_radius = float(final_radius) * float(radius_p)
                final_mass = float(final_mass) * float(earth_mass)
                core_mass_frac_ratio = float(core_mass_frac_ratio) * float(expected_core_mass_frac)
                print 'expected_Rp: {} radius: {} mass: {} CMF: {}'.format(radius_p, final_radius, final_mass, core_mass_frac_ratio)
                print data_list
        found_min = False
