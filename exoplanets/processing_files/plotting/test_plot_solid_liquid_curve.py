
import sys
import matplotlib.pyplot as plt


file_name_01 = sys.argv[1]
file_name_02 = sys.argv[2]

earth_mass = 5.972e27
earth_radius = 6.3781e8

def plot(file_name):
    points = []

    with open(file_name, 'r') as fil:
        lines = fil.readlines()
        for line in lines:
            fields = line.split()
            mass = float(fields[3])
            radius = float(fields[5])

            m = mass/earth_mass
            r = radius/earth_radius

            points.append((mass, r))

    m, r = zip(*points)
    plt.scatter(m, r)

plot(file_name_01)
plot(file_name_02)


plt.show()
