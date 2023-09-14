close all
clear
clc
format long

% This script solves the non-linear equation f(x) = 0
% using the "Bisection" or "Interval Halving" method.

% Example problem:
% f(x) = x * cos(x/2) = 0

% Initial guesses
a = 1.0;
b = 5.0;
    
% Halve the interval
c = (a + b)/2;

% Bisection Iterations
f_c = f_x(c);
k = 1;
while (abs(f_c) > 1e-7)
    
    % Calculate function values at the end points
    f_a = f_x(a);
    f_b = f_x(b);
    
    % Print out the solution
    fprintf('Iter %2d: a = %f, b = %f, c = %f, f(c) = %f \n',...
             k, a, b, c, f_c);
    
    % Check against the "Intermediate Value Theorem"
    if ((f_a * f_c) < 0)
        b = c;
    else
        a = c;
    end
    
    % Halve the interval
    c = (a + b)/2;
    
    % Calculate the function at the mid-point
    f_c = f_x(c);
    
    % Increment the iterator
    k = k + 1;
    
end
