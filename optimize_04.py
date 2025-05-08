import pickle
import numpy as np
from numpy import linalg as LA
import matplotlib.pyplot as plt




with open('training_transition.dat', 'rb') as fil:
    transition = pickle.load(fil)

with open('training_bond_order.dat', 'rb') as dat:
    bo = pickle.load(dat)
    

transition = [ np.minimum(np.abs(t-transition[c-1]), 1) for c, t in enumerate(transition[1:]) ]
transition = np.array(transition[:-1]).reshape(1, len(transition[:-1]))

#print bo[0][0][1:]
data = np.array([ np.abs(bo[i] - bo[i-1]) for i, b in enumerate(bo[1:]) ][:-1])
#print data
#atom_pair_01 = [o[0][6] for o in data]
#atom_pair_02 = [o[0][9] for o in data]
# avg = np.array( [ [ LA.norm(d) for d in data[1:] ] ] )

# print(data)

len_data = len(data)

def sigmoid(x):
    return 1. / (1. + np.exp(-x))
    
def d_sigmoid(x):
    return sigmoid(x) * (1. - sigmoid(x))
    
def loss_function(x_hat, x):
    return - ( x*np.log(x_hat) + (1-x)*np.log(1 - x_hat) )


ones = np.ones( len_data ).reshape(1, len_data )
# print(data)
# print(ones)
zeros = np.zeros( len_data ).reshape(1, len_data )

a1 = data
a1_ones = np.vstack( (data, ones) )
# print(a1)

w1 = np.random.randn(2, 2)
# w1 = np.random.randn(1, 2)
w2 = np.random.randn(2, 3)
w3 = np.random.randn(1, 3)

run = True
N = 1

for n in range(N):
    z1 = np.dot(w1, a1_ones)
    # print(z1)

    # a2 = np.vstack( (sigmoid(z1), ones) )
    a2 = sigmoid(z1)
    a2_ones = np.vstack( (a2, ones) )
    # print(a2)
    
    z2 = np.dot(w2, a2_ones)
    # print(z2)
    
    # a3 = np.vstack( (sigmoid(z2), ones) )
    a3 = sigmoid(a2)
    a3_ones = np.vstack( (a3, ones) )
    # print(a3)
    
    z4 = np.dot(w3, a3_ones)
    # print(z4)
    
    yhat = sigmoid(z4)
    # print(yhat)
    
    loss = loss_function(yhat, transition)
    total_loss = np.sum(loss) / len_data
    # print('loss: {}'.format(total_loss) )
    
    delta4 = yhat * (1. - yhat) * (yhat - transition)
    # print(delta4)
    
    dsig3 = a3 * (1. - a3)
    dsig3_zeros = np.vstack( (dsig3, zeros) )
    delta3 = dsig3_zeros * np.dot( np.transpose(w3), yhat)
    # print(delta3)
    
    dsig2 = a2 * (1. - a2)
    dsig2_zeros = np.vstack( (dsig2, zeros) )
    delta2 = dsig3_zeros * np.dot( np.transpose(w2), delta3[:-1])
    # print(delta2)
    
    # delta_w1 = 1./len_data * np.dot( a1_ones, np.transpose(delta2[:-1]) )
    # delta_w2 = 1./len_data * np.dot( a2, np.transpose(delta3[:-1]) )
    # print(a3)
    # delta_w3 = np.transpose( 1./len_data * np.dot( a3_ones, np.transpose(delta4) ) )

    # print(delta4)
    # print(np.transpose(a3_ones))
    delta_w3 = 1./len_data * np.dot( delta4, np.transpose(a3_ones) )
    # print(delta3)
    delta_w2 = 1./len_data * np.dot( delta3[:-1], np.transpose(a2_ones) )
    # print(delta2)
    delta_w1 = 1./len_data * np.dot( delta2[:-1], np.transpose(a1_ones) )
    
    # print(w1)
    # print(delta_w1)
    # print(w2)
    # print(delta_w2)
    # print(w3)
    # print(delta_w3)

    w1 = w1 - delta_w1
    w2 = w2 - delta_w2
    w3 = w3 - delta_w3


# print(w1)
# print(w2)
# print(w3)

z1 = np.dot(w1, a1_ones)
# print(z1)

# a2 = np.vstack( (sigmoid(z1), ones) )
a2 = sigmoid(z1)
a2_ones = np.vstack( (a2, ones) )
# print(a2)

z2 = np.dot(w2, a2_ones)
# print(z2)

# a3 = np.vstack( (sigmoid(z2), ones) )
a3 = sigmoid(a2)
a3_ones = np.vstack( (a3, ones) )
# print(a3)

z4 = np.dot(w3, a3_ones)
# print(z4)

yhat = sigmoid(z4)



# plt.plot(transition[0])
# plt.plot(data)
# plt.plot(yhat[0])
# 
# plt.show()