import numpy as np
import matplotlib.pyplot as plt


z = 2
# n = z / dt
n=100
#while n < 100000000:
dt = (z-0)/n
t = np.linspace(0, z, n+1)

    #### Analytic solution to second test function.
x = np.exp(0.5*t**2) 
y = 1.0- np.exp(.5*t**2) 


# Euler x
xEuler = np.zeros(n)
EulerErr = np.zeros(n)
xEuler[0] = 1 
    
xRK4 = np.zeros(n) 
RK4Err = np.zeros(n)
xRK4[0] = 1
for i in range(1,n):
    xEuler[i] = xEuler[i-1]+dt*xEuler[i-1]*t[i-1]
    EulerErr[i] = abs(xEuler[i]-x[i])

    k1 = dt*x[i-1]*t[i-1]
    k2 = dt*(x[i-1]+0.5*k1)*(t[i-1]+0.5*dt)
    k3 = dt*(x[i-1]+0.5*k2)*(t[i-1]+0.5*dt)
    k4 = dt*(x[i-1]+k3)*(t[i-1]+dt)
        
    xRK4[i] = xRK4[i-1]+(k1+2.0*k2+2.0*k3+k4)/6.0
    RK4Err[i] = abs(xRK4[i]-x[i])
    print(t[i]," ",x[i]," ",xEuler[i]," ",EulerErr[i]," ",xRK4[i]," ",RK4Err[i])
