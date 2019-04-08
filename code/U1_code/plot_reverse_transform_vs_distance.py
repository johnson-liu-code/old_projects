import numpy as np
import matplotlib.pyplot as plt


outfile = 'test.out'

with open(outfile, 'r') as out:
    lines = out.readlines()

dist_list = []
dist_plp_list = []

for line in lines:
    fields = line.split()
    x = int( fields[0].split(':')[1] )
    y = int( fields[1].split(':')[1] )
    z = int( fields[2].split(':')[1] )
    dist = ( x**2 + y**2 + z**2 )**.5
    plp_rec = float( fields[3].split(':')[1])
    #print dist, plp_rec
    if dist not in dist_list:
        dist_list.append(dist)
        dist_plp_list.append( [dist, plp_rec] )
    else:
        dist_plp_list[ dist_list.index(dist) ].append(plp_rec)

#print dist_plp_list

points = [ (d[0], np.mean(d[1:]) ) for d in dist_plp_list ]

x, y = zip(*points)


plt.scatter(x, y)
plt.grid()
plt.show()
