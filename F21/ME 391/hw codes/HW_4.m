clc
clear all

x = [0, 2, 4, 6, 9, 11, 12, 15, 17, 19];
y = [5, 6, 7, 6, 9, 8, 8, 10, 12, 12];

xset = linspace(0,20);
a1 = 8.143 + .0166*xset;
a2 = 9.3199 + .0217*xset;

scatter(x,y)
hold on
plot(xset,a1,'.k')
plot(xset,a2,'-r')
legend('(x,y)', 'f(x) = y', 'f(y) = x')