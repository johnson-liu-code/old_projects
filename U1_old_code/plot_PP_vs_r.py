


import sys
import argparse
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit


parser = argparse.ArgumentParser()
parser.add_argument("file_name")
parser.add_argument("-s", "--save", action = "store_true")

args = parser.parse_args()

radius = 6

with open(args.file_name, 'r') as fil:
    lines = fil.readlines()
    PP_list = [(float(l.split()[1]), float(l.split()[2]), float(l.split()[3])) for l in lines if 'P0P*' in l and float(l.split()[1]) <= radius]

    found_beta = False
    found_lattice = False
    found_trajecs = False
    found_meas = False

    for line in lines:
        if  line.split()[0] == 'Beta:':
            beta = line.split()[1]
            found_beta = True
        if line.split()[0] == 'Lattice:':
            lattice = line.split()[1]
            found_lattice = True
        if  line.split()[0] == 'Trajecs:':
            trajecs = line.split()[1]
            found_beta = True
        if line.split()[0] == 'Meas:':
            meas = line.split()[1]
            found_lattice = True

        if found_beta == True and found_lattice == True and found_trajecs == True and found_meas == True:
            break

#print beta
#print lattice

values = set(map(lambda x:x[0], PP_list))

#for v in values:
#    print v

sorted_PP = [[y for y in PP_list if y[0] == x] for x in values]
print len(sorted_PP[0])

points = []

for c, v in enumerate(values):
    mean = np.mean([s[1] for s in sorted_PP[c]]) # Re(P0P*)
    std = np.std([s[1] for s in sorted_PP[c]])   # err in Re(P0P*)
    points.append((v, mean, std))

selected_points = [p for p in points if p[1] > 0]

r, PP, std = zip(*sorted(selected_points[1:]))

#print PP

xrange = np.linspace(min(r), max(r), 100)

lnPP = -np.log(np.array(PP))

def fit(x, a, b):
    return a*float(beta)*x**-1 + b


print r
print lnPP

popt, pcov = curve_fit(fit, np.array(r), lnPP)
#print popt

a = popt[0]
b = popt[1]


fig, ax = plt.subplots()

plt.scatter(r, lnPP, edgecolor = 'purple', facecolor = 'None', s = 100, label = 'Beta: ' + beta + ', Lattice: ' + lattice + '\nTrajecs: ' + trajecs + ', Meas: ' + meas + '\n\n-ln(Re PP*) = a*Beta/r + b\na = ' + str(a) + '\nb = ' + str(b))
#plt.errorbar(r, lnPP, yerr = std, color = 'purple', fmt = 'None')
plt.plot(xrange, a * float(beta) * xrange**-1. + b)

plt.xlabel('r', size = 16)
plt.ylabel('-ln(Re PP*)', rotation = 0, labelpad = 40, size = 16)

#plt.ylim(.3, 6)


ax.grid(which = 'major', color = 'black', linestyle='--')
ax.set_axisbelow(True)
ax.tick_params(which='both', # Options for both major and minor ticks
                top='off', # turn off top ticks
                left='off', # turn off left ticks
                right='off',  # turn off right ticks
                bottom='off') # turn off bottom ticks


plt.legend(loc = 'lower right', prop = {'size' : 12})

plt.tight_layout()


if args.save == True:
    plt_dir = 'L12x12x12x12_plots/'
    save_fig_name = plt_dir + args.file_name.split('/')[-1].split('.txt')[0] + '_ln_PP_plot.png'

    plt.savefig(save_fig_name)

else:
    plt.show()
