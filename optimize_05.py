
import pickle
import numpy as np
import matplotlib.pyplot as plt
from NeuralNetwork import *



with open('training_transition.dat', 'rb') as fil:
    transition = pickle.load(fil)

with open('training_bond_order.dat', 'rb') as dat:
    bo = pickle.load(dat)

transition = [ np.minimum(np.abs(t-transition[c-1]), 1) for c, t in enumerate(transition[1:]) ]
transition = np.array(transition[:-1]).reshape(1, len(transition[:-1]))

data = np.array( [ [ np.abs(bo[i] - bo[i-1]) for i, b in enumerate(bo[1:]) ][:-1] ] )

#print(data)
#print(transition)


lvInput = data.reshape(len(data[0]), 1)
# print(data)
lvTarget = transition.reshape(len(transition[0]), 1)
# print(transition)

# lvInput = np.arange(100).reshape(100, 1)
# print(lvInput)

# lvTarget = 


# lvInput =  np.array( [ [0], [1], [2], [3] ] )
# lvTarget = np.array( [ [0], [1], [1], [1] ] )
# print(lvInput)


# lFuncs = [None, TransferFunctions.tanh, TransferFunctions.tanh, TransferFunctions.tanh, TransferFunctions.tanh]
# lFuncs = [None, TransferFunctions.sigmoid, TransferFunctions.sigmoid, TransferFunctions.sigmoid, TransferFunctions.sigmoid]
# lFuncs = [None, TransferFunctions.linear, TransferFunctions.linear, TransferFunctions.linear, TransferFunctions.linear]
# lFuncs = [None, TransferFunctions.gaussian, TransferFunctions.gaussian, TransferFunctions.gaussian, TransferFunctions.gaussian]
# lFuncs = [None, TransferFunctions.sigmoid, TransferFunctions.gaussian, TransferFunctions.sigmoid, TransferFunctions.gaussian]

lFuncs = [None, TransferFunctions.sigmoid, TransferFunctions.sigmoid, TransferFunctions.sigmoid]

bpn = BackPropagationNetwork( (1, 20, 20, 1), lFuncs)
# print(bpn.weights)

# lnMax = 50000
lnMax = 10000
lnErr = 1e-6
for i in range(lnMax+1):
    err = bpn.TrainEpoch(lvInput, lvTarget, momentum = 0.7)
    if i % 1000 == 0 and i > 0:
        print("Iteration {0:6d}K - Error: {1:0.30f}".format(int(i/1000), err))
    if err <= lnErr:
        print("Desired error reached. Iter: {0}".format(i))
        break
    
# Display output

lvOutput = bpn.Run(lvInput)
# for i in range(lvInput.shape[0]):
    # print("Input: {0} Output: {1}".format(lvInput[i], lvOutput[i]))

prediction = lvOutput.reshape(1, len(data[0]))

plt.plot(transition[0])
plt.plot(data[0])
plt.plot(prediction[0])
# 
plt.show()