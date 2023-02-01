%% HW 2
% Will Buziak
% Machine Design
% 2/9/2022

clc
clear all
%% initialize and sort
E = 206.8; %GPa
I = .002025; %m^4
L = 1.8; %m
F1 = 1900; %N 
R1 = 2239.22; %N
R2 = 440.777778; %N
w = 1500; %N/m
x = linspace(0,L,1000);
C3 = [(1900/6)*(x-.2).^3 + (1500/24)*(x-.27).^4 - (2239.22/6)*(x).^3 - (1500/24)*(x-.79).^3 - (440.777778/6)*(x-1.8).^3]/x;

%% Shear, moment, slope & deflection
V_x = R1 - F1.*(x>.2) - w.*(x>.27).*(x-.27) + w.*(x>.79).*(x-.79) + R1.*(x>1.8);
M_x = R1*x - F1.*(x>.2).*(x-.2) - (w/2).*(x>.27).*(x-.27).^2 + (w/2).*(x>.79).*(x-.79).^2 + R1.*(x>1.8).*(x-1.8);
theta_x = (1/(E*I)).*[(R1/2)*x.^2 - (F1/2).*(x>.2).*(x-.2).^2 - (w/6).*(x>.27).*(x-.27).^3 + (w/6).*(x>.79).*(x-.79).^3 + (R1/2).*(x>1.8).*(x-1.8).^2 - C3];
y_x = (1/(E*I)).*[(R1/6)*x.^3 - (F1/6).*(x>.2).*(x-.2).^3 - (w/24).*(x>.27).*(x-.27).^4 + (w/24).*(x>.79).*(x-.79).^4 + (R1/6).*(x>1.8).*(x-1.8).^3 - C3];

%% plot

figure(1)

subplot(4,1,1)
area(x,V_x)
[maxvalue1,i] = max(abs(V_x));
hold on
plot(x(i),V_x(i),'*')
ylabel('V(x) N')
ylim([min([1.2*min(V_x),0,-1.2*min(V_x)]),max([0,1.2*max(V_x),-1.2*max(V_x)])]);
xlim([0,1.2*L])
hold off

subplot(4,1,2)
area(x,M_x)
[maxvalue2,t] = max(abs(M_x));
hold on
plot(x(t),M_x(t),'*')
ylabel('M(x) Nm')
ylim([min([1.2*min(M_x),0,-1.2*min(M_x)]),max([0,1.2*max(M_x),-1.2*max(M_x)])]);
xlim([0,1.2*L])
hold off

subplot(4,1,3)
area(x,theta_x)
[maxvalue3,k] = max(abs(theta_x));
hold on
plot(x(k),theta_x(k),'*')
ylabel('Theta(x)')
ylim([min([1.2*min(theta_x),0,-1.2*min(theta_x)]),max([0,1.2*max(theta_x),-1.2*max(theta_x)])]);
xlim([0,1.2*L])
hold off

subplot(4,1,4)
area(x,y_x)
[maxvalue4,j] = max(abs(y_x));
ylabel('Y(x) mm')
hold on
plot(x(j),y_x(j),'*')
ylim([min([1.2*min(y_x),0,-1.2*min(y_x)]),max([0,1.2*max(y_x),-1.2*max(y_x)])]);
xlim([0,1.2*L])
hold off

%% Q2

m1 = 1862.935; %Nm
R = 5561; %N
d = 8300; %Nm
I2 = 7.85398e-5; % m^4

shear = R - d*x + d.*(x>.67).*(x-.67);
moment = m1 + R*x - (d/2)*x.^2 + (d/2).*(x>.67).*(x-.67).^2;
theta = (1/E*I2).*[m1*x + (R/2)*x.^2 - (d/6)*x.^3 + (d/6).*(x>.67).*(x-.67).^3];
defl = (1/E*I2).*[(m1/2)*x.^2 + (R/6)*x.^3 - (d/24)*x.^4 + (d/24).*(x>.67).*(x-.67).^4];


figure(2)

subplot(4,1,1)
area(x,shear)
[maxvalue5, u] = max(abs(shear));
ylabel('V(x) N')
hold on
plot(x(u),shear(u),'*')
ylim([min([1.2*min(shear),0,-1.2*min(shear)]),max([0,1.2*max(shear),-1.2*max(shear)])]);
xlim([0,1.2*L])
hold off

subplot(4,1,2)
area(x,moment)
[maxvalue6, p] = max(abs(moment));
ylabel('M(x) Nm')
hold on
plot(x(p),moment(p),'*')
ylim([min([1.2*min(moment),0,-1.2*min(moment)]),max([0,1.2*max(moment),-1.2*max(moment)])]);
xlim([0,1.2*L])
hold off

subplot(4,1,3)
area(x,theta)
[maxvalue7, v] = max(abs(theta));
ylabel('Theta(x)')
hold on
plot(x(v),theta(v),'*');
ylim([min([1.2*min(theta),0,-1.2*min(theta)]),max([0,1.2*max(theta),-1.2*max(theta)])]);
xlim([0,1.2*L])
hold off

subplot(4,1,4)
area(x,defl)
[maxvalue8, n] = max(abs(defl));
ylabel('Y(x) mm')
hold on
plot(x(n),defl(n),'*')
ylim([min([1.2*min(defl),0,-1.2*min(defl)]),max([0,1.2*max(defl),-1.2*max(defl)])]);
xlim([0,1.2*L])
hold off

