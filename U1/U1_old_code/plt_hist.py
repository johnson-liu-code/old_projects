

import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation



file_name = sys.argv[1]

data_list = []
new_list = []

with open(file_name, 'r') as fil:
    lines = fil.readlines()
    for line in lines[5:]:
        if 'TRAJ' in line:
            data_list.append(new_list)
            new_list = []
        else:
            new_list.append(float(line))

data_list = data_list[1:]

data0 = data_list[0]
data10 = data_list[9]
data50 = data_list[49]
data99 = data_list[98]


#print len(data0)
#plt.hist(data0, bins = 100)
#plt.hist(data99, bins = 10)

fig, ax = plt.subplots()
hist = plt.hist(data99, bins=100, color='purple')

ax.grid(which = 'major', color='black', linestyle='--')
ax.set_axisbelow(True)
ax.tick_params(which = 'both', # Options for both major and minor ticks
                top = 'off', # turn off top ticks
                left = 'off', # turn off left ticks
                right = 'off',  # turn off right ticks
                bottom = 'off') # turn off bottom ticks

#def updatefig(j):
#    hist = plt.hist(data_list[j])
#    return hist

#ani = animation.FuncAnimation(fig, updatefig, frames=range(100), interval=99, blit=True)

plt.xlabel('Re(Plaquette)', size = 16)
plt.ylabel('Number\nof\nPlaquettes', rotation = 0, labelpad = 40, size = 16)

plt.title(r'100x100 Lattice, $\beta = 10$', size = 16)

plt.tight_layout()

#plt.show()

plt.savefig('hist_plaq_beta10.png')
