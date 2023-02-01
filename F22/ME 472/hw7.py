#####
# Will Buziak
# Homework 7
# ME 472
# Wind power assignment
#####

import math
import numpy as np
from matplotlib import pyplot as plt
from scipy.optimize import curve_fit

nodes = 100 # of segments 
blades = 3 # of blades
n = 20 # rpm (rotational speed)
r = 40 # m (blade length)
d = 3; # m (distance from shaft to inner edge)
uinf = 7 # m/s (unaffected wind speed)
rho = 1.26 # kg/m^3 (density of air)
tl = 2 # m (end tip width)
il = 5 # m (inner tip width)
Clarr = np.array([.5, 1.05, 1.275, 1.3, 1.185, .675])
Cdarr = np.array([.001, .002, .00375, .0055, .008, .01125])
x = np.array([5, 10, 15, 20, 25, 30])
lfit = np.polyfit(x, Clarr, 2)
dfit = np.polyfit(x, Cdarr, 1)
fl = np.poly1d(lfit)
fd = np.poly1d(dfit)
v = (2/3) * uinf
u = []
A = []
linv = []
Fl = []
Fd = []
resultp = []
resultt = []
pa = 0
I = []
resA = []
aoa2 = []
aoa3 = []
w = []
Cd = []
Cl = []
Cd0 = []
Cd1 = []
Cd2 = []
Cl0 = []
Cl1 = []
Cl2 = []
Fl0 = []
Fd0 = []
Fl1 = []
Fd1 = []
Fl2 = []
Fd2 = []
mom = []
mom0 = []
mom1 = []
mom2 = []
thrust = []
thr0 = []
thr1 = []
thr2 = []
Fl = []
Fd = []

i = 0
t = 0.0001
oldA = 0
enum = 0
mtot = 0
ttot = 0
element = np.linspace(1, 100, 81)
def fit1d(a, b, z):
   return a*z+b

def fit2d(a, b, c, z):
   return -a*x**2+b*x+c 

paramscd = curve_fit(fit1d, x, Cdarr) 
paramscl = curve_fit(fit2d, x, Clarr)

kd = paramscd[0]
jl = paramscl[0]

ad = kd[0]
bd = kd[1]

al = jl[0]
bl = jl[1]
cl = jl[2]

m = np.array([0, 2, 4])

for p in range(m.__len__()):
   Cd.append(ad*m[p] + bd)
   Cl.append(-al*m[p]**2 + bl*m[p]**2 + cl)
   

while (t < 40):   
   A.append(t * (tl + il) / 2)
   u.append(t * n)
   t += .4
   
for p in range(A.__len__()):
   resA.append(A[p] - oldA)
   oldA = A[p] + 1e-10
   w.append((v**2 + u[p]**2)**.5)

while (i < 4.0):
   cdl = 0
   cll = .0005
   Fl.append(.5 * rho * A[p] * w[p]**2 * cll)
   Fd.append(.5 * rho * A[p] * w[p]**2 * cdl)
   Fl0.append(.5 * rho * A[p] * w[p]**2 * 0)
   Fd0.append(.5 * rho * A[p] * w[p]**2 * .00025)
   Fl1.append(.5 * rho * A[p] * w[p]**2 * .155)
   Fd1.append(.5 * rho * A[p] * w[p]**2 * .0005)
   Fl2.append(.5 * rho * A[p] * w[p]**2 * .445)
   Fd2.append(.5 * rho * A[p] * w[p]**2 * .00112)
   cdl += .0019375
   cll += .00000775
   pa += .357
   i += .05

mrad = np.linspace(3, 43, 81)
t0 = 0
t1 = 0
t2 = 0
th = 0
Ft0 = []
for p in range(u.__len__()):
   I.append(np.arctan(v / u[p]))
   Cl0.append(0)
   Cl1.append(.155)
   Cl2.append(.445)
   Cd0.append(.00025)
   Cd1.append(.0005)
   Cd2.append(.00112)
   aoa2.append(I[p] - 2)
   aoa3.append(I[p] - 4)
   deg2rad = np.radians(I[p])
   cos = (math.cos(deg2rad))
   sin = math.sin(deg2rad)
   Ft0 = (Fl0[p]) * (cos) + Fd0[p] * (sin)
   Ft = Fl[p] * np.cos(I[p]) + Fd[p] * np.sin(I[p])
   th += Ft
   ttot += Ft
   t0 += Ft0
   Fm0 = Fl0[p] * np.sin(I[p]) - Fd0[p] * np.cos(I[p])
   Fm = Fl[p] * np.sin(I[p]) - Fd[p] * np.cos(I[p])
   mtot += Fm 
   Ft1 = Fl1[p] * np.cos(I[p]) + Fd1[p] * np.sin(I[p])
   t1 += Ft1
   Fm1 = Fl1[p] * np.sin(I[p]) - Fd1[p] * np.cos(I[p]) 
   Ft2 = Fl2[p] * np.cos(I[p]) + Fd2[p] * np.sin(I[p])
   t2 += Ft2
   Fm2 = Fl2[p] * np.sin(I[p]) - Fd2[p] * np.cos(I[p]) 
   mom.append(mrad[p] * Fm)
   thrust.append(th)
   mom0.append(mrad[p] * Fm0)
   mom1.append(mrad[p]* Fm1)
   mom2.append(mrad[p] * Fm2)
   thr0.append(t0)
   thr1.append(t1)
   thr2.append(t2)


ttot = ttot * 3
mtot = mtot * 3

print("Total thrust: %.2f\nTotal moment: %.2f\n" % (ttot, mtot))

radius = np.linspace(0, 40, 101, dtype = np.float64)
rn = np.copy(radius)
for k in range(101):
   rn[k] += 3
   linv.append(rn[k]*v)
   

plt.figure(0)
plt.plot(radius, rn)
plt.xlabel("meters")
plt.ylabel("meters")
plt.title("Distance 'r' from axis of rotation in m", loc='center')
plt.savefig('rn.jpeg')
plt.figure(1)
plt.plot(radius, linv)
plt.xlabel("meters")
plt.ylabel("m/s")
plt.title("Blade velocity 'v' in m/s",loc='center')
plt.savefig('Vn.jpeg')
plt.figure(2)
plt.plot(radius, A)
plt.xlabel("meters")
plt.ylabel("m^2")
plt.title("Blade area in m^2", loc='center')
plt.savefig('An.jpeg')
plt.figure(3)
plt.plot(element, I)
plt.xlabel("element #")
plt.ylabel("angle 'I' in degrees")
plt.title("Angle 'I'", loc='center')
plt.savefig('In.jpeg')
plt.figure(4)
plt.plot(radius, w)
plt.xlabel("meters")
plt.ylabel("m/s")
plt.title("Resultant velocity 'w' in m/s", loc='center')
plt.savefig('Wn.jpeg')
plt.figure(5)
plt.plot(element, I)
plt.plot(element, aoa2)
plt.plot(element, aoa3)
plt.xlabel("element #")
plt.ylabel("angle of attack in deg")
plt.title("Angle of attack 'i' in degrees", loc='center')
plt.savefig('in.jpeg')
plt.figure(6)
plt.plot(element, Cl0)
plt.plot(element, Cl1)
plt.plot(element, Cl2)
plt.xlabel("element #")
plt.ylabel("Cl")
plt.title("Coefficient of lift 'Cl' vs element")
plt.savefig('Cl.jpeg')
plt.figure(7)
plt.plot(element, Cd0)
plt.plot(element, Cd1)
plt.plot(element, Cd2)
plt.xlabel("element #")
plt.ylabel("Cd")
plt.title("Coefficient of drag 'Cd' vs element")
plt.savefig('Cd.jpeg')
plt.figure(8)
plt.plot(element, mom0)
plt.plot(element, mom1)
plt.plot(element, mom2)
plt.xlabel("element #")
plt.ylabel("N-m")
plt.title("Moment v Element")
plt.savefig('moment.jpeg')
plt.figure(9)
plt.plot(element, thr0)
plt.plot(element,thr1)
plt.plot(element,thr2)
plt.xlabel("Thrust kN")
plt.ylabel("element #")
plt.savefig('thrust.jpeg')
plt.title("Thrust v Element")
plt.figure(10)
plt.plot(element, mom)
plt.xlabel("element #")
plt.ylabel("Moment")
plt.title("Moment v Element")
plt.savefig('mom_angle.jpeg')
plt.figure(11)
plt.plot(element, thrust)
plt.xlabel("element #")
plt.ylabel("Thrust kN")
plt.title("Thrust v Element")
plt.savefig('thrust_angle.jpeg')
#plt.show()