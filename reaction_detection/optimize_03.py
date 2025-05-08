
import argparse
import pickle
import numpy as np
from numpy import linalg as LA
import matplotlib.pyplot as plt


# Single hidden layer, N nodes


# parser = argparse.ArgumentParser()
# parser.add_argument('file_name')
# args = parser.parse_args()



training_file_name = 'training_transition.dat'
# training_bo_name = 'training_bond_order.dat'

# training_bo_name = 'sample_bond_order_with_noise_01.dat'
training_bo_name = 'training_bond_order.dat'

#with open('timeseries_1.0.data', 'rb') as fil:
with open(training_file_name, 'rb') as fil:
    transition = pickle.load(fil)[:-1]
with open(training_bo_name, 'rb') as fil:
    bo = pickle.load(fil)

#print bo
transition = [ np.minimum(np.abs(t-transition[c-1]), 1) for c, t in enumerate(transition[1:]) ]
transition = np.array(transition).reshape(1, len(transition))

#print bo[0][0][1:]
data = np.array( [ [ np.abs(bo[i] - bo[i-1]) for i, b in enumerate(bo[1:]) ][:-1] ] )
#print data
#atom_pair_01 = [o[0][6] for o in data]
#atom_pair_02 = [o[0][9] for o in data]
# avg = np.array( [ [ LA.norm(d) for d in data[1:] ] ] )

def sigmoid(x):
    return 1. / (1. + np.exp(-x))

def d_sigmoid(x):
    # return np.exp(-x) / (1. + np.exp(-x))**2.
    return sigmoid(x) * (1. - sigmoid(x))

def loss_function(x_hat, x):
    return - ( x*np.log(x_hat) + (1-x)*np.log(1 - x_hat) )

def tanh(x):
    return np.tanh(x)
    
def d_tanh(x):
    return 1.0 - np.tanh(x)**2



nodes = 10


w1 = np.random.randn(nodes, 1)
#print w1
b1 = np.random.randn(nodes, 1)
w2 = np.random.randn(1, nodes)
#print('w2', w2)
b2 = np.random.randn(1, 1)
#print b2

num_training = len(transition[0])

N = 10000
alpha = 2.

thresh = 1.e-3
total_loss = 1


for i in range(N):
# while total_loss > thresh:
    z1 = np.dot(w1, data) + b1
    #print('z1', z1)
    a2 = tanh(z1)
    #print('a2', a2)
    z2 = np.dot(w2, a2) + b2
    #print('w2', w2)
    #print('z2', z2)

    y = sigmoid(z2)
    #print('y', y)
    h = ( (-transition / y) + (1.-transition) / (1.-y) ) * ( (np.exp(-z2)) / (1. + np.exp(-z2))**2. )
    #print('h', h)
    #print h_stack
    #print('a2', a2)
    dw2 = h * a2
    #print('dw2', dw2)
    db2 = h
    #print db2

    db1 = h * w1 * d_sigmoid(z1)
    #print('db1', db1)
    dw1 = db1 * np.tile(data, (nodes, 1))
    #print('dw1', dw1)
    #print np.sum(dw1, axis = 1).reshape(3, 1)
    w1 = w1 - alpha * np.sum(dw1, axis = 1).reshape(nodes, 1) / num_training
    b1 = b1 - alpha * np.sum(db1, axis = 1).reshape(nodes, 1) / num_training
    #print('w2', w2)
    #print np.sum(dw2, axis = 1).reshape(1, 3)
    w2 = w2 - alpha * np.sum(dw2, axis = 1).reshape(1, nodes) / num_training
    #print('w2', w2)
    b2 = b2 - alpha * np.sum(db2) / num_training
    #print np.sum(db2) / num_training
    #print('b2', b2)

    loss = loss_function(y, transition)
    total_loss = np.sum(loss) / num_training

    # print(total_loss)


sample_bo_name = 'sample_bond_order_with_noise_01.dat'
with open(sample_bo_name, 'rb') as fil:
    sample_bo = pickle.load(fil)

sample_data = np.array( [ [ np.abs(sample_bo[i] - sample_bo[i-1]) for i, b in enumerate(sample_bo[1:]) ][:-1] ] )



pz1 = np.dot(w1, sample_data) + b1
#print('pz1', z1)
pa2 = tanh(pz1)
#print('pa2', pa2)
pz2 = np.dot(w2, pa2) + b2
#print('w2', w2)
#print('pz2', pz2)
predicted = sigmoid(pz2)
#print('predicted', predicted)
#print predicted.shape
predicted = predicted.tolist()[0]

transition = transition.tolist()[0]

fig = plt.figure()

# plt.plot(sample_data[0])

plt.plot(transition, alpha = 0.2, label = 'transition')
plt.plot(predicted, alpha = 0.7, label = 'prediction')

# plt.plot(sample_data[0], label = 'data')


#plt.plot(avg)
#plt.plot(atom_pair_01)
#plt.plot(atom_pair_02)
#plt.plot(normalized_transition, alpha = 0.8)
plt.legend()
#plt.savefig('test.png', dpi = fig.dpi)
plt.show()
