
import os
import numpy as np
import matplotlib.pyplot as plt


#dir = '/home/jliu/Desktop/files/research/planet_simulator/processing_files/test_data_20190205/'
dir = '/home/jliu/Desktop/files/research/planet_simulator/processing_files/test_data_20181227/'
data_list = []

for p in os.listdir(dir):
    with open(dir + p, 'r') as fil:
        lines = fil.readlines()
        #data = [ (float(line.split()[3]), float(line.split()[5])) for line in lines if 'expected' in line]
        for line in lines:
            if 'expected' in line:
                data_list.append( (float(line.split()[3]), float(line.split()[5])) )
    #data_list = data_list + data

radius, mass = zip(*data_list)

earth_radius = 6.3781e8
earth_mass = 5.972e27

radius = np.array(radius) / earth_radius
mass = np.array(mass) / earth_mass


plt.scatter(mass, radius)
plt.show()
