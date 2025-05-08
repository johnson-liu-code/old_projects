
import argparse
import os
import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt


parser = argparse.ArgumentParser()
parser.add_argument("dir_name")

args = parser.parse_args()

all_points = []
fit1 = []
fit2 = []

for dir in os.listdir(args.dir_name):
    if os.path.isdir(args.dir_name + '/' + dir):
        lattice = dir
        lattice_points = []
        for fil in os.listdir(args.dir_name + '/' + dir):
            if 'out' in fil:
                beta = float(fil[3:-4])
                with open(args.dir_name + '/' + dir + '/' + fil, 'r') as txt:
                    plaq = np.array([float(p.split()[1]) for p in txt.readlines()[100:]])

                lattice_points.append((beta, np.mean(plaq)))
                #if beta < 1 and beta >= 0:
                #    fit1.append((beta, np.mean(plaq)))
                #elif beta > 1:
                #    fit2.append((beta, np.mean(plaq)))

        all_points.append((lattice, lattice_points))


#def fit_1(beta, a):
#    return a*beta
#def fit_2(beta, b, c):
#    return b + c*beta

#beta1, plaq1 = zip(*fit1)
#beta2, plaq2 = zip(*fit2)

#beta1 = np.array(beta1)
#plaq1 = np.array(plaq1)

#beta2 = np.array(beta2)[-6:]
#plaq2 = np.array(plaq2)[-6:]

#init2 = [1., -1.]

#popt1, pcov1 = curve_fit(fit_1, beta1, plaq1)
#popt2, pcov2 = curve_fit(fit_2, beta2, plaq2)

def line(x):
    return x/2.

def lim(x):
    return 1 - .4/x

colors = ['purple', 'blue', 'cyan', 'green']

fig, ax = plt.subplots()

for c, lat in enumerate(all_points):
    beta, plaq = zip(*lat[1])

    plt.scatter(beta, plaq, edgecolor = colors[c], facecolor = 'None', s = 120, label = 'PLAQ vs ' + r'$\beta$' + '\n4x4x4x4')
    #plt.plot(np.linspace(0, 1, 100), fit_1(np.linspace(0, 1, 100), popt1[0]), linewidth = 3, label = str(popt1[0])[:6] + r' * $\beta$')
    #plt.plot(np.linspace(2.5, 5, 100), fit_2(np.linspace(2.5, 5, 100), *popt2), linewidth = 3, label = str(popt2[0])[:6] + ' + ' + str(popt2[1])[:6] + r' * $\beta$')

linerange = np.linspace(0, .9, 100)
limrange = np.linspace(2, 20, 100)

plt.plot(linerange, line(linerange), color = 'blue', linewidth = 2, label = r'$\beta$/2')
plt.plot(limrange, lim(limrange), color = 'green', linewidth = 2, label = r'1 - .4/$\beta$')


ax.grid(which = 'major', color = 'black', linestyle='--')
ax.set_axisbelow(True)
ax.tick_params(which='both', # Options for both major and minor ticks
                top='off', # turn off top ticks
                left='off', # turn off left ticks
                right='off',  # turn off right ticks
                bottom='off') # turn off bottom ticks

plt.xlabel(r'$\beta$', size = 16)
plt.ylabel('PLAQ', rotation = 0, labelpad = 40, size = 16)

plt.legend(loc = 'lower right')

plt.tight_layout()

plt.show()
