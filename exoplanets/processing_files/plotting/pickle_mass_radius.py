import argparse
import os
import numpy as np
import pickle
import matplotlib.pyplot as plt


parser = argparse.ArgumentParser()
#parser.add_argument('rock_directory')
parser.add_argument('iron_directory')
args = parser.parse_args()

earth_radius = 6.3781e8                 # cm
earth_mass = 5.972e27                   # g


def collect_data(data_directory):
    data_list = []
    for p in sorted(os.listdir(data_directory)):
        pressure = float(p.split('_')[1])
        for r in sorted(os.listdir(data_directory + '/' + p)):
            Rc = float(r.split('_')[1])
            file_name = data_directory + '/' + p + '/' + r + '/' + os.listdir(data_directory + '/' + p + '/' + r)[0]
            line = os.popen('tail -1 ' + file_name).read()
            final_radius = float(line.split()[1])
            final_mass = float(line.split()[7])
            data_list.append( (pressure, Rc, final_radius, final_mass) )

    return data_list

#data_list_rock = collect_data(args.rock_directory)
data_list_iron = collect_data(args.iron_directory)

#with open('rock_radius_mass.dat', 'wb') as fil:
#    pickle.dump(data_list_rock, fil)
with open('iron_radius_mass.dat', 'wb') as fil:
    pickle.dump(data_list_iron, fil)
