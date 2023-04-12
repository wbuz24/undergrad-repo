# D2Q9 advection diffusion code

from matplotlib import pyplot as plt
from numba import jit
import numpy as np
import scipy as sp


"""
  6   2   5
    \ | /
  3 - 0 - 1
    / | \
  7   4   8
"""

nx = 100
ny = 100

ux = .1
uy = .4
dt = 1
dx = 1
dy = dx
alpha = 1/12
ck = dx/dt
csq = 1/3 #D2Q9
omega = 1.0/(3*alpha +.5)
mstep = 400
density = 0
tw = 1
rhoold = np.zeros((nx, ny), dtype = np.float64)


fin = np.zeros((9, nx, ny), dtype = np.float64) # initialized 2D array of n     size filled with zeros
rho = np.zeros((nx, ny), dtype = np.float64)

u = np.zeros((2, nx, ny), dtype = np.float64) # velocity vector

w = np.array ([4/9, 1/9, 1/9, 1/9, 1/9, 1/36, 1/36, 1/36, 1/36 ]) #declared     arrays
e = np.array ([[0, 0], [1, 0], [0, 1], [-1, 0], [0, -1], [1, 1], [-1, 1]
    ,[-1, -1], [1, -1]])

def equil(rho, u):
     feq = np.zeros((9, nx, ny), dtype = np.float64)

     for ix in range(0, nx, 1):
         for iy in range(ny):
             for i in range(9): # assumes range(0, 2, 1):
                eu = e[i, 0] * u[0, ix, iy] + e[i, 1] * u[1, ix, iy]
                usq = u[0, ix, iy] **2 + u[1, ix, iy]**2
                feq[i, ix, iy] = w[i] * rho[ix, iy] * (1 + (eu/csq) + .5 * (eu/csq)**2 - .5 * (usq/csq))
     return feq


def macro(fin):
    rho = np.sum(fin, axis = 0) # loops through array, adding all elements
                                 # axis specifies the axis to sum up
    return rho

def initial(rho):
    rho0 = 0
    for ix in range(nx): # rho[:] = rho0 produces same output
        for iy in range(ny):
            rho[ix, iy] = rho0
    return rho

def initialize(fin, u):
 for i in range(ny):
        for j in range(nx):
            u[0, i, j] = ux
            u[1, i, j] = uy
            for k in range(9):
                #fin[k, i, j] = w[k] * density
                rho[i, j] = 0
                #if i == 0:
                 #   fin[k, i, j] = w[k] * tw
 fin = equil(rho, u)
 return fin, u

# main loop
fin, u = initialize(fin, u)


for t in range(mstep):
    #fin[:, :, 0] = fin[:, :, 1]

    #macroscopic
    rho = macro(fin)

    #boundary condition left
    rho[0, :] = tw



    #boundary condition right
    rho[nx - 1, :] = rho[nx - 2, :]

 #boundary condition top
    rho[:, ny - 1] = 0 #rho[:, ny - 2]


    #boundary condition bottom
    rho[:, 0] = 0 #rho[:, 1]


    #implement boundary condition
    feq = equil(rho, u)
    fin[[6, 3, 7], 0, :] = feq[[6, 3 ,7 ], 0, :] + fin[[8, 1, 5], 0, :] - feq[[8, 1, 5], 0, :]

    fin[[5, 1, 8], nx - 1, :] = feq[[5, 1, 8], nx - 1, :] + fin[[7, 3, 6], nx - 1, :] - feq[[7, 3, 6], nx - 1, :]

    fin[[6, 2, 5], :, ny - 1] = feq[[6, 2, 5], :, ny - 1] + fin[[8, 4, 7], :, ny - 1] - feq[[8, 4, 7], :, ny - 1]

    fin[[7, 4, 8], :, 0] = feq[[7, 4, 8], :, 0] + fin[[5, 2, 6], :, 0] - feq[[5, 2, 6], :, 0]

    #collision
    fout = fin - omega * (fin - feq)

    # bounce back @ [5, 1, 8]
    #fout[[5, 1, 8], nx - 1, :] = fin[[7, 3, 6], nx - 1, :]

    # bounce back @ [6, 2, 5]
  #stream
    for ix in range(nx):
        for iy in range(ny):
            for i in range (9):
                nextx = ix + e[i, 0]
                nexty = iy + e[i, 1]

                if nextx >= nx:
                    nextx = 0
                elif nextx < 0:
                    nextx = nx - 1

                if nexty >= ny:
                    nexty = 0
                elif nexty < 0:
                    nexty = ny - 1

                fin[i, nextx, nexty] = fout[i, ix, iy]
    res = np.amax(np.abs(rho - rhoold))
    rhoold = rho
    print("iter: ", t, " residual: ", res)

 # plot results
plt.figure(0)
plt.contourf(rho.transpose(), np.arange(0, 1, .1), extend="both")
plt.savefig("advection - diffusion.png", dpi = 300)

