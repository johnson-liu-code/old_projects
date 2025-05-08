
import argparse
import numpy as np
import os
import sys
import subprocess

from run_integrator import *


parser = argparse.ArgumentParser()
parser.add_argument("dir_name")
parser.add_argument("num_dir")
parser.add_argument("integrator")
args = parser.parse_args()

#pressure = [str('{0:012.7f}'.format(x)) for x in np.arange(100, 410, 20)]
#core_radius = [str('{0:012.7f}'.format(x)) for x in np.arange(1e6, 1e8, .1e7)]

#pressure = [str('{0:05}'.format(x)) for x in np.arange(1.e1, 2.e2, 2.e1)]
pressure = [str('{0:05}'.format(x)) for x in np.arange(1.e3, 4.5e4, 2.e3)]
core_radius = [str('{0:010}'.format(x)) for x in np.arange(0, 1.e8, 1.e8)]
# core_radius doesn't matter when there's only one layer


print pressure
print core_radius


data_dir = args.dir_name + '/data/' + args.num_dir + '/'

#if os.path.isdir(data_dir):
#    sys.exit("That directory exists!")

#num_layers = '3'
#num_layers = '2'
num_layers = '1'

if num_layers == '3':
    interface_pressure = '330x'
    rho_list = '7.85x7.05x3.98'
    K_list = '255x201x206'

elif num_layers == '2':
    interface_pressure = ''
    # solid iron core
    rho_list = '7.85x3.98'
    K_list = '255x206'
    # liquid iron core
    #rho_list = '7.05x3.98'
    #K_list = '201x206'

elif num_layers == '1':
    interface_pressure = ''
    # rock
    #rho_list = '3.98'
    #K_list = '206'
    # iron
    #rho_list = '7.85'
    #K_list = '255'
    #rho_list = '8.3'
    #K_list = '156.2'
    rho_list = '7.86'
    K_list = '162.5'

step_size = '1e4'

# Mercury
#Rp = '2.439e8'
#Mp = '3.302e26'

# Earth
#Rp = '6.3781e8'
#Mp = '5.972e27'


for pres in pressure:
    pres_dir = data_dir + 'Pi_' + pres + '/'
    if not os.path.isdir(pres_dir):
        os.makedirs(pres_dir)
    for core_r in core_radius:
        core_dir = pres_dir + 'Rc_' + core_r + '/'
        if not os.path.isdir(core_dir):
            os.makedirs(core_dir)

        file_name = core_dir + 'Pi_' + pres + '_Rc_' + core_r + '_.txt'
        print file_name

        radii_list = interface_pressure + core_r

#        final_radius, final_mass = execute_integrator( args.file_name, num_layers, radii_list, rho_list, K_list, pressure, step, Rp, Mp, 'e', '-p')

        #cmd = ['nice', '-n', '10', args.dir_name + '/planet_interior', pres, core_r, '1e4', args.integrator]
        cmd = ['nice', '-n', '10', args.dir_name + '/planet_interior', num_layers, radii_list, rho_list, K_list, pres, step_size, args.integrator, '-p']
        #cmd = ['cpulimit', '-l', '200', './density_integrator_v_001', pres, core_r]

        with open(file_name, 'w') as outfile:
            subprocess.call(cmd, stdout = outfile)
