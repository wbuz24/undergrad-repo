function [value,iter,error] = Bisection(a,b)
% This script solves the non-linear equation f(x) = 0
% using the "Bisection" or "Interval Halving" method.
    
% Halve the interval
c = (a + b)/2;

% Bisection Iterations
f_c = f_x1(c);
k1 = 1;
while (abs(f_c) > 1e-6)
    
    % Calculate function values at the end points
    f_a = f_x1(a);
    f_b = f_x1(b);
    
    % Print out the solution
    %fprintf('Iter %2d: a = %f, b = %f, c = %f, f(c) = %f \n',...
            % k1, a, b, c, f_c);
    
    % Check against the "Intermediate Value Theorem"
    if ((f_a * f_c) < 0)
        b = c;
    else
        a = c;
    end
    
    % Halve the interval
    c = (a + b)/2;
    
    % Calculate the function at the mid-point
    f_c = f_x1(c);
    
    error = abs(f_c - pi);
    value(k1) = f_x1(c);
    iter(k1) = k1;
    % Increment the iterator
    k1 = k1 + 1;
end
end