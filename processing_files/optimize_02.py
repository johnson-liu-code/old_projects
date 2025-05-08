import argparse
import pickle
import numpy as np
import matplotlib.pyplot as plt


parser = argparse.ArgumentParser()
parser.add_argument('training_dir')
parser.add_argument('sample_dir')
args = parser.parse_args()



def sigmoid(x):
    return 1. / (1. + np.exp(-x))

def d_sigmoid(x):
    return np.exp(-x) / (1. + np.exp(-x))**2.

def loss_function(c_x, e_x):
    return -(e_x * np.log(c_x) + (1-e_x)*np.log(1-c_x))


#def sweep(num_training, transition, bo_diff, bd_diff, weights):
#


dir = '/home/jliu/Desktop/files/research/reaction_detection/fictious_data/'

with open(dir + args.training_dir + '/sample_transition.txt', 'rb') as fil:
    training_transition = pickle.load(fil)
with open(dir + args.training_dir + '/sample_bond_order.txt', 'rb') as fil:
    training_bo = pickle.load(fil)
with open(dir + args.training_dir + '/sample_bond_dist.txt', 'rb') as fil:
    training_bd = pickle.load(fil)

with open(dir + args.sample_dir + '/sample_bond_order.txt', 'rb') as fil:
    sample_bo_noise = pickle.load(fil)
with open(dir + args.sample_dir + '/sample_bond_dist.txt', 'rb') as fil:
    sample_bd_noise = pickle.load(fil)
with open(dir + args.sample_dir + '/sample_transition.txt', 'rb') as fil:
    sample_transition = pickle.load(fil)

training_transition = training_transition[:-1]
training_transition = np.array(training_transition).reshape(1, len(training_transition))
training_bo_diff = np.abs( training_bo[1:] - training_bo[:-1] )
training_bd_diff = np.abs( training_bd[1:] - training_bd[:-1] )

training_bo_diff = np.array(training_bo_diff).reshape(1, len(training_bo_diff))
training_bd_diff = np.array(training_bd_diff).reshape(1, len(training_bd_diff))

sample_bo_diff = np.abs( sample_bo_noise[1:] - sample_bo_noise[:-1] )
sample_bd_diff = np.abs( sample_bd_noise[1:] - sample_bd_noise[:-1] )

#sample_bo_diff = np.array(sample_bo_diff).reshape(1, len(sample_bo_diff))
#sample_bd_diff = np.array(sample_bd_diff).reshape(1, len(sample_bd_diff))

a1 = np.vstack( (training_bo_diff, training_bd_diff) )

w1 = np.random.randn(3, 2)
b1 = np.random.randn(3, 1)
w2 = np.random.randn(1, 3)
b2 = np.random.randn(1, 1)

#print w1
#print b1
#print w2
#print b2

num_training = len(training_transition[0])

N = 10000

thresh = 1.e-2
total_loss = 1

for i in range(N):
#while total_loss > thresh:
    z1 = np.dot(w1, a1) + b1
    a2 = sigmoid(z1)
    z2 = np.dot(w2, a2) + b2
    y = sigmoid(z2)

    h = (-training_transition / y) + ( (1-training_transition) / (1-y) ) * d_sigmoid(z2)

    idn = np.diag( np.ones(4) )
    ones = np.ones(num_training).reshape(1, num_training)
    a2_ones = np.vstack( (a2, ones) )

    grad_L_2 = h * np.dot(idn, a2_ones)

    grad_L_11 = h * w2[0][0] * d_sigmoid(z1[0]) * np.vstack( (a1, ones)) # this is wrong!, we need the derivative of the sigmoid function
    grad_L_12 = h * w2[0][1] * d_sigmoid(z1[1]) * np.vstack( (a1, ones))
    grad_L_13 = h * w2[0][2] * d_sigmoid(z1[2]) * np.vstack( (a1, ones))

    w1_11 = w1[0][0] - np.sum(grad_L_11[0]) / float(num_training)
    w1_12 = w1[0][1] - np.sum(grad_L_11[1]) / float(num_training)
    b1_1 = b1[0][0] - np.sum(grad_L_11[2]) / float(num_training)

    w1_21 = w1[1][0] - np.sum(grad_L_12[0]) / float(num_training)
    w1_22 = w1[1][1] - np.sum(grad_L_12[1]) / float(num_training)
    b1_2 = b1[1][0] - np.sum(grad_L_12[2]) / float(num_training)

    w1_31 = w1[2][0] - np.sum(grad_L_13[0]) / float(num_training)
    w1_32 = w1[2][1] - np.sum(grad_L_13[1]) / float(num_training)
    b1_3 = b1[2][0] - np.sum(grad_L_13[2]) / float(num_training)

    w2_1 = w2[0][0] - np.sum(grad_L_2[0]) / float(num_training)
    w2_2 = w2[0][1] - np.sum(grad_L_2[1]) / float(num_training)
    w2_3 = w2[0][2] - np.sum(grad_L_2[2]) / float(num_training)
    b2 = b2[0][0] - np.sum(grad_L_2[3]) / float(num_training)

    w1 = np.array( [[w1_11, w1_12], [w1_21, w1_22], [w1_31, w1_32]] )
    b1 = np.array( [[b1_1], [b1_2], [b1_3]] )
    w2 = np.array( [[w2_1, w2_2, w2_3]] )
    b2 = np.array( [[b2]] )

    loss = loss_function(y, training_transition)
    total_loss = np.sum(loss) / float(num_training)
    print total_loss

#print w1
#print b1
#print w2
#print b2


a1 = np.vstack( (sample_bo_diff, sample_bd_diff) )
z1 = np.dot(w1, a1) + b1
a2 = sigmoid(z1)
z2 = np.dot(w2, a2) + b2
y = sigmoid(z2)

#print y

plt.plot(training_transition[0], label = 'Training Reaction Set')
plt.plot(y[0], alpha = 0.8, label = 'Prediction from Neural Network')
#plt.plot(sample_bo_diff, alpha = 0.6, label = 'BO diff')
#plt.plot(sample_bd_diff, alpha = 0.6, label = 'BD diff')

#plt.plot(sample_transition)
#plt.plot(y[0], alpha = 0.5)
plt.xlabel('Trajectory', size = 14)
plt.yticks(np.arange(0, 1.1, 1))
plt.ylim(0, 1.2)
plt.grid(linestyle = '--')

plt.legend()
plt.tight_layout()

plt.show()
