% HW 1
% Will Buziak
% Thermodynamics

%Plot the equation for pressure distribution for #'s 5 & 6,
%between 0 & h

%% Problem 5

%% initialize
m = 15; % kg
A = .05; % m^2
h = .05; % m
Z_l = .2; %m
rho = 997; %kg/m^3
g = 9.81; % m/s^2

z = 0:.01:.5;
pressure = 101325 + (m*g)/A + 104268.*(z<.5) + 997*9.81.*(z<.2);

%% plot 

plot(z,pressure)
xlim([0,.5])
ylim([1,2.3e5])

close

%% Problem 6

height = 5; % m
alpha = .007; %s^2/m^2

y = 0:.1:5;
p = 101325 + 709.275*9.81.*(y<5);

%% plot
plot(y,p)
xlim([0,5])

