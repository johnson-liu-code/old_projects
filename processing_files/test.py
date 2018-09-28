
import sys
from run_integrator import *


file_name = sys.argv[1]

final_radius, final_mass, core_mass = run_integrator( file_name, '2', '1.64882569683e8', '7.85x3.98', '255x206', '40.1436514877', '1e4', 'r', 'z')

print(final_radius, final_mass, core_mass)
