

import numpy as np
from scipy.sparse import diags


def running_avg(vector, N):
    length = len(vector)
    vector = np.array(vector)

    if length < 10000:
        vector = np.array(vector)
        diagonals = np.ones((1, 2*N + 1))[0]
        offsets = np.arange(-N, N+1)

        matrix = (1./(2.*N+1)) * diags( diagonals, offsets, shape = (length, length) ).todense()
        avg_list = np.array(matrix.dot(vector))[0]

    else:
        #avg_list = []
        #sum = 0
        #for i in range((2*N)+1):
            #print(vector[i])
        #    sum += vector[i]
        #avg = sum / ((2.*N)+1)

        #avg_list.append(avg)

        #for i in range(length - (2*N+1)):
            #print(i, i + 2*N)
            #print('subtract ', i, ', add ', i + 2*N)
        #    sum = (avg * ((2.*N)+1)) - vector[i] + vector[i + 2*N + 1]
            #print('sum ', sum)
        #    avg = sum / ((2.*N)+1)
            #print('avg ', avg)

        #    avg_list.append(avg)

        #y = vector

        #for i in range(2*N):
        #    y = np.insert(y, 0, 0)
        #    vector = np.insert(vector, length, 0)

        #vector = y + vector

        #avg_list = vector / (2.*N+1)

        y = vector
        z = vector

        for i in range(N):
            y = np.insert(y, 0, 0)
            y = y[:-1]

            z = np.insert(z, len(z), 0)
            z = z[1:]

            vector = vector + y + z

        avg_list =  vector / ((2.*N)+1)

    return avg_list
