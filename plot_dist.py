import matplotlib.pyplot as plt

with open('test_dist.txt', 'r') as fil:
    dat = [ (line.split()[3], line.split()[6]) for line in fil.readlines()[1000:2000]]

qs, uni = zip(*dat)

#plt.hist(qs, bins = 30)
plt.hist(uni, bins = 30)

plt.show()
