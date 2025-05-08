
import argparse
import os
import pickle


parser = argparse.ArgumentParser()
parser.add_argument('dir_name')
args = parser.parse_args()


data = []

for d in os.listdir(args.dir_name):
#    print d
    with open(args.dir_name + '/' + d, 'rb') as fil:
        dat = pickle.load(fil)
        data.append(dat)

combined_data = [item for sublist in data for item in sublist]

with open('iron_combined.dat', 'wb') as fil:
    pickle.dump(combined_data, fil)
