#!/usr/bin/env python3
# coding: utf-8


import numpy as np
import matplotlib.pyplot as plt

#r1 = np.linspace(0, 4, 1000)
#x1 = np.exp((-r1**2) / 2) / (2*np.pi)**(3/2)
#y1 = np.multiply(r1**2, x1)

# plt.plot(r1, y1)

dim = 3
#dt = 1e-2
dt = 5e-2
num_bins = 100
N_T = 300
N = N_T
rMax = 4
warms = 1000
timeSteps = 4000

def V(R):
    RSqd = 0
    for d in range(dim):
        RSqd += R[d] * R[d]
    
    return RSqd / 2.

#def zeroAccumulators():
#    Esum, ESqdSum = 0, 0
#    psi = np.zeros(num_bins)

#    return Esum, ESqdSum, psi

def initialize(N_T):
    r = [ np.random.uniform(-.5, .5, dim) for n in range(N_T)]
    alive = [True for n in range(N_T)]
    
    return r, alive

def oneMonteCarloStep(r, alive, n, E_T):
    for d in range(dim):
        r[n][d] += np.random.normal(0, 1) * dt**.5
    
    q = np.exp( -dt * ( V(r[n]) - E_T ) )

    survivors = int(q)
    #print(q, survivors)
    if q - survivors > np.random.uniform(0, 1):
        survivors += 1

    #print(survivors)
    for s in range(survivors-1):
        N = len(r)
        r.append( np.zeros(dim) )
        print(N, len(r))
        for d in range(dim):
            r[N][d] = r[n][d]
        alive.append(True)

    if survivors == 0:
        alive[n] = False

    return r, alive

def oneTimeStep(r, alive, psi, E_T, ESum, ESqdSum):
    N = len(r)
    for n in range(N):
        r, alive = oneMonteCarloStep(r, alive, n, E_T)
    #print(r, alive)
    #print(len(r), len(alive))
    r = [ind for c, ind in enumerate(r) if alive[c] == True]
    alive = [a for a in alive if a == True]
    N = len(r)
    #print(N)
    E_T += np.log( N_T / float(N) ) / 10.
    ESum += E_T
    ESqdSum += E_T**2.
    
    for n in range(N):
        #rSqd = 0
        #for d in range(dim):
        #    rSqd = r[n][d]**2.
        rSqd = r[n][-1]**2.
        i = int(rSqd**.5 / rMax * num_bins)
        if i < num_bins:
            psi[i] += 1
    #print(len(r), len(alive))
    return r, alive, psi, E_T, ESum, ESqdSum
    
def run_monte_carlo(N_T):
    r, alive = initialize(N_T)

    E_T, ESum, ESqdSum = 0, 0, 0
    psi = np.zeros(num_bins)

#    ESum, ESqdSum, psi = zeroAccumulators()

    for t in range(warms):
        r, alive, psi, E_T, ESum, ESqdSum = oneTimeStep(r, alive, psi, E_T, ESum, ESqdSum)

#    ESum, ESqdSum, psi = zeroAccumulators()

    E_T, ESum, ESqdSum = 0, 0, 0
    psi = np.zeros(num_bins)

    for t in range(timeSteps):
        #print(len(r), len(alive))
        #print(alive)
        r, alive, psi, E_T, ESum, ESqdSum = oneTimeStep(r, alive, psi, E_T, ESum, ESqdSum)
    
#    print('finish 1')
    
    EAve = ESum / timeSteps
    EVar = ESqdSum / timeSteps - EAve**2
    
    print('<E>: {} +/- {}    <E^2> - <E>^2: {}\n'.format(EAve, (EVar / timeSteps)**.5, EVar ) )

    psiNorm, psiExactNorm = 0, 0
    #print('rMax: {}    num_bins: {}'.format(rMax, num_bins))
    dr = float(rMax) / num_bins
    #print('dr: ', dr)
    for i in range(num_bins):
        r = i * dr
#        print('i: {}    r: {}'.format(i, r))
        psiNorm += r**(dim-1.) * psi[i]**2
        psiExactNorm += r**(dim-1.) * np.exp(-r**2)
    
#    print('finish 2')
#    print('psiNorm: {}    psiExactNorm: {}'.format(psiNorm, psiExactNorm))
    psiNorm = psiNorm**.5
    psiExactNorm = psiExactNorm**.5
#    print('psiNorm: {}    psiExactNorm: {}'.format(psiNorm, psiExactNorm))

    for i in range(num_bins):
        r = i * dr
#        print('r: {}    r**dim: {}    psi: {}    psiNorm: {}'.format(r, r**dim, psi[i], psiNorm))
        psi_value = r**(dim-1.) * psi[i] / psiNorm
        psiExact_value = r**(dim-1.) * np.exp(-r**2.) / psiExactNorm
#        print('psi_value: {}    psiNorm: {}'.format(psi_value, psiNorm))
        print('{}    {}    {}'.format(r, psi_value, psiExact_value))
    
    return r, psi_value, psiExact_value
    
r, psi, psiExact = run_monte_carlo(N_T)
# print(r)

