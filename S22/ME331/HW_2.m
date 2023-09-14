%% HW 2
% Will Buziak
% Thermodynamics
% 2/9/2022
clc
clear all
%% initialize and sort
values = [0.010  101.33 
0.028  27.63 
0.047  11.26 
0.065  7.56 
0.083  6.17 
0.102  4.15 
0.120  3.51];

n=7;
volume = values(:,1);
pressure = values(:,2);
%% variable manipulation

y = log(pressure);
x = log(volume);
% a = log(A);

plot(x,y,'.')
hold on
p = polyfit(x,y,1);
p1 = polyval(p,x);
plot(x,p1)



