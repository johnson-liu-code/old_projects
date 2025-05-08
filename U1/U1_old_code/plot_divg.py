


import sys
import matplotlib.pyplot as plt

from running_avg import *


fil_name = sys.argv[1]
N = sys.argv[2]

with open(fil_name, 'r') as fil:
    lines = fil.readlines()
    divg_list = [float(x.split()[1]) for x in lines[5:] if 'DIVG' in x]

plot_dir = 'plots/'

avg = running_avg(divg_list, int(N))


fig, ax = plt.subplots()

plt.plot(divg_list, color = 'purple', linewidth = 1, label = 'Average Divergence')
plt.plot(avg, color = 'cyan', linewidth = 2, label = 'Running Average\n(+/- ' + str(N) + ' frames)')


ax.grid(which = 'major', color = 'black', linestyle='--')
ax.set_axisbelow(True)
ax.tick_params(which='both', # Options for both major and minor ticks
                top='off', # turn off top ticks
                left='off', # turn off left ticks
                right='off',  # turn off right ticks
                bottom='off') # turn off bottom ticks

plt.xlim(0, len(divg_list))
plt.ylim(-.4, .4)

plt.xlabel('Trajectory', size = 16)
plt.ylabel('Avg\nDivergence\n(angle)', rotation = 0, labelpad = 40, size = 16)


plt.legend()

plt.tight_layout()


save_fig_name = plot_dir + fil_name.split(".")[0] + "." + fil_name.split(".")[1] + ".png"
#plt.savefig(save_fig_name)


plt.show()

