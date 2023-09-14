function [valuef,valueg] = HW_3_p4(x,y)
% Code to solve 
%
% f(x,y) = x^2 + y^2 - 4 = 0
% g(x,y) = (x-2)^2 + (y+1)^2 - 9 = 0
%
% using the "Newton's" method

% convergence threshold
epsilon = 1e-7;

% iteration counter
k4 = 0;

% Print out the values

% Newton iterations
while ( (abs(f(x,y)) > epsilon) || (abs(g(x,y)) > epsilon) )
    
    % increment iteration counter
    k4 = k4 + 1;
    
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
    
    
% goto next iteration
end
valuef = f(x,y);
valueg = g(x,y);
end    

