import sys
import os
import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

'''
num = sys.argv[1]
top_dir = '/home/jliu/Desktop/files/research/planet_interior_simulator/data/solid_liquid_core/' + str(num) + '/'
print top_dir

#Rp = 6.3781e8


fig, ax = plt.subplots()

#for dir in os.listdir(top_dir)[:-1]:
#    print dir
for fil in sorted(os.listdir(top_dir)):
    percent = fil.split('_')[0]
    with open(top_dir + fil) as txt_file:
        lines = txt_file.readlines()
        mass = [float(m.split()[3]) for m in lines]
        radius = [float(r.split()[5]) for r in lines]

        #mass_radius = sorted( [ ( float(m.split()[3]), float(m.split()[5]) ) for m in lines] )

        #print mass_radius

        lab = fil.split('.')[0]

        mass, radius = zip(*mass_radius)
        #print radius
        #plt.plot(mass, radius, label = lab)
        plt.scatter(mass, radius)

plt.title('Liquid and Solid Iron Cores')

plt.grid()

plt.xlabel('Mass in Earth Mass Units', size = 12)
plt.ylabel('Radius in Earth Radius Units', size = 12)

plt.legend()

plt.show()
'''

file_name_solid = sys.argv[1]
file_name_liquid = sys.argv[2]

with open(file_name_solid, 'r') as fil:
    lines_solid = fil.readlines()
#mass_solid = [float(m.split()[3]) for m in lines_solid]
#radius_solid = [float(r.split()[5]) for r in lines_solid]
mass_radius_solid = sorted( [ (float(m.split()[3]), float(m.split()[5]) ) for m in lines_solid] )
mass_solid, radius_solid = zip(*mass_radius_solid)

mass_solid = np.array(mass_solid)
#print mass_solid
radius_solid = np.array(radius_solid)
#print radius_solid

with open(file_name_liquid, 'r') as fil:
    lines_liquid = fil.readlines()
#mass_liquid = [float(m.split()[3]) for m in lines_liquid]
#radius_liquid = [float(r.split()[5]) for r in lines_liquid]
mass_radius_liquid = sorted( [ (float(m.split()[3]), float(m.split()[5]) ) for m in lines_liquid] )
mass_liquid, radius_liquid = zip(*mass_radius_liquid)

#plt.plot(mass_solid, radius_solid, label = 'solid')
plt.scatter(mass_solid, radius_solid, label = 'solid')

#plt.plot(mass_liquid, radius_liquid, label = 'liquid')
plt.scatter(mass_liquid, radius_liquid, label = 'liquid')


CMF_solid = 0.295896
CMF_liquid = 0.247954

x = np.linspace(min(mass_solid), max(mass_solid))

#y = np.log(x)
y1 = (1.07 - .21*CMF_solid)*x**(1/3.7)
y2 = (1.07 - .21*CMF_liquid)*x**(1/3.7)

plt.plot(x, y1, label = 'Zeng solid')
plt.plot(x, y2, label = 'Zeng liquid')

'''
def func_solid(x_range, a, b, c):
    return (a - b*CMF_solid)*x_range**c

def func_liquid(x_range, a, b, c):
    return (a - b*CMF_liquid)*x_range**c


popt_solid, pcov_solid = curve_fit(func_solid, mass_solid, radius_solid)
plt.plot(mass_solid, func_solid(mass_solid, *popt_solid) )

popt_liquid, pcov_liquid = curve_fit(func_liquid, mass_liquid, radius_liquid)
plt.plot(mass_liquid, func_liquid(mass_liquid, *popt_liquid) )

#print popt_solid
#print pcov_solid
#print popt_liquid
#print pcov_liquid
'''
plt.grid()

plt.xlabel('Mass in Earth Mass Units', size = 12)
plt.ylabel('Radius in Earth Radius Units', size = 12)

plt.legend()

#plt.show()


from scipy import optimize
import matplotlib
from matplotlib import pyplot as plt
from scipy import *
import numpy as np


Mat_ydata=[]
Mat_angle=[]
Mat_xdata=[]

#for c in range(0,100,20):
#    num_points=c+100
#    xdata=linspace(0,num_points/2, num_points)
#    ydata=5.1/((xdata-c)**2+2.1**2)+0.05*((0.5*rand(num_points))*exp(2*rand(num_points)**2))
    #print ydata
#    Mat_angle.append(c)
#    Mat_ydata.append(ydata)
#    Mat_xdata.append(xdata)

#print Mat_angle
#print Mat_ydata
#print Mat_xdata
#print np.size(Mat_xdata)
#print type(Mat_xdata)

def lor_func(x, cmf, par):
#    a,b,d=par
    a, b, c = par
#    return a/((x-c)**2+b**2)
    return (a - b * cmf) * x**c

def err (p, cmf, x, y):
    return lor_func(x, cmf, p) - y

Mat_angle = [CMF_solid, CMF_liquid]
Mat_xdata = [mass_solid, mass_liquid]
Mat_ydata = [radius_solid, radius_liquid]

#print len(Mat_angle)
#print len(Mat_xdata)
#print len(Mat_ydata)

def err_global(p, Mat_a, Mat_x, Mat_y):
    err0=[]
    for i in range( 0, len(Mat_a) ):
        errc = err( p, Mat_a[i], Mat_x[i], Mat_y[i] )
        err1 = np.concatenate( (err0, errc) )
        err0 = err1
    return err0


p_global = [1, 1, 1]
p_best, success = optimize.leastsq(err_global, p_global, args = ( Mat_angle, Mat_xdata, Mat_ydata ), maxfev = 40000)

toplot = []
for i in range( 0, len( Mat_angle ) ):
    toplot.append( lor_func( Mat_xdata[i], Mat_angle[i], p_best ) )
err_toplot = err_global( p_best, Mat_angle, Mat_xdata, Mat_ydata )
print p_best
print success

labels = ['custom solid', 'custom liquid']

for i in range( 0, len( Mat_angle ) ):
    #plt.plot(Mat_xdata[i],Mat_ydata[i],'o',Mat_xdata[i],toplot[i],'-')
    plt.plot( Mat_xdata[i], toplot[i], '--', label = labels[i])

plt.legend()

plt.show()
