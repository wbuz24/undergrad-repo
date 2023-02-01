function [value,iter,error] = Secant(x1,x2)

% This script solves the non-linear equation f(x) = 0
% using the "Secant" method.

% Example problem:
% f(x) = x * cos(x/2) = 0

% Initial guesses
    
% Secant Iterations
fx = f_x1(x2);
k2 = 1;
while (abs(fx) > 1e-7)
    
    % Approximate the 1st derivative of f(x)
    f_prime_x_approx = (f_x1(x2) - f_x1(x1))/(x2 - x1);
    
    % Newton update formula
    x3 = x2 - (f_x1(x2)/f_prime_x_approx);
    
    % Calculate the function at the new point
    fx = f_x1(x3);
    
    % Print out the solution
    %fprintf('Iter %2d: x = %10.7f, f(x) = %12.9f \n',...
         %    k2, x3, fx);
         
    % Calculate error
    error = abs(x3 - pi);
         
    % Swap variables for the next iteration
    x1 = x2;
    x2 = x3;
    value(k2)  = f_x1(x3);
    iter(k2) = k2;
    % Increment the iterator
    k2 = k2 + 1;
    
end

end
