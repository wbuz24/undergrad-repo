clear 
clc 
close all 

% initialize 
m = 10; 
b = 1; 
k = 5; 
x0 = 1; 
v0 = 0; 
h = .5; 
b_eq = b/m; 
omega_n = sqrt(k/m); 
zeta = b/(2*sqrt(m*k)); 
omega_d = omega_n*sqrt(1-zeta^2); 
t = 0:.5:50; 
x = zeros(1,101); 
x(1) = 1; 

% analytical
xdouble = (1/m)*(-k*1); 
x(2) = 1 +xdouble*((h^2)/2); 
x_analytical = (((v0+zeta*omega_n*x0)/omega_d)*sin(omega_d.*t)+x0*cos(omega_d.*t)).*exp(- zeta*omega_n.*t); 


for i = 2:length(t)-1 
 x(i+1) = (1/((m/(h^2))+(b/(2*h))))*(-k*x(i)+b*x(i-1)/(2*h)-(m/h^2)*(x(i-1)-2*x(i)));   
 
end 

for i = 1:length(t)
xa(i) = (exp(-zeta*omega_n*t(i)))*((zeta*omega_n/omega_d)*sin(omega_d*t(i))+cos(omega_d*t(i))); 
end 


% plot 
plot(t,x) 
hold on 
plot(t,xa) 
xlabel('time') 
ylabel('x') 
title('analytical v. numerical') 
legend('numerical''analytical') 
