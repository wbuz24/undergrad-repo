clear all
clc
clear
format long

% initialize t
x = -1:.05:5;

% initial function
f_initial = x.*sin(x);

f0 = zeros(length(x),1);
f1 = -pi.*(x-pi);
f2 = -pi.*(x-pi)-(x-pi).^2;
f3 = -pi.*(x-pi)-(x-pi).^2-(((x-pi).^3)/6)*pi;

% plot
plot(x,f_initial,'k','linewidth',3);
hold

plot(x,f0,'r','linewidth',2);
plot(x,f1,'b','linewidth',2);
plot(x,f2,'g','linewidth',2);
plot(x,f3,'--m','linewidth',2);

plot(pi,0,'ok','linewidth',2);

legend('f(x)','deg-0 approx.','deg-1 approx.','deg-2 approx.','deg-3 approx.','Location','NorthEast','fontsize',13);
xlim([-1 5])
ylim([-5 25])