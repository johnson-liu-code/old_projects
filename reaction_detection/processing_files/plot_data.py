import pickle
import numpy as np
import matplotlib.pyplot as plt


with open('training_transition.txt', 'rb') as fil:
    training_transition = pickle.load(fil)

with open('training_bond_order.txt', 'rb') as fil:
    training_bond_order = pickle.load(fil)
#with open('training_bond_order_with_noise.txt', 'rb') as fil:
#    training_bond_order_with_noise = pickle.load(fil)

with open('training_bond_dist.txt', 'rb') as fil:
    training_bond_dist = pickle.load(fil)
#with open('training_bond_dist_with_noise.txt', 'rb') as fil:
#    training_bond_dist_with_noise = pickle.load(fil)

with open('sample_transition_01.txt', 'rb') as fil:
    sample_transition = pickle.load(fil)

with open('sample_bond_order_01.txt', 'rb') as fil:
    sample_bond_order = pickle.load(fil)
with open('sample_bond_order_with_noise_01.txt', 'rb') as fil:
    sample_bond_order_with_noise = pickle.load(fil)

with open('sample_bond_dist_01.txt', 'rb') as fil:
    sample_bond_dist = pickle.load(fil)
with open('sample_bond_dist_with_noise_01.txt', 'rb') as fil:
    sample_bond_dist_with_noise = pickle.load(fil)


training_bo_diff = np.abs(training_bond_order[1:] - training_bond_order[:-1])
training_bd_diff = np.abs(training_bond_dist[1:] - training_bond_dist[:-1])

#training_bo_noise_diff = np.abs(training_bond_order_with_noise[1:] - training_bond_order_with_noise[:-1])
#training_bd_noise_diff = np.abs(training_bond_dist_with_noise[1:] - training_bond_dist_with_noise[:-1])

sample_bo_diff = np.abs( sample_bond_order[1:] - sample_bond_order[:-1] )
sample_bd_diff = np.abs( sample_bond_dist[1:] - sample_bond_dist[:-1] )

sample_bo_noise_diff = np.abs( sample_bond_order_with_noise[1:] - sample_bond_order_with_noise[:-1] )
sample_bd_noise_diff = np.abs( sample_bond_dist_with_noise[1:] - sample_bond_dist_with_noise[:-1] )



plt.plot(training_transition, color = 'blue', linewidth = 1, label = 'Fictitious reaction data\n(expected outcome for training)', alpha = 0.5)
#plt.plot(training_bond_order, color = 'orange', linewidth = 1, label = 'Fictitious bond order data (training feature)')
#plt.plot(training_bond_order_with_noise, color = 'orange', linewidth = 1, label = 'Fictitious bond order data with noise (training feature)')

#plt.plot(training_bond_dist, color = 'green', linewidth = 1, label = 'Fictitious bond distance data\n(training feature)')
#plt.plot(training_bond_dist_with_noise, color = 'green', linewidth = 1, label = 'Fictitious bond distance data with noise\n(training feature)')

#plt.plot(training_bo_diff, color = 'orange', linewidth = 1, label = 'Bond order difference')
plt.plot(training_bd_diff, color = 'purple', linewidth = 1, label = 'Bond distance difference')

#plt.plot(training_bo_noise_diff, color = 'red', linewidth = 1, label = 'Abs(BO noise diff)', alpha = 0.8)
#plt.plot(training_bd_noise_diff, color = 'purple', linewidth = 1, label = 'Abs(BD noise diff)')

#plt.plot(sample_transition, linewidth = 1, label = 'sample transition', alpha = 0.4)

#plt.plot(sample_bond_order_with_noise, color = 'red', linewidth = 1, label = 'Sample bond order with noise')
#plt.plot(sample_bond_order, color = 'orange', linewidth = 1, label = 'Sample bond order')

#plt.plot(sample_bond_dist_with_noise, color = 'purple', linewidth = 1, label = 'Sample bond distnace with noise')
#plt.plot(sample_bond_dist, color = 'green', linewidth = 1, label = 'Sample bond distance')

#plt.plot(sample_bo_diff, color = 'orange', linewidth = 1, label = 'Sample bond order difference')
#plt.plot(sample_bd_diff, color = 'green', linewidth = 1, label = 'Sample bond distance difference')
#plt.plot(sample_bo_noise_diff, color = 'red', linewidth = 1, label = 'Sample bond order difference with noise')
#plt.plot(sample_bd_noise_diff, color = 'purple', linewidth = 1, label = 'Sample bond distance difference with noise')

plt.xlabel('Trajectory', size = 14)
#plt.ylabel('Reaction\n(0 or 1)', rotation = 0, labelpad = 30, size = 14)
#plt.ylabel('Bond\nOrder', rotation = 0, labelpad = 30, size = 14)
#plt.ylabel('Bond\nDistance\n(units\nnot shown)', rotation = 0, labelpad = 50, size = 14)
plt.grid(linestyle = '--')
plt.legend(loc = 'upper right', prop = {'size': 14})
#plt.yticks(np.arange(0, 1.1, 1))
#plt.ylim(-.1, 1.4)
#plt.ylim(0, .7)
plt.ylim(0, 1.2)
#plt.ylim(0, 0.8)
#plt.ylim(0.3, 1.2)
plt.tight_layout()
plt.show()
