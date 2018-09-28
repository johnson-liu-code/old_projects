

import numpy as np
import matplotlib.pyplot as plt

def func(x):
    return x**(7./3) - x**(5./3)

#x_range = np.linspace(0, 2, 100)
x_range = np.linspace(1, 5, 100)
y = func(x_range)

y7 = x_range**(7./3)
y3 = x_range**(5./3)

log_x = np.log10(x_range)
#print log_x
log_y = np.log10(y)

a = .4

#print x_range.T
#print y.T
#print log_y.T

ar = np.hstack( (x_range.reshape(len(x_range), 1), y.reshape(len(x_range), 1), log_y.reshape(len(x_range), 1)) )
#print ar

fig, ax = plt.subplots()

ax.ticklabel_format(axis = 'x', style = 'sci', scilimits = (0, 0))

plt.plot(x_range, y7, label = r'$y = x^{7/3}$')
plt.plot(x_range, y3, label = r'$y = x^{5/3}$')
plt.plot(x_range, y, label = r'$y = x^{7/3} - x^{5/3}$')
plt.plot(x_range, np.log10(x_range), label = r'$y = \log(x)$')

#plt.plot(log_x, log_y, label = r'log($a$) = log($x^{7/3} - x^{5/3}$)')

#plt.plot( [x_range[0], x_range[-1]], [a, a], label = '$a = 0.4$')

#plt.xlabel('log(x) (unitless)')
#plt.ylabel('log(a)\n(unitless)', rotation = 0, labelpad = 30)
plt.xlabel('x')
plt.ylabel('y', rotation = 0, labelpad = 20)

#ax.set_xscale('log')
ax.set_yscale('log')

plt.grid(True, which = 'both', linestyle = '--')
#plt.xlim(x_range[0], x_range[-1])

plt.legend()

plt.tight_layout()

plt.show()
