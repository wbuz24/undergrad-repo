function [value,iter] = Newstons(x)
% This script solves the non-linear equation f(x) = 0
% using the "Newton-Raphson" method.

% Example problem:
% f(x) = x * cos(x/2) = 0
% Newton's Iterations
fx = f_x(x);
k3 = 1;
while (abs(fx) > 1e-6)

    % Newton update formula
    x = x - (f_x(x)/f_prime_x(x));

    % Calculate the function at the new point
    fx = f_x(x);


    % Calculate error
    error = abs(x - pi);
    iter(k3) = k3;
    % Increment the iterator
    k3 = k3 + 1;

end
value(k3) = error;


end