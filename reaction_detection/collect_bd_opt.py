
import os
import numpy as np
import pickle

data = []

for fil in os.listdir('/home/jliu/Desktop/files/research/reaction_detection/data/optimized_geometries'):
    with open('/home/jliu/Desktop/files/research/reaction_detection/data/optimized_geometries/' + fil, 'r') as coors_file:
        lines = coors_file.readlines()[2:]

        dist_list = []

        for i in range(0, 20):
            #atom1 = lines[i].split()[0]
            pos1x = float(lines[i].split()[1])
            pos1y = float(lines[i].split()[2])
            pos1z = float(lines[i].split()[3])

            for j in range(i, 20):
                #atom2 = lines[j + 1].split()[0]
                #print(atom1, atom2)
                #data.append((atom1, atom2))
                pos2x = float(lines[j + 1].split()[1])
                pos2y = float(lines[j + 1].split()[2])
                pos2z = float(lines[j + 1].split()[3])

                dist = ( (pos1x - pos2x)**2. + (pos1y - pos2y)**2. + (pos1z- pos2z)**2. )**.5

                dist_list.append(dist)

        dist_list = np.array(dist_list)
        data.append(dist_list)

data = np.array(data)


with open('xyz_opt.dat', 'wb') as fil:
    pickle.dump(data, fil)

