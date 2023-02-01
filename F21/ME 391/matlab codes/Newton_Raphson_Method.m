close all
clear
clc
format long

% This script solves the non-linear equation f(x) = 0
% using the "Newton-Raphson" method.

% Example problem:
% f(x) = x * cos(x/2) = 0

% Initial guess
x = 2.0;

% Newton's Iterations
fx = f_x(x);
k = 1;
while (abs(fx) > 1e-7)

    % Newton update formula
    x = x - (f_x(x)/f_prime_x(x));

    % Calculate the function at the new point
    fx = f_x(x);

    % Print out the solution
    fprintf('Iter %2d: x = %10.7f, f(x) = %12.9f \n',...
             k, x, fx);

    % Calculate error
    error = abs(x - pi);

    % Increment the iterator
    k = k + 1;

end
