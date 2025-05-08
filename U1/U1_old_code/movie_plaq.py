

import sys
import numpy as np
import matplotlib
#matplotlib.use("Agg")
import matplotlib.pyplot as plt
import matplotlib.animation as animation


file_name = sys.argv[1]


#Writer = animation.writers['ffmpeg']
#writer = Writer(fps=15, metadata=dict(artist='Me'), bitrate=1800)

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
#data0 = data_list[0]

n = 100
#data0_p = np.array([data0[i:i + n] for i in range(0, len(data0), n)])

data_list_p = [ np.array([data[i:i + n] for i in range(0, len(data), n)]) for data in data_list ]

#print data0_p[999]

#plt.imshow(data0_p, cmap='cool', interpolation="nearest", vmin = -1, vmax = 1)
#plt.show()
#print len(data_list)

fig = plt.figure()

im = plt.imshow(data_list_p[0], cmap='Greys', interpolation='nearest', origin='lower', vmin = -1, vmax = 1)
cbar = fig.colorbar(im)


def updatefig(j):
    im.set_array(data_list_p[j])
    return [im]

ani = animation.FuncAnimation(fig, updatefig, frames=98, interval=100, blit=True)

plt.title(r'100x100 Lattice, $\beta$ = 10', size = 16)

plt.tight_layout()


#plt.show()

ani.save('movie_100x100_beta10.png')
