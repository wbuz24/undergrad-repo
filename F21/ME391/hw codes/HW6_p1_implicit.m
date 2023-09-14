close all
clear
clc
format long

% This script solves the non-linear equation f(x) = 0
% using the "Newton-Raphson" method.

%f(t,y) = y' = y +2*t - t^2

% Initial guess
x = -1;
t = .1:.1:.6;
% Newton's Iterations
fx = f_x(x,t);
k = 1;
while (abs(fx) > 1e-12)

    % Newton update formula
    x = x - (f_x(x,t)/f_prime_x(x));

    % Calculate the function at the new point
    fx = f_x(x,t);

    % Print out the solution
    fprintf('Iter %2d: x = %10.7f, f(x) = %12.9f \n',...
             k, x, fx);

    % Calculate error
    error = abs(x - (exp(t)));

    % Increment the iterator
    k = k + 1;

end
