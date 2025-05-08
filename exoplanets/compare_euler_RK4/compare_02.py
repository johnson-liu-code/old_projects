
import numpy as np


dt = .02
t = np.arange(0, 2.+dt, dt)
x = np.exp(.5*t**2)

length = len(t)
x_rk4 = np.zeros(length)
x_rk4[0] = 1.

for c in range(1, length):
    k1 = x_rk4[c-1] * t[c-1] * dt
    k2 = (x_rk4[c-1] + k1/2.) * (t[c-1] + dt/2.) * dt
    k3 = (x_rk4[c-1] + k2/2.) * (t[c-1] + dt/2.) * dt
    k4 = (x_rk4[c-1] + k3) * t[c-1] * dt

    k = (1./6) * (k1 + 2.*k2 + 2.*k3 + k4)

    x_rk4[c] = x_rk4[c-1] + k

x_diff_rk4 = x - x_rk4
for c in range(length):
   print('{}   {:.12f}   {:.12f}  {:.12f}'.format(t[c], x[c], x_rk4[c], x_diff_rk4[c] ) )
