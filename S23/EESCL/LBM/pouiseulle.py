# pouiseulle flow 

from matplotlib import pyplot as plt
import numpy as np
import scipy as sp
from matplotlib import cm
from numba import jit

"""
  6   2   5
    \ | /
  3 - 0 - 1
    / | \
  7   4   8
"""

nx = 200
ny = 100

ux = 0.01
uy = 0
dt = 1
dx = 1
dy = dx
re = 500
alpha = (ux * ny) / re
ck = dx/dt
csq = 1/3 #D2Q9
omega = 1.0/(3*alpha +.5)
mstep = 1000
oldvel = 0

fin = np.zeros((9, nx, ny), dtype = np.float64) # initialized 2D array of n     size filled with zeros
rho = np.zeros((nx, ny), dtype = np.float64)

umacro = np.zeros((2, nx, ny), dtype = np.float64)
u = np.zeros((2, nx, ny), dtype = np.float64) # velocity vector

w = np.array ([4/9, 1/9, 1/9, 1/9, 1/9, 1/36, 1/36, 1/36, 1/36]) #declared     arrays
e = np.array ([[0, 0], [1, 0], [0, 1], [-1, 0], [0, -1], [1, 1], [-1, 1], [-1, -1], [1, -1]])

@jit (nopython=True)
def equil(rho, u):
    feq = np.zeros((9, nx, ny), dtype = np.float64)

    for ix in range(nx):
        for iy in range(ny):
            for i in range(9): 
                eu = 3 * (e[i, 0] * u[0, ix, iy] + e[i, 1] * u[1, ix, iy])
                usq = (3/2) * (u[0, ix, iy] **2 + u[1, ix, iy]**2)
                feq[i, ix, iy] = w[i] * rho[ix, iy] * (1 + (eu) + .5 * (eu)**2 - usq)
    return feq

@jit (nopython=True)
def macro(fin):
    rho = np.sum(fin, axis = 0) # loops through array, adding all elements
                                 # axis specifies the axis to sum up
    u = np.zeros((2, nx, ny), dtype = np.float64)
    for i in range(9):
        u[0, :, :] += fin[i, :, :] * e[i, 0]
        u[1, :, :] += fin[i, :, :] * e[i, 1] 
    u[0] = u[0] / rho
    u[1] = u[1] / rho
    return rho, u


def initialize():
    for i in range(nx):
        for j in range(ny):
            u[0, i, j] = 0; 
            u[1, i ,j] = 0;
            rho[i, j] = 1
    return rho, u

@jit (nopython=True)
def collisions(fin, feq):
    fout = fin - omega * (fin - feq)

    return fout

@jit (nopython=True)
def stream(fout, fin):
    for ix in range(nx):
        for iy in range(ny):
            for i in range (9):
                nextx = ix + e[i, 0]
                nexty = iy + e[i, 1]
                
                if (nextx >= nx):
                    nextx = 0

                elif (nextx < 0):
                    nextx = nx - 1
                
                if (nexty >= ny):
                    nexty = 0

                elif (nexty < 0):
                    nexty = ny - 1
                    
                fin[i, nextx, nexty] = fout[i, ix, iy]
    return fin

# main loop
rho, u = initialize()
fin = equil(rho, u)

for t in range(mstep):
    fin[:, nx - 1, :] = fin[:, nx - 2, :]

    #macroscopic
    rho, umacro = macro(fin)
    
    #boundary condition left
    
    umacro[0, 0, i] = ux
    umacro[1, 0, i] = uy #u[1, :, :] = uy

    rho[0, :] = 1 / (1 - umacro[0, 0, :]) * (np.sum(fin[[2, 0, 4], 0, :], axis=0) + 2 * np.sum(fin[[5, 1, 8], 0, :], axis=0)) 
    #rho[0, :] = (fin[0, 0, :] + fin[2, 0, :] + fin[4, 0, :] + 2 * (fin[1, 0, :] + fin[5, 0, :] + fin[8, 0, :])) / (1 - umacro[0, 0, :])

    #boundary condition right
    #rho[nx - 1, :] = rho[nx - 2, :]
    #umacro[:, nx - 1, :] = umacro[:, nx - 2, :]

    #boundary condition top
    #rho[:, ny - 1] = rho[:, ny - 2]
    #u[:, :, ny - 1] = 0
    #boundary condition bottom
    #rho[:, 0] = rho[:, 1]
    #u[:, :, 0] = 0

    #implement boundary condition
    feq = equil(rho, umacro)
    fin[[6, 3, 7], 0, :] = feq[[6, 3 ,7 ], 0, :] + fin[[8, 1, 5], 0, :] - feq[[8, 1, 5], 0, :]

    #fin[[5, 1, 8], nx - 1, :] = feq[[5, 1, 8], nx - 1, :] + fin[[7, 3, 6], nx - 1, :] - feq[[7, 3, 6], nx - 1, :]

    #fin[[6, 2, 5], :, ny - 1] = feq[[6, 2, 5], :, ny - 1] + fin[[8, 4, 7], :, ny - 1] - feq[[8, 4, 7], :, ny - 1]
    #fin[[7, 4, 8], :, 0] = feq[[7, 4, 8], :, 0] + fin[[5, 2, 6], :, 0] - feq[[5, 2, 6], :, 0]

    #collision
    fout = collisions(fin, feq)

    # bounce back @ [5, 1, 8]
    #fout[[5, 1, 8], nx - 1, :] = fin[[7, 3, 6], nx - 1, :]

    # bounce back @ [6, 2, 5]
    fout[[6, 2, 5], :, ny - 1] = fin[[8, 4, 7], :, ny - 1] # top

    fout[[7, 4, 8], :, 0] = fin[[5, 2, 6], :, 0] # bottom
    
    #stream
    fin = stream(fout, fin)
    res = np.abs(np.amax((umacro - oldvel)))
    oldvel = umacro + 1e-10
    print("iter: ", t, " residual: ", res)

 # plot results
plt.figure(0)
plt.contourf(umacro[0].transpose(), np.arange(0, 2 * ux, (2 * ux)/10), extend="both", cmap = cm.jet)
plt.savefig("pouiseulle1.png", dpi = 300)

plt.figure(1)
plt.contourf(umacro[1].transpose(), np.arange(0,2 * ux,(2 * ux)/10), extend="both", cmap=cm.jet)
plt.savefig("pouiseulle2.png", dpi = 300)

sq = (umacro[0]**2 + umacro[1]**2)**.5

plt.figure(2)
plt.contourf(sq.transpose(), np.arange(0,2 * ux,(2 * ux)/10), extend="both", cmap=cm.jet)

plt.savefig("pouiseulle3.png", dpi = 300)

