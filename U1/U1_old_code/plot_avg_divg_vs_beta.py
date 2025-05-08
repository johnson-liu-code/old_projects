




import sys
import os
import numpy as np
import matplotlib.pyplot as plt


dir_name = sys.argv[1]

points = []


for f in sorted(os.listdir(dir_name)):
    fil_name = dir_name + '/' + f

    with open(fil_name, 'r') as fil:
        print fil_name
        lines = fil.readlines()
        divg_list = [float(x.split()[1]) for x in lines[5:] if 'DIVG' in x]
        for line in lines:
            if 'Beta' in line:
                beta = float(line.split()[1])
                break

    points.append( ( beta, np.mean(divg_list) ) )

beta, avg_divg = zip(*points)

plt.plot(beta, avg_divg)


ax.grid(which = 'major', color = 'black', linestyle='--')
ax.set_axisbelow(True)
ax.tick_params(which='both', # Options for both major and minor ticks
                top='off', # turn off top ticks
                left='off', # turn off left ticks
                right='off',  # turn off right ticks
                bottom='off') # turn off bottom ticks


plt.show()

