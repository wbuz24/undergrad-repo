%% HW 3
clear
close all
clc
%% Bisection
[valueb1,iterb1,errorb1] = Bisection(-7,-5);
[valueb2,iterb2,errorb2] = Bisection(-5,-3);

%% Secant 
[values1,iters1,errors1] = Secant(-7,-5);
[values2,iters2,errors2] = Secant(-5,-3);


semilogy(iterb1, valueb1);
xlim([0 length(iterb1)]);

fprintf('Iter %2d: error: %f, Iter %2d: error= %f, Iter %2d: error= %f, Iter %2d: error= %f, \n',...
             iterb1,errorb1,iterb2,errorb2,...
             iters1,errors1,iters2,errors2);
         
hold on
%% plot


semilogy(valueb2,iterb2);

semilogy(values1,iters1);

semilogy(values2,iters2);

legend('Bisection1','Bisection2','Secant1','Secant2');

[valuen1,itern1] = Newtons(2);
[valuen2,itern2] = Newtons(4);

fprintf('Iter %2d: #, of digits: %f, Iter %2d: # of digits: %f', ...
             iters1,values1,itern1,valuen1);


hold off;


