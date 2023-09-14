clear 
close all 
clc 
m = 10; 
l = 1; 
g = 9.8; 
t = linspace(0,10,100); 
x = zeros(size(t)); 
% calculations
h = t(2-t(1)); 
xdouble = zeros(size(t)); 
x(1) = deg2rad(179);
xdouble(1) = -sin(x(1))*g/l; 

for i = 1:length(t)-1 
 xdouble(i+1) = xdouble(i) + -h*g*sin(x(i))/l;  x(i+1) = xdouble(i)*h + x(i); 
  
end 

%plot
yyaxis left 
plot(t,x) 
hold on 
xlabel('time') 
ylabel('theta') 
yyaxis right 
plot(t,xdouble) 
ylabel('theta derivative')

