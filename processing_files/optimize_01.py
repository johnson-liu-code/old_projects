import pickle
import numpy as np
import matplotlib.pyplot as plt


with open('training_transition.txt', 'rb') as fil:
    training_transition = pickle.load(fil)

with open('training_bond_order.txt', 'rb') as fil:
    training_bond_order = pickle.load(fil)
with open('training_bond_dist.txt', 'rb') as fil:
    training_bond_dist = pickle.load(fil)

#with open('training_bond_order_with_noise.txt', 'rb') as fil:
#    training_bond_order_with_noise = pickle.load(fil)
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

'''
#print training_transition.index(1)
print training_transition[166]
print training_bond_order[165]
print training_bond_order[166]
print training_bond_order[167]
print training_bond_dist_with_noise[165]
print training_bond_dist_with_noise[166]
print training_bond_dist_with_noise[167]
'''

training_bo_diff = np.abs( training_bond_order[1:] - training_bond_order[:-1] )
training_bd_diff = np.abs( training_bond_dist[1:] - training_bond_dist[:-1] )

#training_bo_noise_diff = np.abs( training_bond_order_with_noise[1:] - training_bond_order_with_noise[:-1] )
#training_bd_noise_diff = np.abs( training_bond_dist_with_noise[1:] - training_bond_dist_with_noise[:-1] )

#print len(training_transition[:-1])
#print len(bo_diff)

def sweep(num_training, training_transition, bo, bd, weights):
    total_grad = np.array( [[0, 0, 0]] ).T

    for c, trans in enumerate(training_transition[:-1]):
        y = trans
        a = weights[0]*bo[c] + weights[1]*bd[c] + weights[2]
        vec = np.array( [ [bo[c], bd[c], 1] ] ).T
        #print np.dot( np.identity(3), vec )
        grad = 2*(a-y) * np.dot( np.identity(3), vec )
        #print grad
        total_grad = total_grad + grad

    change = - total_grad / num_training
    weights = weights + change

    return weights

def cost(num_training, transition, bo_diff, bd_diff, weights):
    a = weights[0]*bo_diff + weights[1]*bd_diff + weights[2]
    total_cost = (a - transition[:-1])**2.
    #return sum(total_cost) / num_training
    return sum(total_cost)/num_training

num_training = len(training_transition[:-1])
#weights = np.random.uniform(-1, 1, 3)
weights = np.array( [[1.e-2, 1.e-2, 1.e-2]] ).T
#weights = np.array( [[0.86938917, 0.53726666, -0.07022231]] ).T
#print weights


N = 100
C = 100

#for n in range(N):
while C > 2e-3:
    weights = sweep(num_training, training_transition, training_bo_diff, training_bd_diff, weights)
    #print weights
    C = cost(num_training, training_transition, training_bo_diff, training_bd_diff, weights)
    print C


print weights

sample_bo_diff = np.abs( sample_bond_order[1:] - sample_bond_order[:-1] )
sample_bd_diff = np.abs( sample_bond_dist[1:] - sample_bond_dist[:-1] )

sample_bo_noise_diff = np.abs( sample_bond_order_with_noise[1:] - sample_bond_order_with_noise[:-1] )
sample_bd_noise_diff = np.abs( sample_bond_dist_with_noise[1:] - sample_bond_dist_with_noise[:-1] )

sample_predicted = weights[0]*sample_bo_diff + weights[1]*sample_bd_diff + weights[2]
sample_noise_predicted = weights[0]*sample_bo_noise_diff + weights[1]*sample_bd_noise_diff + weights[2]

with open('sample_predicted_01.txt', 'wb') as fil:
    pickle.dump(sample_predicted, fil)

plt.plot(sample_transition, color = 'blue', label = 'Sample transition', alpha = 0.4)
plt.plot(sample_predicted, color = 'cyan', label = 'Sample predicted')

#plt.plot(sample_noise_predicted, label = 'Sample predicted with noise')
#plt.plot(sample_bo_diff, label = 'sample bo diff')
#plt.plot(sample_bd_diff, label = 'sample bd diff')
#plt.plot(sample_bo_noise_diff, label = 'sample bo noise diff', alpha = 0.6)
#plt.plot(sample_bd_noise_diff, label = 'sample bd noise diff')
plt.xlabel('Trajectory', size = 14)
plt.yticks(np.arange(0, 1.1, 1))
plt.ylim(0, 1.2)
plt.grid(linestyle = '--')
plt.legend(loc = 'upper right', prop = {'size': 14})
plt.show()
