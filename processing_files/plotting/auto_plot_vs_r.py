

import sys
import os

top_dir_name = sys.argv[1]

#fields = top_dir_name.split('data')

#plot_dir = fields[0] + 'plots' + fields[1]
lowest_dirs = [root for root, dirs, files in os.walk(top_dir_name) if not dirs]

for l in lowest_dirs:
    fil_list = os.listdir(l)
    for f in fil_list:
        #print l + '/' + f
        os.system("python /home/jliu/Desktop/files/research/planet_interior_simulator/processing_files/plot_vs_r.py " + l + '/' + f + ' -s')
