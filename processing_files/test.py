

'''
l = ['1', '2', 'done', '3']

for i in l:
    print i
    if i == 'done':
        break

done = False

n = 1

while done == False:
    print n
    n += 1
    if n == 10:
        break
'''

import numpy as np

x = np.linspace(10, 8000, 200)

print x
