
import os
import matplotlib.pyplot as plt


dir = '/home/jliu/Desktop/files/research/planet_simulator/processing_files/test_data_20190205/'

data_list = []

for p in os.listdir(dir):
    with open(dir + p, 'r') as fil:
        lines = fil.readlines()
        #data = [ (float(line.split()[3]), float(line.split()[5])) for line in lines if 'expected' in line]
        for line in lines:
            if 'expected' in line:
                data_list.append( (float(line.split()[3]), float(line.split()[5])) )
    #data_list = data_list + data

data_list = sorted(data_list)

radius, mass = zip(*data_list)

plt.scatter(mass, radius)
plt.show()
