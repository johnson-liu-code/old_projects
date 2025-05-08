



import sys
import matplotlib.pyplot as plt



file_name = sys.argv[1]

with open(file_name, 'r') as fil:
    #plaq_poly_list = [(float(l.split()[1]), float(l.split()[3])) for l in fil.readlines() if 'PLAQ' in l]
    real_poly_list = [float(l.split()[4]) for l in fil.readlines() if 'PLAQ' in l]

#plaq, poly = zip(*plaq_poly_list)


#plt.plot(plaq)
#plt.plot(poly)

plt.plot(real_poly_list)

plt.xlabel('Trajecs', size = 16)
plt.ylabel('Re(P)', rotation = 0, labelpad = 30, size =16)

plt.xlim(-10, len(real_poly_list))

plt.tight_layout()

plt.show()
