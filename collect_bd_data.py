
import numpy as np
import pickle



with open('9a_MD_1000K_bp86.xyz', 'r') as fil:
    lines = fil.readlines()
    frame_list = [c for c, l in enumerate(lines) if 'frame' in l]

data = []

for f in frame_list:
    dist_list = []

    for i in range(1, 21):
        #atom1 = lines[f + i].split()[0]
        pos1x = float(lines[f + i].split()[1])
        pos1y = float(lines[f + i].split()[2])
        pos1z = float(lines[f + i].split()[3])

        for j in range(i, 21):
            #print lines[f + j + 1]
            #atom2 = lines[f + j + 1].split()[0]
            #print(atom1, atom2)
            pos2x = float(lines[f + j + 1].split()[1])
            pos2y = float(lines[f + j + 1].split()[2])
            pos2z = float(lines[f + j + 1].split()[3])

            dist = ( (pos1x - pos2x)**2. + (pos1y - pos2y)**2. + (pos1z- pos2z)**2. )**.5

            dist_list.append(dist)

    dist_list = np.array(dist_list)
    data.append(dist_list)

data = np.array(data)

#print len(data[0])
#print np.array(data[0])

with open('xyz.dat', 'wb') as fil:
    pickle.dump(data, fil)
