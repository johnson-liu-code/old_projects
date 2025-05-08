import numpy as np
import matplotlib.pyplot as plt


r1 = np.linspace(0, 4, 1000)
x1 = np.exp( (-r1**2.) / 2. ) / (2*np.pi)**(3./2)
y1 = np.multiply(r1**2., x1)


#with open('psi_3D_harmonic_oscillator.data', 'r') as fil:
with open('psi.data', 'r') as fil:
#with open('test_08_data.txt', 'r') as fil:
    lines = fil.readlines()

#print(lines)

points = [line.split() for line in lines]
points = [ ( float(point[0]), float(point[1]), float(point[2]) ) for point in points]

#print(points)

r, psi, psi_exact = zip(*points)
r = np.array(r)
#print(r)
#print(psi)

plt.plot(r, psi, marker = '+')
#plt.plot(r, np.multiply(r**2., psi), marker = '+', linestyle = 'None' )
#plt.plot(r, np.multiply(r**2., psi_exact))
#plt.plot(r1, y1)
plt.xlabel('r')
plt.ylabel(r'$\psi$')
#plt.ylabel(r'r$^2 \psi$')
plt.grid()
plt.show()
