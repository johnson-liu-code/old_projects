
import numpy as np
import matplotlib.pyplot as plt

P = 100

vinet_K0 = 156.2
vinet_K0p = 6.08
vinet_rho0 = 8.3

bme_K0 = 162.5
bme_K0p = 5.5
bme_rho0 = 7.86

zeng_K0 = 255
zeng_rho0 = 7.85


def vinet(x):
    return 3*vinet_K0*x**(2./3) * (1. - x**(-1./3)) * np.exp(3./2 * (vinet_K0p - 1.) * (1. - x**(-1./3)))
def bme(x):
    return 3./2 * bme_K0 * (x**(7./3) - x**(5./3)) * (1 + (3./4)*(bme_K0p - 4)*(x**(2./3) - 1) )
def zeng(x):
    return 3./2 * zeng_K0 * (x**(7./3) - x**(5./3))

x = 1.
prev_x = x

change = .1
tresh = .001
found = False

points = []
'''
while found == False:
    if vinet(x) > P:
        x -= change
    else:
        x += change

    points.append((x, vinet(x)))

    if abs(vinet(x) - P) < tresh:
        found = True
        rho = x * vinet_rho0
    else:
        if (vinet(prev_x) > P and vinet(x) < P) or (vinet(prev_x) < P and vinet(x) > P):
            change *= .1
        prev_x = x

x, y = zip(*points)
'''

x_range = np.linspace(1, 2)
y_vinet = vinet(x_range)
y_bme = bme(x_range)
y_zeng = zeng(x_range)

plt.plot(x_range, y_zeng, label = 'Zeng Equation of State')
plt.plot(x_range, y_vinet, label = 'Vinet Equation of State')
plt.plot(x_range, y_bme, label = 'BME Equation of State')
#plt.scatter(x, y)

plt.xlabel('x (unitless)')
plt.ylabel('Pressure\n(GPa)', rotation = 0, labelpad = 40)

plt.grid(linestyle = '--')

plt.legend()
plt.tight_layout()

plt.show()
