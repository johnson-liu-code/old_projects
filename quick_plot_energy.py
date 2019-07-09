import matplotlib.pyplot as plt


with open('energy_vs_time_1000_walkers.txt', 'r') as fil:
    energy = [float(line) for line in fil.readlines()]

plt.plot(energy)
plt.xlabel('Trajectory')
plt.ylabel('Energy')
plt.title('1000 initial walkers')
plt.grid()
plt.show()
