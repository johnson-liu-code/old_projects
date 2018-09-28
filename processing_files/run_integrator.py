from subprocess import Popen, PIPE


# radii must be given as actual values, not fractions
def run_integrator(file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, algorithm, eos, Rp, Mp, expected_core_mass_frac):
#    print file_name
#    print num_layers
#    print radii_list
#    print rho_list
#    print K_list
#    print pressure
#    print step_size
#    print Rp
#    print Mp
#    print algorithm

    process = Popen(["./" + file_name, num_layers, radii_list, rho_list, K_list, str(pressure), str(step_size), algorithm, eos, Rp, Mp, expected_core_mass_frac ], stdout = PIPE)
    (output, err) = process.communicate()

    #final_radius = output.splitlines()[-1].split()[1]
    #final_mass = output.splitlines()[-1].split()[7]
    #core_mass = output.splitlines()[-1].split()[9]

    radius = output.splitlines()[-1].split()[1]
    mass_ratio = output.splitlines()[-1].split()[3]
    core_mass_frac_ratio = output.splitlines()[-1].split()[5]

    #return float(final_radius), float(final_mass)

    return float(radius), float(mass_ratio), float(core_mass_frac_ratio)
