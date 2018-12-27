

import sys
import numpy as np
from scipy.stats import gaussian_kde
import matplotlib.pyplot as plt




file_name = sys.argv[1]


with open(file_name, 'r') as data:
    beta = file_name[-7:-4]
    lines = data.readlines()
    points = [(float(l.split()[2]), float(l.split()[3])) for l in lines[5:] if 'POLY' in l]


real, imag = zip(*points)

real = np.array(real[100:])
imag = np.array(imag[100:])

xy = np.vstack([real, imag])
z = gaussian_kde(xy)(xy)
idx = z.argsort()
x, y, z = real[idx], imag[idx], z[idx]

fig, ax = plt.subplots()

#plt.plot(real, imag, color = 'purple', marker = "+", linestyle = 'None', label = r'$\beta$ = ' + str(beta))
ax.scatter(x, y, c = z, s = 50, edgecolor = '', marker = "+", label = "Im(P) vs Re(P)\n" + r"$\beta$ = " + beta)

plt.xlabel('Re(P)', size = 16)
plt.ylabel('Im(P)', rotation = 0, labelpad = 40, size = 16)


ax.grid(which = 'major', color = 'black', linestyle='--')
ax.set_axisbelow(True)
ax.tick_params(which='both', # Options for both major and minor ticks
                top='off', # turn off top ticks
                left='off', # turn off left ticks
                right='off',  # turn off right ticks
                bottom='off') # turn off bottom ticks

plt.legend(loc = 'upper right', prop = {'size' : 12})

plt.gca().set_aspect('equal', adjustable='box')

plt.tight_layout()


plt.show()
