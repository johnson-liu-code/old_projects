
import numpy as np
import matplotlib.pyplot as plt

'''
p3 = -2.81361e-05
p2 = 0.00413289
p1 = 0.00829398
r3 = 6.6729e+08
r2 = 6.6728e+08
r1 = 6.6727e+08
'''

p3 = -0.00102085
p2 = 0.000298368
p1 = 0.00161763
r3 = 1.14064e+08
r2 = 1.14048e+08
r1 = 1.14032e+08

r = [r1, r2, r3]
p = [p1, p2, p3]

#a1 = 448.11
#a2 = -9.25654e-07
#a3 = 3.80819e-16

a1 = 10.3828
a2 = -9.96226e-08
a3 = 7.52861e-17

a = [a1, a2, a3]

#final_radius = 667289931.8
final_radius = 1.14052e+08

x = np.linspace(r1, r3, 100)

def func(a, x):
    return a[0] + a[1]*x + a[2]*x**2.

final_pressure = func(a, final_radius)

plt.scatter(r, p, color = 'red', label = 'Simulated Pressure')
plt.plot(x, func(a, x), label = 'Interpolation')
plt.scatter(final_radius, final_pressure, color = 'green', label = 'Final Pressure\nand Radius')

plt.xlabel('Radius (cm)', size = 14)
plt.ylabel('Pressure\n(GPa)', rotation = 0, labelpad = 30, size = 14)

plt.grid(linestyle = '--')

plt.legend()

plt.tight_layout()

plt.show()
