import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker


with open('test_3D_03.txt', 'r') as fil:
    lines = fil.readlines()
    #energy_lines = [float(line.split()[6]) for line in fil.readlines() if '<E> =' in line]
    N_E_err = [ (float(line.split()[3]), float(line.split()[6]), float(line.split()[8]) ) for line in lines if '<E> =' in line]
    V = [ float(line.split()[4]) for line in lines if '<E^2>' in line]

N, energy, err = zip(*N_E_err)

length = len(energy)

tick_spacing = .5

fig, ax = plt.subplots(1, 1)
ax.plot(energy, label = '<E>')
ax.plot(err, label = 'error')
ax.plot(V, label = 'Variance')
plt.grid(linestyle='--')
plt.legend()
ax.yaxis.set_major_locator(ticker.MultipleLocator(tick_spacing))
plt.xlabel('Trajectory')
plt.title('3D Harmonic Oscillator')
#plt.ylabel('<E>')
#plt.ylabel('N')
#plt.ylabel('Variance')
plt.show()
