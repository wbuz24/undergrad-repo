% Caleb Williams (5/9/19)
% Calculates the position, velocity, and acceleration as a function of time
% of a system of carts connected by springs and dashpots. Euler's Method is
% used to solve the equations of motion numerically.
clear all; close all; clc;
tic

% Problem parameters
k1=50; % cart 1 spring constant (N/m)
k2=50; % cart 2 spring constant (N/m)
b1=1; % cart 1 viscous damping coefficient (kg/s)
b2=1; % cart 2 viscous damping coefficient (kg/s)
m1=5; % cart 1 mass (kg)
m2=5; % cart 2 mass (kg)
x10=1; % cart 1 initial position (m)
x20=-1; % cart 2 initial position (m)
v10=0; % cart 1 initial velocity (m/s)
v20=0; % cart 2 initial velocity (m/s)

% Set time step stuff
simTime=10; % simulation time (s)
tStep=0.001; % simulation time step
iterations=simTime/tStep;
t=0:iterations;

% Pre-allocate variables for speed and add initial conditions
x1=zeros(iterations,1);
x1(1,:)=x10;
x2=zeros(iterations,1);
x2(1,:)=x20;
v1=zeros(iterations,1);
v1(1,:)=v10;
v2=zeros(iterations,1);
v2(1,:)=v20;
a1=zeros(iterations,1);
a1(1,:)=-(b1*v10-b2*(v20-v10)+k1*x10-k2*(x20-x10))/m1;
a2=zeros(iterations,1);
a2(1,:)=-(b2*(v20-v10)+k2*(x20-x10))/m2;

% Solve the ODE's with Euler's Method
for n=2:(iterations+1)
  x1(n,:)=x1(n-1,:)+v1(n-1,:)*tStep; % cart 1 position
  x2(n,:)=x2(n-1,:)+v2(n-1,:)*tStep; % cart 2 position
  v1(n,:)=v1(n-1,:)+a1(n-1,:)*tStep; % cart 1 velocity
  v2(n,:)=v2(n-1,:)+a2(n-1,:)*tStep; % cart 2 velocity
  % Find cart accelerations
  a1(n,:)=-(b1*v1(n,:)-b2*(v2(n,:)-v1(n,:))+k1*x1(n,:)-k2*(x2(n,:)-x1(n,:)))/m1;
  a2(n,:)=-(b2*(v2(n,:)-v1(n,:))+k2*(x2(n,:)-x1(n,:)))/m2;
end


% Plot results
subplot(3,1,1)
hold on;
plot(t',x1,'r')
plot(t',x2,'m')
ylabel('Position (m)')
title('Position, Velocity, & Acceleration as a Function of Time')
legend('Mass 1','Mass 2')
subplot(3,1,2)
hold on;
plot(t',v1,'b')
plot(t',v2,'c')
ylabel('Velocity (m/s)')
legend('Mass 1','Mass 2')
subplot(3,1,3)
hold on;
plot(t',a1,'g')
plot(t',a2,'y')
ylabel('Acceleration (m/s^2)')
xlabel('time (iterations)')
legend('Mass 1','Mass 2')

toc

