from matplotlib import pyplot as plt
import numpy as np
import scipy as sp


mstep = 100
n = 100
dt = 1.0
dx = 1.0
alpha = .25
omega = 1 / (alpha + .5)
twall = 1


fin = np.zeros((2, n), dtype = np.float64) # initialized 2D array of n size filled with zeros

rho = np.zeros((n), dtype = np.float64) 

w = np.array ([1/2, 1/2]) #declared arrays

e = np.array ([-1, 1]) 

def equil(rho):
    feq = np.zeros((2, n), dtype = np.float64)
    
    for ix in range(0, n, 1):
        for i in range(2): # assumes range(0, 2, 1):
            feq[i, ix] = w[i] * rho[ix]
    
    return feq

def macro(fin):
    rho = np.sum(fin, axis = 0) # loops through array, adding all elements
                                # axis specifies the axis to sum up

    return rho

def initial(rho):
    rho0 = .5
    for i in range(n): # rho[:] = rho0 produces same output
        rho[i] = rho0
    return rho

rho = initial(rho)
rhoold = 0;

fin = equil(rho)
# starting main loop

for time in range (mstep):
    #fin[:, n] = fin[:, n-1]

    rho = macro(fin)
    
    rho[0] = twall; # semicolon is still proper syntax
    
    feq = equil(rho)

    fin[0, 0] = feq[0, 0] + fin[1, 0] - feq[1, 0]  

    # collision (could write a function)
    fout = fin - omega * (fin - feq) # python shorthand knows arrays of same size to be indexed properly
    

    # bounce back boundary
    for i in range(2):
        fout[i, n - 1] = fin[1 - i, n - 1] 
    
    # stream
    for ix in range(n):
        for i in range (2):
            next = ix + e[i]

            if next >= n:
                next = 0
            elif next < 0:
                next = n - 1

            fin[i, ix] = fout[i, next] # next variable takes care of indexing
            
    res = np.amax(np.abs(rho - rhoold))
    rhoold = rho
    print("iter: ", time, " residual: ", res)
    
# plot results
plt.figure(0)
plt.plot(np.arange(n), rho)
plt.savefig("diffusion.png", dpi = 300)

