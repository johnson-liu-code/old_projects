import matplotlib.pyplot as plt


with open('test_scatter.txt', 'r') as fil:
    lines = [line for line in fil.readlines()]

plt.scatter(range(len(lines)), lines)
plt.show()
