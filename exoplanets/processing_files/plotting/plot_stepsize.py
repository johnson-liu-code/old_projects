
import argparse
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import ScalarFormatter
from matplotlib.ticker import FormatStrFormatter



parser = argparse.ArgumentParser()
parser.add_argument("file_name1")
parser.add_argument("file_name2")
args = parser.parse_args()


def collect_data(file_name):
    with open(file_name, 'r') as data:
        lines = data.readlines()
        step_size_radius_mass = [ ( float(line.split()[0]), float(line.split()[1]), float(line.split()[2])) for line in lines]
    return step_size_radius_mass

step_size_radius_mass_01 = collect_data(args.file_name1)
step_size_radius_mass_02 = collect_data(args.file_name2)

step_size_01, radius_01, mass_01 = zip(*step_size_radius_mass_01)
step_size_02, radius_02, mass_02 = zip(*step_size_radius_mass_02)

step_size_01 = np.array(step_size_01)/(1.e5)
step_size_02 = np.array(step_size_02)/(1.e5)

radius_01 = np.abs( 1. - np.array(radius_01) )
mass_01 = np.abs( 1. - np.array(mass_01) )

radius_02 = np.abs( 1. - np.array(radius_02) )
mass_02 = np.abs( 1. - np.array(mass_02) )


#print radius

fig, ax = plt.subplots()

ax.ticklabel_format(axis = 'x', style = 'sci', scilimits = (0, 0))
#ax.ticklabel_format(axis = 'y', style = 'sci', scilimits = (0, 0))

plt.scatter(np.log10(step_size_01), np.log10(radius_01), label = 'RK4 Radius')
plt.scatter(np.log10(step_size_02), np.log10(radius_02), label = 'Euler Radius')
plt.scatter(np.log10(step_size_01), np.log(mass_01), label = 'RK4 Mass')
plt.scatter(np.log10(step_size_02), np.log(mass_02), label = 'Euler Mass')

#plt.ticklabel_format(style = 'sci', axis = 'x')

#plt.xticks(rotation=-45)
ax.yaxis.set_major_formatter(FormatStrFormatter('%.2f'))


plt.tick_params(axis = 'both', which = 'major', labelsize = 12)

plt.grid(linestyle = '--')



plt.xlabel('Log$_{10}$ of Step Size (km)', size = 12)
plt.ylabel('Error in\nResult\n' + r'(log$_{10}$ scale)', rotation = 0, labelpad = 42, size = 12)
#plt.ylabel('Final Radius\n(as fraction\nof planet\nradius)', rotation = 0, labelpad = 42, size = 12)
#plt.ylabel('Error in\nFinal Radius\n' + r'(log$_{10}$ scale)', rotation = 0, labelpad = 42, size = 12)
#plt.ylabel('Final Mass\n(as fraction\nof planet\nradius)', rotation = 0, labelpad = 42, size = 12)
#plt.ylabel('Error in\nFinal Mass\n' + r'(log$_{10}$ scale)', rotation = 0, labelpad = 42, size = 12)

plt.legend()
plt.tight_layout()
plt.show()
