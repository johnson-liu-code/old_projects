

import argparse
import os
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable


parser = argparse.ArgumentParser()

parser.add_argument("top_dir_name")
parser.add_argument("-s", "--save", action = 'store_true')

args = parser.parse_args()


Pi_Rc_radius_list = []
Pi_Rc_mass_list = []

Rc_ticks = []
Pi_ticks = []

Pi_dirs = sorted(os.listdir(args.top_dir_name))
for c, Pi_dir in enumerate(Pi_dirs):
    Pi = float(Pi_dir.split('_')[-1])
    Pi_ticks.append(Pi)

    Rc_dirs = sorted(os.listdir(args.top_dir_name + '/' + Pi_dir))

    Rc_radius_list = []
    Rc_mass_list = []

    for Rc_dir in Rc_dirs:
        Rc = float(Rc_dir.split('_')[-1])
        data_file = os.listdir(args.top_dir_name + '/' + Pi_dir + '/' + Rc_dir)[0]
        data_file_name = args.top_dir_name + '/' + Pi_dir + '/' + Rc_dir + '/' + data_file

        print data_file_name

        last_line = os.popen('tail -1 ' + data_file_name).read()

        fields = last_line.split()
        radius = float(fields[1])
        mass = float(fields[7])

        Rc_radius_list.append(radius)
        Rc_mass_list.append(mass)

        if c == len(Pi_dirs) - 1:
            Rc_ticks.append(Rc)

    Pi_Rc_radius_list.append(np.array(Rc_radius_list))
    Pi_Rc_mass_list.append(np.array(Rc_mass_list))

Pi_Rc_radius_list = np.array(Pi_Rc_radius_list)
Pi_Rc_mass_list = np.array(Pi_Rc_mass_list)

########################################################################################

plt_titles = ['Simulated Radius', 'Simulated Mass']

def plot_heatmap(plt_title, Rc_ticks, Pi_ticks, Pi_Rc_radius, )


fig, ax = plt.subplots()

xlocs, xlabels = plt.xticks()
plt.xticks(np.arange(len(Rc_ticks)), Rc_ticks, fontsize = 9)

ylocs, ylabels = plt.yticks()
plt.yticks(np.arange(len(Pi_ticks)), Pi_ticks, fontsize = 9)

im = ax.imshow(Pi_Rc_radius_list, interpolation = 'nearest', cmap = 'RdGy')

plt.ylabel('Initial\nPressure\n(GPa)', rotation = 0, labelpad = 30, size = 12)
plt.xlabel('Rc as\nFraction\nof Rp', size = 12)

plt.title('Simulated Radius', size = 14)

ax.grid(which = 'major', color = 'black', linestyle=':')
ax.set_axisbelow(True)
ax.tick_params(which='both', # Options for both major and minor ticks
                top='off', # turn off top ticks
                left='off', # turn off left ticks
                right='off',  # turn off right ticks
                bottom='off') # turn off bottom ticks

divider = make_axes_locatable(ax)

cax = divider.append_axes("right", size="3%", pad=0.05)

cbar = fig.colorbar(im, cax = cax)
cbar.ax.set_ylabel('Ratio of\nfinal radius\nto actual\nradius', rotation = 0, labelpad = 40, size = 12)

plt.tight_layout()

if args.save == True:
    fields = args.top_dir_name.split('data')
    plot_dir = fields[0] + 'plots' + fields[1] + '/'

    if not os.path.isdir(plot_dir):
        os.makedirs(plot_dir)

    plot_name = plot_dir + 'simulated_radius.png'

    plt.savefig(plot_name)

else:
    plt.show()

########################################################################################

fig, ax = plt.subplots()

xlocs, xlabels = plt.xticks()
plt.xticks(np.arange(len(Rc_ticks)), Rc_ticks, fontsize = 9)

ylocs, ylabels = plt.yticks()
plt.yticks(np.arange(len(Pi_ticks)), Pi_ticks, fontsize = 9)

im = ax.imshow(Pi_Rc_mass_list, interpolation = 'nearest', cmap = 'RdGy')

plt.ylabel('Initial\nPressure\n(GPa)', rotation = 0, labelpad = 30, size = 12)
plt.xlabel('Rc as\nFraction\nof Rp', size = 12)

plt.title('Simulated Mass', size = 14)

ax.grid(which = 'major', color = 'black', linestyle=':')
ax.set_axisbelow(True)
ax.tick_params(which='both', # Options for both major and minor ticks
                top='off', # turn off top ticks
                left='off', # turn off left ticks
                right='off',  # turn off right ticks
                bottom='off') # turn off bottom ticks

divider = make_axes_locatable(ax)

cax = divider.append_axes("right", size="3%", pad=0.05)

cbar = fig.colorbar(im, cax = cax)
cbar.ax.set_ylabel('Ratio of\nfinal mass\nto actual\nmass', rotation = 0, labelpad = 40, size = 12)

plt.tight_layout()

if args.save == True:
    fields = args.top_dir_name.split('data')
    plot_dir = fields[0] + 'plots' + fields[1] + '/'

    if not os.path.isdir(plot_dir):
        os.makedirs(plot_dir)

    plot_name = plot_dir + 'simulated_mass.png'

    plt.savefig(plot_name)

else:
    plt.show()
