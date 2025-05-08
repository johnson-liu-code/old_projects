
import argparse
import os
import numpy as np
from decimal import *
import matplotlib.pyplot as plt


parser = argparse.ArgumentParser()

parser.add_argument("file_name1")
#parser.add_argument("file_name2")
#parser.add_argument("file_name3")
#parser.add_argument("-s", "--save", action = 'store_true')
args = parser.parse_args()

#print args.file_name1
#print args.file_name2

with open(args.file_name1, 'r') as fil:
    lines = fil.readlines()
    points1 = [(float(l.split()[1]), float(l.split()[3]), float(l.split()[5]), float(l.split()[7])) for l in lines[3:-5]]

#with open(args.file_name2, 'r') as fil:
#    lines = fil.readlines()
#    points2 = [(float(l.split()[1]), float(l.split()[3]), float(l.split()[5]), float(l.split()[7])) for l in lines[3:-1]]


#with open(args.file_name1, 'r') as fil:
#    lines = fil.readlines()
#    points1 = [(Decimal(float(l.split()[1])), Decimal(float(l.split()[3])), Decimal(float(l.split()[5])), Decimal(float(l.split()[7]))) for l in lines[3:-1]]

#with open(args.file_name2, 'r') as fil:
#    lines = fil.readlines()
#    points2 = [(Decimal(float(l.split()[1])), Decimal(float(l.split()[3])), Decimal(float(l.split()[5])), Decimal(float(l.split()[7]))) for l in lines[3:-1]]

#with open(args.file_name3, 'r') as fil:
#    lines = fil.readlines()
#    points3 = [(Decimal(float(l.split()[1])), Decimal(float(l.split()[3])), Decimal(float(l.split()[5])), Decimal(float(l.split()[7]))) for l in lines[3:]]


r1, d1, p1, m1 = zip(*points1)
data1 = [d1, p1, m1]

#r2, d2, p2, m2 = zip(*points2)
#data2 = [d2, p2, m2]

#r3, d3, p3, m3 = zip(*points2)
#data3 = [d3, p3, m3]

d1 = np.array(d1)
#d2 = np.array(d2)
#d3 = np.array(d3)
p1 = np.array(p1)
#p2 = np.array(p2)
#p3 = np.array(p3)
m1 = np.array(m1)
#m2 = np.array(m2)
#m3 = np.array(m3)


#d_diff = np.log10( np.absolute(d1 - d2) )
#p_diff = np.log10( np.absolute(p1 - p2) )
#m_diff = np.log10( np.absolute(m1 - m2) )

#r1 = r1[:63701]
#d_diff = abs(d1[:63701] - d2[:63701])
#p_diff = abs(p1[:63701] - p2[:63701])
#m_diff = abs(m1[:63701] - m2[:63701])

#print d_diff
#print p_diff

#print d1[1000:1010]
#print d2[1000:1010]
#print d1[1000:1010] - d2[1000:1010]

#print format(d1[0] - d2[0], '.50f')
#print d2[0]
#print d3[0]

#data_diff = [d_diff, p_diff, m_diff]

ylabels = [ 'Density\n(g cm$^{-3}$)', 'Pressure\n(GPa)', 'Mass(g)' ]
#ylabels = ['Difference\nin Density\n' + r'(g cm$^{-3}$)', 'Difference\nin Pressure\n(GPa)', 'Difference\nin Mass\n(g)']
#ylabels = [ r'Log$_{10}$' + '\nof the\ndifference\nin Density', r'Log${_10}$' + '\nof the\ndifference\nin Pressure', r'Log$_{10}$' + '\nof the\ndifference\nin Mass' ]
plot_label = [ 'Density', 'Pressure', 'Mass' ]

#loc1 = r1.index(.6)
#print loc1
#loc2 = r1.index(.7)
#print loc2
#loc1 = 14632
#loc2 = 17071

#loc1 = 16460
#loc2 = 16490

plt.figure()
plt.plot(r1, d1)

plt.xlabel('Distance from center')
plt.ylabel('Density')
plt.grid()
plt.show()

'''
plt.figure()
plt.plot(r1, p1)
plt.show()

plt.figure()
plt.plot(r1, m1)
plt.show()
'''
'''
#for n, dat in enumerate(data1):
for n, dat in enumerate(data_diff):
    fig, ax = plt.subplots()

    #plt.plot(r1, data1[n], '-', linewidth = 3, label = 'Quad')
    #plt.plot(r1, data_diff[n], label = 'Abs(Solid - Liquid)')
    #plt.plot(r2, data2[n], '--', linewidth = 2, label = 'Lin')
    #plt.plot(r3, data3[n], '-', linewidth = 10, alpha = .3, label = 'None')

    plt.grid(linestyle = '--')

    plt.xlabel('Radius (cm)', size = 16, labelpad = 20)
    plt.ylabel(ylabels[n], rotation = 0, size = 16, labelpad = 50)

    plt.xticks(np.linspace(float(min(r1)), float(max(r1)+1), 5))


    plt.legend()
    plt.tight_layout()

    plt.show()
'''
'''
    if args.save == True:
        fields = args.file_name1.split('data')
        print fields[1]
        fields2 = fields[1].split('/')

        plot_dir = fields[0] + 'plots' + ('/').join(fields2[:-2]) + '/' + fields2[-1].split('.txt')[0] + '/'

        if not os.path.isdir(plot_dir):
            os.makedirs(plot_dir)
        print plot_dir

        plot_name = plot_dir + fields2[-1].split('.txt')[0] + plot_label[n] + '.png'

        print plot_name

        plt.savefig(plot_name)

    else:
        plt.show()
'''
