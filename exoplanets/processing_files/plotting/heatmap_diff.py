

import argparse
import os
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1 import make_axes_locatable

parser = argparse.ArgumentParser()

parser.add_argument("top_dir_name1")
parser.add_argument("top_dir_name2")

parser.add_argument("-s", "--save", action = 'store_true')

args = parser.parse_args()


Pi_Rc_radius_list = []
Pi_Rc_mass_list = []

Rc_ticks = []
Pi_ticks = []

def collect_heatmap_data(dir_name):
    Pi_Rc_radius_list = []
    Pi_Rc_mass_list = []

    Rc_ticks = []
    Pi_ticks = []

    Pi_dirs = sorted( os.listdir(dir_name) )
    for c, Pi_dir in enumerate(Pi_dirs):
        Pi = float(Pi_dir.split('_')[-1])
        Pi_ticks.append(Pi)

        Rc_dirs = sorted( os.listdir( dir_name + '/' + Pi_dir) )

        Rc_radius_list = []
        Rc_mass_list = []

        for Rc_dir in Rc_dirs:
            Rc = float(Rc_dir.split('_')[-1])
            data_file = os.listdir( dir_name + '/' + Pi_dir + '/' + Rc_dir )[0]
            data_file_name = dir_name + '/' + Pi_dir + '/' + Rc_dir + '/' + data_file

            #print data_file_name

            last_line = os.popen('tail -1 ' + data_file_name).read()

            fields = last_line.split()
            radius = float(fields[1])
            mass = float(fields[7])

            Rc_radius_list.append( abs(1 - radius) )
            Rc_mass_list.append( abs(1 - mass) )
    #        Rc_radius_list.append( radius )
    #        Rc_mass_list.append( mass )

    #        print radius
    #        print mass


            if c == len(Pi_dirs) - 1:
                Rc_ticks.append(Rc)

        Pi_Rc_radius_list.append(np.array(Rc_radius_list))
        Pi_Rc_mass_list.append(np.array(Rc_mass_list))

    Pi_Rc_radius_list = np.array(Pi_Rc_radius_list)
    Pi_Rc_mass_list = np.array(Pi_Rc_mass_list)

    return Pi_Rc_radius_list, Pi_Rc_mass_list, Rc_ticks, Pi_ticks

Pi_Rc_radius_list_01, Pi_Rc_mass_list_01, Rc_ticks, Pi_ticks = collect_heatmap_data(args.top_dir_name1)
Pi_Rc_radius_list_02, Pi_Rc_mass_list_02, Rc_ticks, Pi_ticks = collect_heatmap_data(args.top_dir_name2)

Pi_Rc_radius_diff = np.absolute(Pi_Rc_radius_list_01 - Pi_Rc_radius_list_02)
Pi_Rc_mass_diff = np.absolute(Pi_Rc_mass_list_01 - Pi_Rc_mass_list_02)

vmin = min( min(Pi_Rc_radius_diff.flatten()), min(Pi_Rc_mass_diff.flatten()) )
vmax = max( max(Pi_Rc_radius_diff.flatten()), max(Pi_Rc_mass_diff.flatten()) )


########################################################################################

plt_titles = ['Simulated Radius', 'Simulated Mass']
cbar_labels = ['Absolute value\nof the\ndifference\nbetween the\nresults from\nRK4 and Euler', 'Absolute value\nof the\ndifference\nbetween the\nresults from\nRK4 and Euler']
file_names = ['simulated_radius.png', 'simulated_mass.png']
data_lists = [Pi_Rc_radius_diff, Pi_Rc_mass_diff]

#print data_lists

#if args.save == True:
#    fields = args.top_dir_name1.split('data')
#    plot_dir = fields[0] + 'plots' + fields[1] + '/'

#    if not os.path.isdir(plot_dir):
#        os.makedirs(plot_dir)


def plot_heatmap(file_name, plt_title, cbar_label, Rc_ticks, Pi_ticks, Pi_Rc_list):
    fig, ax = plt.subplots()

#    X, Y = np.meshgrid(Rc_ticks, Pi_ticks)

#    im = ax.imshow(Pi_Rc_list, extent = [min(Rc_ticks), max(Rc_ticks), min(Pi_ticks), max(Pi_ticks)], vmin = vmin, vmax = vmax, origin = 'lower', interpolation = 'bilinear', cmap = 'RdGy', aspect = 'auto')
    im = ax.imshow(Pi_Rc_list, vmin = vmin, vmax = vmax, origin = 'lower', interpolation = 'bicubic', cmap = 'cool', aspect = 'auto')

    #plt.plot([0.675567506625, 0.675567506625], [min(Pi_ticks), max(Pi_ticks)], linestyle = '--')
    #ax.plot([min(Rc_ticks), max(Rc_ticks)], [40., 40.], linestyle = '--')


#    ax.xaxis.set_major_locator(plt.MaxNLocator(10))
#    ax.yaxis.set_major_locator(plt.MaxNLocator(20))

    interval = 3

    new_Pi_ticks = [x for c, x in enumerate(Pi_ticks) if c%interval == 0]
    new_Rc_ticks = [x for c, x in enumerate(Rc_ticks) if c%interval == 0]

#    xlocs, xlabels = plt.xticks()
    plt.xticks(np.arange(0, len(Rc_ticks), interval), new_Rc_ticks, fontsize = 11)

#    ylocs, ylabels = plt.yticks()
    plt.yticks(np.arange(0, len(Pi_ticks), interval), new_Pi_ticks, fontsize = 11)


#    contours = plt.contour(X, Y, Pi_Rc_list, 20, colors = 'black')
#    plt.clabel(contours, inline = True, fontsize = 8)

    plt.ylabel('Initial\nPressure\n(GPa)', rotation = 0, labelpad = 30, size = 12)
    plt.xlabel('Rc as\nFraction\nof Rp', size = 12)

    plt.title(plt_title, size = 14)

#    ax.grid(which = 'major', color = 'black', linestyle=':')
#    ax.set_axisbelow(True)
    ax.tick_params(which='both', # Options for both major and minor ticks
                      top=False, # turn off top ticks
                     left=False, # turn off left ticks
                     right=False,  # turn off right ticks
                     bottom=False) # turn off bottom ticks

    divider = make_axes_locatable(ax)

    cax = divider.append_axes("right", size="3%", pad=0.05)

    cbar = fig.colorbar(im, cax = cax)
    cbar.ax.set_ylabel(cbar_label, rotation = 0, labelpad = 50, size = 12)

    plt.tight_layout()

    plt.show()

#    if args.save == True:
#        plot_name = plot_dir + file_name

#        plt.savefig(plot_name)

#    else:
#        plt.show()

for c, itm in enumerate(plt_titles):
    plot_heatmap(file_names[c], plt_titles[c], cbar_labels[c], Rc_ticks, Pi_ticks, data_lists[c])
#    plot_heatmap('test', 'test', 'test', Rc_ticks, Pi_ticks, data_lists[c])
