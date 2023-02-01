%% Project 4: ME 463
clear
clc

%% initial conditions
m = 1;
k = 3;

t = 0:.5:100;

x0 = [1;
      -1];
v01 = 0;
v02 = 0;
vdot0 = [v01;
         v02];
    

%% Modal analysis

% M^(-1/2)
Mi = [1/m, 0
        0, 1/m];
% K matrix
K = [2*k, -k;
     -k, 2*k];
% K ~
Kt = Mi*K*Mi;

% lambda 
lambda = eig(Kt);

% find V matrices
n1 = sqrt(((-2*k)/m - lambda(1)).^2 + (k/m).^2);
V1 = [(k/m)/n1;
      (-2*k/m)/n1];

n2 = sqrt(((-2*k)/m - lambda(2)).^2 + (k/m).^2);
V2 = [(k/m)/n2;
      (-2*k/m)/n2];

w1 = sqrt(k/m);
w2 = sqrt(3*k/m);

P = [V1, V2];

Pt = transpose(P);

r0 = Pt*Mi*x0;
rdot0 = Pt*Mi*vdot0;

r1 = sqrt(((w1.^2)*r0(1) + rdot0(1))/w1) * sin(w1*t + atan((w1*r0(1))/rdot0(1)));
r2 = sqrt(((w2.^2)*r0(2) + rdot0(2))/w2) * sin(w2*t + atan((w2*r0(2))/rdot0(2)));

r = [r1;
     r2];
x_t = Mi*P*r;

x1 = x_t(1,:);
x2 = x_t(2,:);

figure(1)

plot(t,x1)



