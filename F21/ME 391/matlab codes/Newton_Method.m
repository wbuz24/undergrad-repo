close all
clear
clc
format long

% Code to solve 
%
% f(x,y) = x^2 + y^2 - 4 = 0
% g(x,y) = (x-2)^2 + (y+1)^2 - 9 = 0
%
% using the "Newton's" method

% Initial guesses
x = 2.0;
y = 3.0;

% convergence threshold
epsilon = 1e-7;

% iteration counter
k = 0;

% Print out the values
fprintf('Itr %d: x = %15.10f, y = %15.10f  => f(x,y) = %15.10f, g(x,y) = %15.10f \n',k,x,y,f(x,y),g(x,y));

% Newton iterations
while ( (abs(f(x,y)) > epsilon) || (abs(g(x,y)) > epsilon) )
    
    % increment iteration counter
    k = k + 1;
    
    % Setup Ax = b linear system to solve for changes (dx, dy)
    A = Jacobian_matrix(x,y);
    b = [-f(x,y); -g(x,y)];
    
    % changes = [dx; dy]
    changes = A\b;
    dx = changes(1);
    dy = changes(2);
    
    % Newton's update formula
    % x_new = x_old + dx
    % y_new = y_old + dy
    x = x + dx;
    y = y + dy;
    
    % Print out the values
    fprintf('Itr %d: x = %15.10f, y = %15.10f  => f(x,y) = %15.10f, g(x,y) = %15.10f \n',k,x,y,f(x,y),g(x,y));
    
% goto next iteration
end
