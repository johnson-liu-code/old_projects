import numpy as np
import pickle
import matplotlib.pyplot as plt

N = 1000

reaction_list = np.sort( np.random.choice(N, 10, replace = False) )
# print reaction_list

bond_order = []
bond_dist = []
transition = []

switch = 1

for i in range(N):
    if switch == 1:
        bond_order.append( np.random.uniform(.1, .3) )
        bond_dist.append( np.random.uniform(.7, 1) )
    elif switch == -1:
        bond_order.append( np.random.uniform(.4, .7) )
        bond_dist.append( np.random.uniform(.3, .6) )
    if i in reaction_list:
        switch *= -1
        transition.append(1)
    else:
        transition.append(0)

bond_order = np.array(bond_order)
bond_dist = np.array(bond_dist)

bo_diff = np.abs( bond_order[1:] - bond_order[:-1] )
bd_diff = np.abs( bond_dist[1:] - bond_dist[:-1] )

#with open('sample_transition_03.txt', 'wb') as fil:
#    pickle.dump(transition, fil)
#with open('sample_bond_order_03.txt', 'wb') as fil:
#    pickle.dump(bond_order, fil)
#with open('sample_bond_dist_03.txt', 'wb') as fil:
#    pickle.dump(bond_dist, fil)

noise = np.random.normal(0, .1, 1000)
bo_with_noise = bond_order + noise
bo_noise_diff = np.abs( bo_with_noise[1:] - bo_with_noise[:-1] )

bd_with_noise = bond_dist + noise
bd_noise_diff = np.abs( bd_with_noise[1:] - bd_with_noise[:-1] )

#plt.plot(noise, linewidth = 0.5)

#plt.plot(transition, linewidth = 1)

#plt.plot(bond_order, linewidth = 1, label = 'BO')
#plt.plot(bo_with_noise, linewidth = 1, label = 'BO w/ noise', alpha = 0.5)
#plt.plot(bo_diff, linewidth = 1, label = 'BO diff', alpha = 0.8)
#plt.plot(bo_noise_diff, linewidth = 1, label = 'BO w/ noise diff', alpha = 0.6)

#plt.plot(bond_dist, linewidth = 1, label = 'BD')
#plt.plot(bd_with_noise, linewidth = 1, label = 'BD w/ noise', alpha = 0.5)
#plt.plot(bd_diff, linewidth = 1, label = 'BD diff', alpha = 0.8)
#plt.plot(bd_noise_diff, linewidth = 1, label = 'BD w/ noise diff', alpha = 0.6)

#plt.legend()

#plt.show()
'''
with open('training_transition.txt', 'wb') as fil:
    pickle.dump(transition, fil)
with open('training_bond_order.txt', 'wb') as fil:
    pickle.dump(bond_order, fil)
with open('training_bond_order_with_noise.txt', 'wb') as fil:
    pickle.dump(bo_with_noise, fil)
with open('training_bond_dist.txt', 'wb') as fil:
    pickle.dump(bond_dist, fil)
with open('training_bond_dist_with_noise.txt', 'wb') as fil:
    pickle.dump(bd_with_noise, fil)
'''

with open('sample_transition_01.txt', 'wb') as fil:
    pickle.dump(transition, fil)
with open('sample_bond_order_01.txt', 'wb') as fil:
    pickle.dump(bond_order, fil)
with open('sample_bond_order_with_noise_01.txt', 'wb') as fil:
    pickle.dump(bo_with_noise, fil)
with open('sample_bond_dist_01.txt', 'wb') as fil:
    pickle.dump(bond_dist, fil)
with open('sample_bond_dist_with_noise_01.txt', 'wb') as fil:
    pickle.dump(bd_with_noise, fil)

