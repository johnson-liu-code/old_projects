from subprocess import Popen, PIPE


def run_integrator(file_name, num_layers, radii_list, rho_list, K_list, pressure, step_size, algorithm):
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

    process = Popen(["./" + file_name, num_layers, radii_list, rho_list, K_list, str(pressure), str(step_size), algorithm, eos ], stdout = PIPE)
    (output, err) = process.communicate()

    frac_mass_frac_iron = output.splitlines()[-1].split()[1]

    return float(frac_mass_frac_iron)
