
import os
import pickle
import numpy as np
from sklearn.neural_network import MLPClassifier
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable
import pprint


#X = [ [0., 0.], [1., 1.], [2., 2.]]
#y = [0, 1, 2]
#clf = MLPClassifier(solver='lbfgs', alpha=1e-5,
#                     hidden_layer_sizes=(5, 2), random_state=1)

#clf.fit(X, y)

#print( clf.predict([[2., 2.], [-1., -2.]]) )


with open('timeseries_1.0.data', 'rb') as fil:
    transition = pickle.load(fil)
with open('bo_opt.dat', 'rb') as fil:
    bo_training = np.array( pickle.load(fil) )[:-1]
with open('bo.dat', 'rb') as fil:
    bo_sample = pickle.load(fil)[:-1]

#print len(transition)

transition = [ np.minimum(np.abs(t-transition[c-1]), 1) for c, t in enumerate(transition[1:]) ]
#print len(transition)
transition = np.array(transition).reshape(len(transition), )

#print len(transition)
#print transition.shape
#print bo_training.shape
#print bo_sample.shape

'''
transition_chunk_01 = transition[:3000]
transition_chunk_02 = transition[3000:6000]
transition_chunk_03 = transition[6000:]

bo_training_chunk_01 = bo_training[:3000]
bo_training_chunk_02 = bo_training[3000:6000]
bo_training_chunk_03 = bo_training[6000:]

bo_sample_chunk_01 = bo_sample[:3000]
bo_sample_chunk_02 = bo_sample[3000:6000]
bo_sample_chunk_03 = bo_sample[6000:]


#print len(bo_sample_chunk_01)
#print len(bo_sample_chunk_02)
#print len(bo_sample_chunk_03)

#l1 = 11
#l2 = 13

clf = MLPClassifier(solver = 'lbfgs', alpha = 1e-5,
                    hidden_layer_sizes = (l1, l2), random_state = 1,
                    activation = 'logistic', max_iter = 1000 )

clf.fit(bo_training_chunk_01, transition_chunk_01)


prediction_chunk_01 = clf.predict(bo_sample_chunk_01)
prediction_chunk_02 = clf.predict(bo_sample_chunk_02)
prediction_chunk_03 = clf.predict(bo_sample_chunk_03)


x_01 = np.linspace(0, 2999, 3000)
x_02 = np.linspace(3000, 5999, 3000)
x_03 = np.linspace(6000, len(transition), len(transition) - 6000)

#print len(x_01)
#print len(x_02)
#print len(x_03)

#print len(prediction_chunk_01)
#print len(prediction_chunk_02)
#print len(prediction_chunk_03)


plt.plot(1.2 * transition_chunk_01, label = 'Training 01')
plt.plot(x_02, 1.2 * transition_chunk_02, label = 'Standard 02')
plt.plot(x_03, 1.2 * transition_chunk_03, label = 'Standard 03')

plt.plot(prediction_chunk_01, label = 'Prediction 01')
plt.plot(x_02, prediction_chunk_02, label = 'Prediction 02')
plt.plot(x_03, prediction_chunk_03, label = 'Prediction 03')

plt.legend()

plt.show()
'''

layer1 = np.arange(2, 6)
layer2 = np.arange(2, 4)

#print layer1
#print layer2

#for l1 in layer1:
#    for l2 in layer2:
#        print(l1, l2)


all_err = []

for l1 in layer1:
    err_list = []
    for l2 in layer2:
        #print(l1, l2)
        clf = MLPClassifier(solver = 'lbfgs', alpha = 1e-5,
                            hidden_layer_sizes = (l1, l2), random_state = 1,
                            activation = 'tanh', max_iter = 500 )

        clf.fit(bo_training, transition)

        prediction = clf.predict(bo_sample)

        err = np.sum(np.abs(transition - prediction))
        '''
        fig = plt.figure()

        plt.plot(1.2 * transition, alpha = 0.5, label = 'Standard')
        plt.plot(prediction, alpha = 0.8, label = 'Prediction')

        plt.xlabel('Simulation Trajectory')
        plt.ylabel('Reaction', rotation = 0, labelpad = 30)
        plt.title('Layer 1: {}, Layer 2: {}'.format(l1, l2) )

        plt.tick_params(
                        axis = 'y',
                        which = 'both',
                        left = False,
                        right = False,
                        labelleft = False)

        plt.legend()

        plt.tight_layout()

        save_dir = '/home/jliu/Desktop/files/research/reaction_detection/data/meta_data/l1_' + str(l1) + '/'
        if not os.path.isdir(save_dir):
            os.makedirs(save_dir)

        save_name = save_dir + 'l1_' + str(l1) + '_l2_' + str(l2) + '.png'

        fig.savefig(save_name, dpi = fig.dpi)

        plt.close('all')
        '''
        err_list.append(err)

    all_err.append(err_list)


print all_err

fig, ax = plt.subplots()
#im = ax.imshow(all_err, origin = 'lower')
im = ax.imshow(all_err, origin = 'lower', cmap = 'cool', aspect = 'auto')

#plt.xticks(layer1)
#plt.yticks(layer2)

plt.xticks(np.arange(0, len(layer2), 1), layer2, fontsize = 11)
plt.yticks(np.arange(0, len(layer1), 1), layer1, fontsize = 11)

plt.xlabel('Layer 2')
plt.ylabel('Layer 1')

divider = make_axes_locatable(ax)
cax = divider.append_axes("right", size="3%", pad=0.05)
cbar = fig.colorbar(im, cax = cax)
cbar.ax.set_ylabel("'Error'", rotation = 0, labelpad = 40, size = 12)

plt.grid(linestyle = '--')

plt.tight_layout()

plt.show()
