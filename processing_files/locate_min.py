
import argparse
import numpy as np


from run_integrator import *
from linear_interpolater import *


parser = argparse.ArgumentParser()
parser.add_argument("file_name")
parser.add_argument("integration_method")
parser.add_argument("eos")
args = parser.parse_args()

thresh = 1.e-4
#thresh = 1.e-5
#variables = ['Central Pressure', 'Rc', 'Radius', 'Mass']
#variables = ['Central Pressure', 'Rc', 'Core Mass Frac Ratio', 'Mass']
variables = ['Central Pressure', 'Rc', 'Radius', 'Core Mass Frac Ratio']
#step_size = 5e3
#step_size = 1e4 # Sometimes the step size is larger than the difference between Rc1 and Rc2.

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

# Mercury
#Rp = '2.439e8'
#Mp = '3.302e26'

# Earth
#Rp = '6.3781e8'
earth_radius = '6.3781e8'
#Mp = '5.972e27'
earth_mass = '5.972e27'

def find_min(data_list, inde_index, depe_index, desired_y, expected_core_mass_frac, radius_p, mass_p):
    step_size = 1e4
    print('\nFinding best {} for {} ...\n'.format( variables[inde_index], variables[depe_index] ) )

    #print data_list[2]
    #print type(data_list[2])
    data_list[2] = []    # radius / core_mass_frac_ratio
    data_list[3] = []    # mass

    other_inde_index = int(np.abs(1 - inde_index))

#    if inde_index == 0:
#        other_inde_index = 1
#    elif inde_index == 1:
#        other_inde_index = 0

    for c, i in enumerate( data_list[inde_index] ):
        #print 'c', c
        #print 'i', i
        if inde_index == 0:
            radii_list = str( data_list[other_inde_index][1] )
            #print 'radii_list', radii_list
            #radii_list = core_boundary + str( data_list[other_inde_index][-1] )
            #radii_list = core_boundary + '{0:.10f}'.format( data_list[other_inde_index][-1] )
            pressure = str(i)
            #pressure = '{0:.10f}'.format(i)

        elif inde_index == 1:
            radii_list = str(i)
            #radii_list = str(i)
            #radii_list = core_boundary + '{0:.10f}'.format(i)
            pressure = str( data_list[other_inde_index][1] )
            #pressure = '{0:.10f}'.format( data_list[other_inde_index][-1] )

        final_radius, final_mass, core_mass_frac_ratio = run_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, algorithm, eos, radius_p, mass_p, expected_core_mass_frac)
        #print final_radius, final_mass, core_mass_frac_ratio
        ##################################################
        data_list[2].append(final_radius)        # radius
        ##################################################
        # CHANGE TO FITTING CORE MASS FRAC HERE
        #data_list[2].append(core_mass_frac_ratio) # CMFR
        ##################################################
        #data_list[3].append(final_mass)      # mass
        data_list[3].append(core_mass_frac_ratio) # CMFR
#    print('depe_variable: ', depe_index, ', inde_variable: ', inde_index)

    #print data_list
    while abs( desired_y - data_list[depe_index][1] ) > thresh:
        '''
        if data_list[depe_index][0] - data_list[depe_index][1] == 0:
            print data_list[depe_index][0], data_list[depe_index][1]
            print 'hello'
            #print 'break', data_list
            #break

            if data_list[inde_index][0] > data_list[inde_index][1]:
                larger_variable_index = 0
                smaller_variable_index = 1

            else:
                larger_variable_index = 1
                smaller_variable_index = 0

            if data_list[depe_index][0] < 1:
                data_list[inde_index][larger_variable_index] = 1.1 * data_list[inde_index][larger_variable_index]

                if inde_index == 0:
                    pressure = str( data_list[inde_index][1] )
                    radii_list = str( data_list[other_inde_index][1] )
                elif inde_index == 1:
                    pressure = str( data_list[other_inde_index][1] )
                    radii_list = str( data_list[inde_index][1] )

            elif data_list[depe_index][0] > 1:
                data_list[inde_index][smaller_variable_index] = .9 * data_list[inde_index][smaller_variable_index]

                if inde_index == 0:
                    pressure = str( data_list[inde_index][0] )
                    radii_list = str( data_list[other_inde_index][0] )
                elif inde_index == 1:
                    pressure = str( data_list[other_inde_index][0] )
                    radii_list = str( data_list[inde_index][0] )

            final_radius, final_mass, core_mass_frac_ratio = run_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, algorithm, eos, radius_p, mass_p, expected_core_mass_frac)

            if data_list[depe_index][0] < 1:
                data_list[2][larger_variable_index] = final_radius
                data_list[3][larger_variable_index] = core_mass_frac_ratio

            elif data_list[depe_index][0] > 1:
                data_list[2][smaller_variable_index] = final_radius
                data_list[3][smaller_variable_index] = core_mass_frac_ratio
        '''
        print 'data: ', data_list

        next_inde_guess = lin_inter( data_list[inde_index], data_list[depe_index], desired_y )
        #print type(next_inde_guess)
        print 'next_inde_guess: {0:.10f}'.format(next_inde_guess)
        #print next_inde_guess

        if inde_index == 0:
            radii_list = str( data_list[other_inde_index][1] )
            pressure = str(next_inde_guess)

            final_radius, final_mass, core_mass_frac_ratio = run_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, algorithm, eos, radius_p, mass_p, expected_core_mass_frac )
            print('pressure: {0}, Rc: {1:.0f}, radius: {2}, mass: {3}, CMFR: {4}'.format(next_inde_guess, data_list[other_inde_index][1], final_radius, final_mass, core_mass_frac_ratio))
            #print('pressure: {} Rc: {} core_mass_frac_ratio: {} mass: {}'.format(next_inde_guess, data_list[other_inde_index][-1], core_mass_frac_ratio, final_mass))
            #print core_mass_frac_ratio
        elif inde_index == 1:
            radii_list = str(next_inde_guess)
            pressure = str( data_list[other_inde_index][1] )

            final_radius, final_mass, core_mass_frac_ratio = run_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, algorithm, eos, radius_p, mass_p, expected_core_mass_frac )
            print('pressure: {0}, Rc: {1:.0f}, radius: {2}, mass: {3}, CMFR: {4}'.format(data_list[other_inde_index][1], next_inde_guess, final_radius, final_mass, core_mass_frac_ratio))
            #print('pressure: {} Rc: {} core_mass_frac_ratio: {} mass: {}'.format(data_list[other_inde_index][-1], next_inde_guess, core_mass_frac_ratio, final_mass))

        if abs(desired_y - data_list[depe_index][0]) < abs(desired_y - data_list[depe_index][1]):
            data_list[inde_index] = [ data_list[inde_index][0], next_inde_guess ]
            data_list[2] = [ data_list[2][0], final_radius ]
            data_list[3] = [ data_list[3][0], core_mass_frac_ratio ]

        else:
            data_list[inde_index] = [ data_list[inde_index][1], next_inde_guess ]
            data_list[2] = [ data_list[2][1], final_radius ]
            data_list[3] = [ data_list[3][1], core_mass_frac_ratio ]
        '''
        if abs(desired_y - data_list[depe_index][0]) < abs(desired_y - data_list[depe_index][1]):
            data_list[inde_index] = [ data_list[inde_index][0] ]
            data_list[2] = [ data_list[2][0] ]    # radius
            data_list[3] = [ data_list[3][0] ]    # mass
        else:
            data_list[inde_index] = [ data_list[inde_index][1] ]
            data_list[2] = [ data_list[2][1] ]    # radius
            data_list[3] = [ data_list[3][1] ]    # mass

        data_list[inde_index].append(next_inde_guess)
        ##################################################
        data_list[2].append(final_radius)        # radius
        ##################################################
        # CHANGE TO FITTING CORE MASS FRAC HERE
        #data_list[2].append(core_mass_frac_ratio) # CMFR
        ##################################################
        #data_list[3].append(final_mass)
        data_list[3].append(core_mass_frac_ratio)
        '''
        if np.abs(data[1][0] - data[1][1]) < step_size:
            step_size = 1e3

        #print(abs( 1 - data_list[depe_index][-1] ), thresh)
    #print 'data_list_type', type(data_list)
    #print data_list
    return data_list, final_radius, final_mass, core_mass_frac_ratio


# 0: pressure, 1: Rc, 2: radius, 3: mass
# 0: pressure, 1: Rc, 2: core_mass_frac_ratio, 3: mass

#data_list = [ [400, 390], [3e8, 3.5e8], [], [] ]
#data_list = [ [500, 400], [.6, .7], [], [] ]
#group_list = [ (0, 3), (1, 2) ]  # the usual
# 0: pressure, 1: Rc, 2: radius, 3: core_mass_frac_ratio
group_list = [ (0, 2), (1, 3)]


found_min = False
desired_y = 1.

#expected_core_mass_frac_list = [str(x) for x in np.arange(.2, 1, .2)]
expected_core_mass_frac_list = ['0.295896']
#Mp_list = [str(x) for x in np.arange(1, 20, 1)]
#Mp_list = ['1']
mass_p = earth_mass
#Rp_list = ['.6', '.7', '.8', '2']
#Rp_list = np.arange(.6, 2.1, .1)
#Rp_list = np.arange(.6, 2.1, .01)
Rp_list = [.66]

for expected_core_mass_frac in expected_core_mass_frac_list:
    #for Mp in Mp_list:
    for Rp in Rp_list:
        #mass_p =str(float(Mp)*float(earth_mass))
        radius_p = str(float(Rp)*float(earth_radius))
        #data_list = [ [4000, 5000], [.8, .9], [], [] ]
        #data_list = [ [2000, 2200], [8e8, 9e8], [], [] ]
        data_list = [ [200., 300.], [2e8, 3e8], [], [] ]
        #data_list = [ [282.349805827, 290], [303922081, 403922081], [], [] ]
        #data_list = [ [900, 1000], [2e8, 3e8], [], [] ]
        #data_list = [ [2000, 3000], [2e8, 3e8], [], []]
        while found_min == False:
            #print('data_list[0][0]: ', data_list[0][0])
            for g in group_list:
                data_list, final_radius, final_mass, core_mass_frac_ratio = find_min(data_list, g[0], g[1], desired_y, expected_core_mass_frac, radius_p, mass_p)
            #if data_list[1][0] > 1 or data_list[1][1] > 1:
            #    found_min = True
            #    print 'expected_core_mass_frac: {} Mp: {} core radius larger than 1'.format(expected_core_mass_frac, Mp)

            '''
            print('Finding best pressure for core mass frac:\n')

            pressure_1 = data_list[0][0]
            pressure_2 = data_list[0][1]


            found_best_core_mass_frac = False
            while found_best_core_mass_frac == False:
                #pressure_1 = data_list[0][0]
                #pressure_2 = data_list[0][1]
                #print('pressure_1: ', pressure_1)
                #print('pressure_2: ', pressure_2)
                radii_list = str( data_list[1][1] )
                #radii_list = core_boundary + str( data_list[1][1] )
                #print('radii_list: ', radii_list)

                final_radius_1, final_mass_1, core_mass_frac_ratio_1 = run_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure_1, step_size, algorithm, eos, radius_p, mass_p, expected_core_mass_frac )
                final_radius_2, final_mass_2, core_mass_frac_ratio_2 = run_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure_2, step_size, algorithm, eos, radius_p, mass_p, expected_core_mass_frac )

                #print('CMFR_1: ', core_mass_frac_ratio_1)
                #print('CMFR_2: ', core_mass_frac_ratio_2)

                next_pressure_guess = lin_inter( [pressure_1, pressure_2], [core_mass_frac_ratio_1, core_mass_frac_ratio_2], desired_y )
                #print('next_pressure_guess: ', next_pressure_guess)

                if abs(desired_y - core_mass_frac_ratio_1) < abs(desired_y - core_mass_frac_ratio_2):
                    pressure_2 = next_pressure_guess
                else:
                    pressure_1 = next_pressure_guess

                final_radius, final_mass, core_mass_frac_ratio = run_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, next_pressure_guess, step_size, algorithm, eos, radius_p, mass_p, expected_core_mass_frac )

                print('Pressure: {}, core_mass_frac_ratio: {}'.format(next_pressure_guess, core_mass_frac_ratio))

                if abs(desired_y - core_mass_frac_ratio_1) < thresh or abs(desired_y - core_mass_frac_ratio_2) < thresh:
                    found_best_core_mass_frac = True

            data_list[0][0] = next_pressure_guess
            data_list[2][0] = final_radius
            data_list[3][0] = final_mass
            print('data_list[0][0]: ', data_list[0][0])
            '''

            if abs(desired_y - data_list[2][-1]) < thresh and abs(desired_y - data_list[3][-1]) < thresh:
                found_min = True
                final_mass = float(final_mass) * float(earth_mass)
                #print 'mass: {}'.format(final_mass)
                print 'radius: {} mass: {}'.format(radius_p, final_mass)
                #print 'central pressure: {} core radius: {}'.format(data_list[0][1], data_list[1][1])
                #print 'expected_core_mass_frac: {} Mp: {} radius (in Earth radius): {} mass (in Earth mass): {} core_mass_frac_ratio: {}'.format(expected_core_mass_frac, mass_p, final_radius, final_mass, core_mass_frac_ratio)

        found_min = False
