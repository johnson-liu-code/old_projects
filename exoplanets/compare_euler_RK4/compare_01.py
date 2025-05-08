

import numpy as np
import matplotlib.pyplot as plt



#### List of step sizes.
# step_size = [1, .5, .2, .1, .05, .02, .01, .005, .002, .001, .0005, .0002, .0001]
# step_size = [.1, .05, .02, .01, .005, .002, .001, .0005, .0002, .0001]
# powers = np.linspace(-4, 1)
# step_size = 10.**powers
# print step_size
#step_size = [.0001]
#step_size = [1e-4]
# step_size = [.2e-1, .2e-2, 2e-3, 2e-4, 2e-5, 2e-6, 2e-7]
step_size = [.02]

#n = 10
#step_size = 2./10


error_vs_step_size = []

#### Iterate over step sizes.
for dt in step_size:
    x_list_euler = []
    y_list_euler = []
    x_list_rk = []
    y_list_rk = []

    x_n_euler = 1	##### Euler x(0) = 1
    x_list_euler.append(x_n_euler)
    y_n_euler = 0	##### Euler y(0) = 0
    y_list_euler.append(y_n_euler)

    x_n_rk = 1		#### RK4 x(0) = 1
    x_list_rk.append(x_n_rk)
    y_n_rk = 0		#### RK4 y(0) = 0
    y_list_rk.append(y_n_rk)

    t_list = []
    #t_n = 0
    #t_list.append(t_n)

    z = 2
    # n = z / dt
    #dt = .001

    #t = np.linspace(0, z, n)
    t = np.arange(0, 2.+dt, dt)
    print len(t)
    #### Analytic solution to first test function.
    x = np.exp(.5*t**2)
    #y = -.5*x*t**2
    y = 1. - np.exp(.5*t**2.)
    '''
    #### Analytic solution to second test function.
    x = .5 * ( np.exp(.5*t**2) + np.exp(-.5*t**2) )
    y = .5 * ( np.exp(.5*t**2) - np.exp(-.5*t**2) )
    '''
    for t_n in t[1:]:
        #### Euler update for first test function.
        y_n_euler = y_n_euler - x_n_euler * t_n * dt
        y_list_euler.append(y_n_euler)
        x_n_euler = x_n_euler + x_n_euler * t_n * dt
        x_list_euler.append(x_n_euler)
        '''
        #### Euler update for second test function.
        y_n_euler = y_n_euler + (x_n_euler - y_n_euler) * t_n * dt
        y_list_euler.append(y_n_euler)
        x_n_euler = x_n_euler + (x_n_euler + y_n_euler) * t_n * dt
        x_list_euler.append(x_n_euler)
        '''

        #### RK4 update for first test function.
        k1 = x_n_rk * t_n * dt
        l1 = -x_n_rk * t_n * dt
        k2 = (x_n_rk + k1/2.) * (t_n + dt/2.) * dt
        l2 = -(x_n_rk + k1/2.) * (t_n + dt/2.) * dt
        k3 = (x_n_rk + k2/2.) * (t_n + dt/2.) * dt
        l3 = -(x_n_rk + k2/2.) * (t_n + dt/2.) * dt
        k4 = (x_n_rk + k3) * t_n * dt
        l4 = -(x_n_rk + k3) * t_n * dt

        '''
        #### RK4 update for second test function.
        k1 = (x_n_rk + y_n_rk) * t_n * dt
        l1 = (x_n_rk - y_n_rk) * t_n * dt
        k2 = ( (x_n_rk + k1/2.) + (y_n_rk + l1/2.) ) * (t_n + dt/2.) * dt
        l2 = ( (x_n_rk + k1/2.) - (y_n_rk + l1/2.) ) * (t_n + dt/2.) * dt
        k3 = ( (x_n_rk + k2/2.) + (y_n_rk + l2/2.) ) * (t_n + dt/2.) * dt
        l3 = ( (x_n_rk + k2/2.) - (y_n_rk + l2/2.) ) * (t_n + dt/2.) * dt
        k4 = ( (x_n_rk + k3) + (y_n_rk + l3) ) * t_n * dt
        l4 = ( (x_n_rk + k3) - (y_n_rk + l3) ) * t_n * dt
        '''

        k = (1./6) * (k1 + 2.*k2 + 2.*k3 + k4)
        l = (1./6) * (l1 + 2.*l2 + 2.*l3 + l4)

        x_n_rk = x_n_rk + k
        y_n_rk = y_n_rk + l
        x_list_rk.append(x_n_rk)
        y_list_rk.append(y_n_rk)

        #t_list.append(t_n)

    # end_diff_euler_x = np.abs(x[-1] - x_list_euler[-1])
    #end_diff_euler_y = np.abs(y[-1] - y_list_euler[-1])
    # end_diff_rk_x = np.abs(x[-1] - x_list_rk[-1])
    #end_diff_rk_y = np.abs(y[-1] - y_list_rk[-1])

    # diff_euler_x = np.abs( np.mean(x - x_list_euler) )
    # diff_euler_y = np.abs( np.mean(y - y_list_euler) )
    # diff_rk_x = np.abs( np.mean(x - x_list_rk) )
    # diff_rk_y = np.abs( np.mean(y - y_list_rk) )

    #error_vs_step_size.append( (dt, end_diff_euler_x, end_diff_euler_y, end_diff_rk_x, end_diff_rk_y) )
    # error_vs_step_size.append( (dt, end_diff_euler_x, end_diff_rk_x) )
    #print x_list_euler
    #error_vs_step_size.append( (dt, diff_euler_x, diff_euler_y, diff_rk_x, diff_rk_y) )

# x_diff = np.abs( np.array(x_list_euler) - np.array(x_list_rk) )
# y_diff = np.abs( np.array(y_list_euler) - np.array(y_list_rk) )

#print len(t)
#print len(x_list_euler)
#print len(x)

x_euler_diff = np.abs(x - x_list_euler)
x_rk_diff = np.abs(x - x_list_rk)

# print('time	xEuler	xAnalytic	Difference     xRK4    Difference')
# for c, it in enumerate(x_list_euler):
    # print('{}	{:.12f}	{:.12f}	{:.12f}   {:.12f} {:.12f}'.format(t[c], x_list_euler[c], x[c], x_euler_diff[c], x_list_rk[c], x_rk_diff[c] ) )
    # print c
# print x_list_euler


# print 'stepsize diff_euler_x diff_rk_x'
# print error_vs_step_size
# for p in error_vs_step_size:
    # print p

'''
#### Plot analytic solution and Euler and RK4 solutions.
plt.plot(t, x, label = 'x(t)', linewidth = 5)
plt.plot(t_list, x_list_euler, label = 'x Euler', linestyle = '--', linewidth = 4)
plt.plot(t_list, x_list_rk, label = 'x RK4', linestyle = '-.', linewidth = 3)
plt.plot(t, y, label = 'y(t)', linewidth = 5)
plt.plot(t_list, y_list_euler, label = 'y Euler', linestyle = '--', linewidth = 4)
plt.plot(t_list, y_list_rk, color = 'k', label = 'y RK4', linestyle = '-.', linewidth = 3)
plt.legend()
plt.grid(linestyle = '--')
# plt.title(r'$\frac{dx}{dt} = xt$, $\frac{dy}{dt} = -xt$, $\Delta t = .0001$')
#plt.title(r'$\frac{dx}{dt} = (x+y)t$, $\frac{dy}{dt} = (x-y)t$, $\Delta t = .0001$')
plt.xlabel('t')
plt.ylabel('x and y')
plt.show()
'''

'''
plt.plot(t_list, x_diff, label = 'Difference in x between Euler and RK4')
plt.plot(t_list, y_diff, linestyle = '--', label = 'Difference in y between Euler and RK4')
plt.legend()
plt.grid(linestyle = '--')
plt.title(r'$\frac{dx}{dt} = xt$, $\frac{dy}{dt} = -xt$, $\Delta t = .0001$')
# plt.title(r'$\frac{dx}{dt} = (x+y)t$, $\frac{dy}{dt} = (x-y)t$, $\Delta t = .0001$')
plt.xlabel('t')
plt.ylabel('Difference in x and y')
plt.show()
'''

# step_size, end_diff_euler_x, end_diff_euler_y, end_diff_rk_x, end_diff_rk_y = zip(*error_vs_step_size)
# step_size, diff_euler_x, diff_euler_y, diff_rk_x, diff_rk_y = zip(*error_vs_step_size)
# print step_size
# print end_diff_euler_x
# plt.scatter(step_size, end_diff_euler_x, label = 'error in x (Euler)')
# plt.scatter(step_size, end_diff_rk_x, label = 'error in x (RK4)')
# plt.scatter(step_size, end_diff_euler_y, label = 'error in y (Euler)')
# plt.scatter(step_size, end_diff_rk_y, label = 'error in y (RK4)')
# plt.scatter(step_size, diff_euler_x, label = 'error in x (Euler)')
# plt.scatter(step_size, diff_rk_x, label = 'error in x (RK4)')
# plt.scatter(step_size, diff_euler_y, label = 'error in y (Euler)')
# plt.scatter(step_size, diff_rk_y, label = 'error in y (RK4)')

# plt.xscale('log')
# plt.grid(linestyle = '--')
# plt.legend()
# plt.xlim(.00005, 1.5)
# plt.xlabel('step size')
# plt.ylabel('error in x and y')
# plt.title('Error in final result for x and y')
# plt.show()
