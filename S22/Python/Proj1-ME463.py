# Project 2
# ME 463
# Make a video of a wave pendulum

import numpy as np
from scipy.integrate import odeint
import matplotlib.pyplot as plt
import math
import matplotlib.animation as animate 


# define an ode model
def model(theta,t,b,g,l,m):
    theta1 = theta[0]
    theta2 = theta[1]
    dtheta1_dt = theta2
    dtheta2_dt = - (g/l)*math.sin(theta1)
    dtheta_dt = [dtheta1_dt, dtheta2_dt]
    return dtheta_dt

# initialize parameters
#damping
b = .05

#acceleration of gravity
g = 9.81

#length of string
l = 1
l1 = 1.1
l2 = 1.2
l3 = 1.3
l4 = 1.4

#mass of bob
m = 1

#initial condition
theta_0 = [0,5]

#time
t = np.linspace(0,10,100)

#solve ODE
theta_a = odeint(model,theta_0,t,args = (b,g,l,m))
#theta_b = odeint(model,theta_0,t,args = (b,g,l1,m))
#theta_c = odeint(model,theta_0,t,args = (b,g,l2,m))
#theta_d = odeint(model,theta_0,t,args = (b,g,l3,m))
#theta_e = odeint(model,theta_0,t,args = (b,g,l4,m))

#plot results
plt.figure()
plt.plot(t,theta_a[:,0],'b-',label = r'${x1(t)}$')
#plt.plot(t,theta_b[:,0],'b-', label = r'${x2(t)}$')
#plt.plot(t,theta_c[:,0],'b-', label = r'${x3(t)}$')
#plt.plot(t,theta_d[:,0],'b-', label = r'${x4(t)}$')
#plt.plot(t,theta_e[:,0],'b-', label = r'${x5(t)}$')


plt.plot(t,theta_a[:,1],'r--',label = r'${v1(t)}$')
#plt.plot(t,theta_b[:,1],'r--',label = r'${v2(t)}$')
#plt.plot(t,theta_c[:,1],'r--',label = r'${v3(t)}$')
#plt.plot(t,theta_d[:,1],'r--',label = r'${v4(t)}$')
#plt.plot(t,theta_e[:,1],'r--',label = r'${v5(t)}$')

plt.ylabel('y-distance')
plt.xlabel('time')
plt.legend(loc='best')
plt.show()

#animation
Writer = animate.writers['ffmpeg']
writer = Writer(fps=10, metadata=dict(artist='Will Buziak'), bitrate = -1)
fig = plt.figure(figsize=(g, 5),facecolor = 'w')
ax = fig.add_subplot(1, 1, 1)
#l, = ax.plot([], [], 'r-')
#ax1 = ax.twinx()
#l1, = ax1.plot([],[], 'r-')
#ax2 = ax.twinx()
#l2, = ax2.plot([], [], 'r-')
#ax3 = ax.twinx()
#l3, = ax3.plot([], [], 'r-')
#ax4 = ax.twin()
#l4, = ax4.plot([], [], 'r-')




#plt.rcParams['font.size'] = 15

lns = []
for i in range(len(theta_a)):
    
    #plot string
    ln, = ax.plot([0, np.sin(theta_a[i,0])], [0, -np.cos(theta_a[i,0])], color='r', lw=2)
    
    #plot bob
    bob, = ax.plot(np.sin(theta_a[i,0]), -np.cos(theta_a[i,0]), 'o', markersize=20,color='k')
    
    #plot time
    tm = ax.text(-.9,.25, 'Time = %.1fs' % t[i])
    lns.append([ln, bob, tm])
    

#save the animation
ani = animate.FuncAnimation(fig, model, frames=100, fargs=(theta_a, ln,bob))
fn = 'Pendulum_Animation_Project_1'
ani.save(fn+'.png',writer,fps = 1000/50)
plt.close()