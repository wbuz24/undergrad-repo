import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
from numba import jit
from numba import prange

"""
6   2   5
  \ | /
3 - 0 - 1
  / | \
7   4   8
"""

tstep = 1000
re = 500
nx = 420
ny = 180 

dx = 1
dy = dx
dt = 1
r = ny // 9
cx = nx // 4
cy = ny // 2
oldvel = 0

ux = .04
alpha = ux * r / re
omega = 1 / (3 * alpha + .5)

e = np.array([[0, 0], [1, 0], [0, 1], [-1, 0], [0, -1], [1, 1], [-1, 1], [-1, -1], [1, -1]])

w = np.array([4/9, 1/9, 1/9, 1/9, 1/9, 1/36, 1/36, 1/36, 1/36])

#col1 = np.array([6, 3, 7], dtype = int)
#col2 = np.array([2, 0, 4], dtype = int)
#col3 = np.array([5, 1, 8], dtype = int)

@jit (nopython=True)
def macroscopic(fin):
    rho = np.sum(fin, axis=0)
    u = np.zeros((2, nx, ny))
    for i in prange(9):
        u[0, :, :] += e[i, 0] * fin[i, :, :]
        u[1, :, :] += e[i, 1] * fin[i, :, :]
    u /= rho
    return rho, u

@jit (nopython=True)
def equilibrium(rho, u):
    usqr = (3/2) * (u[0]**2 + u[1]**2)
    feq = np.zeros((9, nx, ny))
    for i in prange(9):
        cu = 3 * (e[i, 0] * u[0, :, :] + e[i, 1] * u[1, :, :])
        feq[i, :, :] = w[i] * rho * (1 + cu + .5*cu**2 - usqr)
    return feq

def is_solid(nx, ny):
    result = np.zeros((nx, ny), dtype = bool)
    for i in range(nx):
        for j in range(ny):
            num = (i - cx)**2 + (j - cy)**2
            if (num < r**2):
                result[i, j] = 1
    return result

def initialize(d, x, y):
    u = np.zeros((2, x, y))
    rho = np.ones((x, y))
    return rho, u

@jit (nopython=True)
def collide(fin, feq, solid):
    fout = fin - omega * (fin - feq)
    
    #bounce back for object
    for i in prange(nx):
        for j in prange(ny):
            if (solid[i, j] != 0):
                #for k in prange(9):
                #    fout[k, i, j] = fin[8 - k, i, j]
                fout[1, i, j] = fin[3, i, j]
                fout[2, i, j] = fin[4, i, j]
                fout[3, i, j] = fin[1, i, j]
                fout[4, i, j] = fin[2, i, j]
                fout[5, i, j] = fin[7, i, j]
                fout[6, i, j] = fin[8, i, j]
                fout[7, i, j] = fin[5, i, j]
                fout[8, i, j] = fin[6, i, j]
    return fout

@jit (nopython=True)
def stream(fout, fin):
    for ix in prange(nx):
        for iy in prange(ny): 
            for i in prange (9): 
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

solid = is_solid(nx, ny)
rho, vel = initialize(2, nx, ny)
fin = equilibrium(rho, vel)

for t in range(tstep): 
    
    #right wall outflow    
    fin[[5, 1, 8], -1, :] = fin[[5, 1, 8], -2, :]

    rho, u = macroscopic(fin)

    #left wall
    u[0, 0, :] = ux
    rho[0, :] = 1 / (1 - u[0, 0, :]) * (np.sum(fin[[2, 0, 4], 0, :], axis=0) + 2 * np.sum(fin[[5, 1, 8], 0, :], axis=0))

    #equilibrium
    feq = equilibrium(rho, u)
    
    #left implementation
    fin[[6, 3, 7], 0, :] = feq[[6, 3, 7], 0, :] + fin[[8, 1, 5], 0, :] - feq[[8, 1, 5], 0, :]

    
    #collision
    fout = collide(fin, feq, solid)
    
    #stream
    fin = stream(fin, fout)
    
    res = np.abs(np.amax((u - oldvel)))
    oldvel = u
    print("iter: ", t, " residual: ", res)

# plot results
plt.figure(0)
plt.contourf(((u[0]**2+u[1]**2)**0.5).transpose(), np.arange(0, 2 * ux, (2 * ux)/10), extend="both", cmap = cm.jet)
plt.savefig("cylinder.png", dpi = 300)

