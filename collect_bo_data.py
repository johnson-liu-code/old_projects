

import argparse
import math
import itertools
import numpy as np
import pickle


parser = argparse.ArgumentParser()
parser.add_argument('file_name')
parser.add_argument('dump_name')
args = parser.parse_args()


with open(args.file_name, 'r') as fil:
    lines = fil.readlines()
    frame_list = [c for c, l in enumerate(lines) if 'frame' in l]

#print frame_list

x = range(21)
#print x
pair_list = list( itertools.combinations(x, 2) )
#print pair_list
#print pair_list.index( (19, 20) )

#zero_vector = np.zeros( (1, len(pair_list) ))



for f in frame_list[:1]:
    first_vector = np.zeros( (1, len(pair_list) ))

    num_lines = int( lines[f-1] )

    for i in range(num_lines):
        cols = lines[f + 1 + i].split()
        if ( int(cols[0]), int(cols[1]) ) in pair_list:
            first_vector[0][pair_list.index( (int(cols[0]), int(cols[1])) )] = float(cols[2])

for f in frame_list[1:]:
    zero_vector = np.zeros( (1, len(pair_list) ))

    num_lines = int( lines[f-1] )

    for i in range(num_lines):
        cols = lines[f + 1 + i].split()
        if ( int(cols[0]), int(cols[1]) ) in pair_list:
            zero_vector[0][pair_list.index( (int(cols[0]), int(cols[1])) )] = float(cols[2])

    first_vector = np.vstack( (first_vector, zero_vector) )


with open(args.dump_name, 'wb') as fil:
    pickle.dump(first_vector, fil)
