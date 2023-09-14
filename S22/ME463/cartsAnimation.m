% Caleb Williams (5/9/19)
% Creates an animation of two carts connected with springs and dashpots.
clear all; close all; clc;

% Problem parameters
k1=50; % cart 1 spring constant (N/m)
k2=50; % cart 2 spring constant (N/m)
b1=1; % cart 1 viscous damping coefficient (kg/s)
b2=1; % cart 2 viscous damping coefficient (kg/s)
m1=5; % cart 1 mass (kg)
m2=5; % cart 2 mass (kg)
x10=.7; % cart 1 initial position (m)
x20=1; % cart 2 initial position (m)
v10=0; % cart 1 initial velocity (m/s)
v20=0; % cart 2 initial velocity (m/s)

% Set time step stuff
simTime=9; % simulation time (s)
tStep=0.01; % simulation time step
iterations=simTime/tStep;
t=0:iterations;

% Pre-allocate variables for speed
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

% Set up video
v=VideoWriter('masses.avi');
v.FrameRate=100;
open(v);

% Begin iterative process of solving the ODE's with Euler's Method
for n=2:(iterations+1)
    
  x1(n,:)=x1(n-1,:)+v1(n-1,:)*tStep;
  x2(n,:)=x2(n-1,:)+v2(n-1,:)*tStep;
  v1(n,:)=v1(n-1,:)+a1(n-1,:)*tStep;
  v2(n,:)=v2(n-1,:)+a2(n-1,:)*tStep;
  a1(n,:)=-(b1*v1(n,:)-b2*(v2(n,:)-v1(n,:))+k1*x1(n,:)-k2*(x2(n,:)-x1(n,:)))/m1;
  a2(n,:)=-(b2*(v2(n,:)-v1(n,:))+k2*(x2(n,:)-x1(n,:)))/m2;
  
  % Plot everything for the video
  subplot(2,1,1)
  hold on;
  plot(t(:,1:n),x1(1:n,:),'b')
  plot(t(:,1:n),x2(1:n,:),'r')
  xlim([0 iterations])
  ylabel('Mass Position (m)')
  legend('Mass 1','Mass 2')
  title('Two Spring-Mass System by Caleb Williams');
  subplot(2,1,2)
  hold on;
  fill([0 7 7 0],[0 0 1.5 1.5],'w'); % clears background
  plot([0 x2(n,:)+5.5],[0.75 0.75],'bl'); % springs
  fill([x1(n,:)+2 x1(n,:)+3 x1(n,:)+3 x1(n,:)+2],[0 0 1 1],'r'); % mass 1
  fill([x2(n,:)+5 x2(n,:)+6 x2(n,:)+6 x2(n,:)+5],[0 0 1 1],'r'); % mass 2
  fill([0 0.1 0.1 0],[0 0 1 1],[0.5 0.5 0.5]);
  xlim([0 7]);
  ylim([0 1.5]);
  frame=getframe(gcf);
  writeVideo(v,frame)
  
end

close(v);


