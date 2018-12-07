
import numpy as np


def lin_inter(x_values, y_values, desired_y):
    slope = (y_values[1] - y_values[0])/(x_values[1] - x_values[0])

    #print abs(desired_y - y_values[0])
    #print abs(desired_y - y_values[1])
    if abs(desired_y - y_values[0]) < abs(desired_y - y_values[1]):
        #print 'opt 1'
        delta_y = desired_y - y_values[0]
        next_x_guess = x_values[0] + delta_y/slope
    else:
        #print 'opt 2'
        delta_y = desired_y - y_values[1]
        next_x_guess = x_values[1] + delta_y/slope

    return next_x_guess


#x_values = [40, 50]
#y_values = [.9, 1.2]

#x_values = [30, 40]
#y_values = [.8, .9]

#x_values = [30, 50]
#y_values = [.7, 1.1]

#x_values = [45, 50]
#y_values = [1.1, 1.2]

#x_values = [.1, .5]
#y_values = [.01, .25]

#x_values = [.5, 1.75]
#y_values = [.25, 3.0625]

#print(lin_inter(x_values, y_values, 1.))

'''
x_values = [.1, .5]
y_values = [.01, .25]
2
thresh = 1.e-6
desired_y = 9

y = y_values[1]

def y_func(x):
    return x**2.

while (abs(desired_y - y) > thresh):
    next_x_guess = lin_inter(x_values, y_values, desired_y)
    y = y_func(next_x_guess)

    print("x: ", next_x_guess, " y: ", y)

    if abs(desired_y - y_values[0]) < abs(desired_y - y_values[1]):
        x_values = [x_values[0]]
        y_values = [y_values[0]]
    else:
        x_values = [x_values[1]]
        y_values = [y_values[1]]

    x_values.append(next_x_guess)
    y_values.append(y)
'''
