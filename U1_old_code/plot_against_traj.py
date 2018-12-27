

import sys
import numpy as np
import matplotlib.pyplot as plt

from running_avg import *

file_name = sys.argv[1]

with open(file_name, 'r') as txt:
    poly = [float(p.split()[1]) for p in txt.readlines() if 'POLY' in p]

avg = running_avg(poly, 50)

plt.plot(poly, color = 'purple')
plt.plot(avg, color = 'cyan', linewidth = 3)

plt.show()
