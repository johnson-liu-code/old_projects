
import argparse

from run_integrator import *
from linear_interpolater import *

parser = argparse.ArgumentParser()
parser.add_argument("file_name")
args = parser.parse_args()

algorithm = 'r'
eos = 'z'

Rp = '6.3781e8'
#Rp = '1e9'
Mp = '5.972e27'

#Rp = '1e9'
#Mp = '1e27'

# solid iron core
rho_list = '7.85x3.98'
K_list = '255x206'
expected_core_mass_frac = 0.295896

# liquid iron core
#rho_list = '7.05x3.98'
#K_list = '201x206'
#expected_core_mass_frac = 0.247954


num_layers = '2'
step_size = '1e4'
#radii_list = '.4783'
#pressure = '344.89'
#pressure = '500'


#change = .1
thresh = 1e-4
done = False

#print 'num_layers', num_layers
#print 'rho_list', rho_list
#print 'K_list', K_list
#print 'step_size', step_size
#print 'alogrithm', algorithm
#print 'eos', eos
#print 'Rp', Rp
#print 'Mp', Mp

'''
prev_change = 0

while done == False:
    print ('radius: ', radii_list)
    frac_radius, frac_mass, core_mass_frac = run_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, algorithm, eos, Rp, Mp)
    if abs(core_mass_frac - expected_core_mass_frac ) > thresh:
        print ('core_mass_frac', core_mass_frac)
        #print ('diff: ', abs(core_mass_frac - expected_core_mass_frac) )
        if core_mass_frac > expected_core_mass_frac:
            radii_list = str(float(radii_list) + change)
            this_change = 1
        else:
            radii_list = str(float(radii_list) - change)
            this_change = -1
        if this_change == -prev_change:
            change = .1*change
        prev_change = this_change
    else:
       done = True
'''

#pressure_list = [str(p) for p in np.linspace(1000, 9000, 11)]
#pressure_list = [str(p) for p in np.linspace(1000, 2000, 11)]
#pressure_list = [str(p) for p in np.linspace(100, 900, 9)]

pressure_list = ['9000', '10000']
#pressure_list = ['50', '100', '250']
#pressure_list = ['400', '500', '600', '700', '800', '900']
#pressure_list = ['10']

radii_list_list = ['.2', '.3', '.4']

print pressure_list

#for pressure in list(reversed(pressure_list)):
for pressure in pressure_list:
    #print pressure

    done = False
    unstable = False
    radii_found = False

    for i in radii_list_list[0:-1]:
        print i

    #radii_list = '.2'


    data_list = [ [], [] ]
    data_list[0].append(float(radii_list))

    frac_radius, frac_mass, core_mass_frac = run_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, algorithm, eos, Rp, Mp, str(expected_core_mass_frac) )
    data_list[1].append(core_mass_frac)

    #radii_list = str(float(radii_list) - .025 )
    radii_list = '.3'

    data_list[0].append(float(radii_list))
    frac_radius, frac_mass, core_mass_frac = run_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, algorithm, eos, Rp, Mp, str(expected_core_mass_frac) )
    data_list[1].append(core_mass_frac)

    print 'data_list_0: ', data_list[0]
    print 'data_list_1: ', data_list[1]

    #print ('core_radius: ', data_list[0])
    #print ('core_mass_frac: ', data_list[1])

    while done == False:
        print 'data_list_0: ', data_list[0]
        print 'data_list_1: ', data_list[1]

        next_radii_guess = str(lin_inter(data_list[0], data_list[1], expected_core_mass_frac ))
        #print 'next guess: ', next_radii_guess

        frac_radius, frac_mass, core_mass_frac = run_integrator( args.file_name, num_layers, next_radii_guess, rho_list, K_list, pressure, step_size, algorithm, eos, Rp, Mp, str( expected_core_mass_frac) )
        #print core_mass_frac

        if abs( core_mass_frac - data_list[1][0] ) < abs( core_mass_frac - data_list[1][1]):
            data_list[0][1] = float(next_radii_guess)
            data_list[1][1] = core_mass_frac
        else:
            data_list[0][0] = float(next_radii_guess)
            data_list[1][0] = core_mass_frac

        #print ('core_radius: ', data_list[0])
        #print ('core_mass_frac: ', data_list[1])

        if abs( core_mass_frac - expected_core_mass_frac ) < thresh:
            done = True

        if data_list[1][0] == data_list[1][1]:
            done = True
            unstable = True


        #radius = frac_radius * float(Rp)
        #mass = frac_mass * float(Mp)

    if unstable == False:
        print ('pressure: {} mass: {} radius: {} core_mass_frac: {}'.format(pressure, frac_mass, frac_radius, core_mass_frac))
    else:
        print ('pressure: {} unstable'.format(pressure))
