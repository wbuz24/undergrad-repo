close all
clear
clc
%% SOR
% This script solves an (nxn) system of linear equations
% using the "Successive-Over-Relaxation (SOR)" method.

% Example problem (Diagonally-Dominant Tridiagonal System):
% 4x_1 -  x_2        = 100
% -x_1 + 4x_2 -  x_3 = 200
%      -  x_2 + 4x_3 = 100

% System definition
n = 3;
A = [ .6536 .0575  .0095 ; ...     
    .2411  .8725 .1062 ; ...     
    .0004 .1986  .2331 ];
b = [ .5691; ...      
    .4626; ...      
    .2146];%

% Initial guess
x = zeros(n,1);

% Over-Relaxation Factor
omega = 1.03;

% SOR iterations
numItr = 0;

% old and new solutions
x_old = x;
x_new = x_old;

% Residual vector
R = zeros(n,1);

% iterative loop
Error = 10;
epsilon = 1e-8;
k = 1;
while (Error > epsilon)
    
    % loop over equations
    for i = 1:n
    
        % calculate summation term number 1
        % Sum_{j = 1:i-1} a_ij * x_j^(k+1)
        sum1 = 0.0;
        for j = 1:i-1
           sum1 = sum1 + A(i,j)*x_new(j);
        end
        
        % calculate summation term number 2
        % Sum_{j = i:n} a_ij * x_j^(k)
        sum2 = 0.0;
        for j = i:n
           sum2 = sum2 + A(i,j)*x_old(j);
        end
        
        % calculate residual term
        % R_i = (1/a_ii)*(b_i - sum1 - sum2)
        R(i) = (1/A(i,i))*(b(i) - sum1 - sum2);
        
        % update solution
        % x^(k+1) = x^(k) + omega * R^(k,k+1)
        x_new(i) = x_old(i) + omega*R(i);
    end
    
    % print new solution & current residual
    fprintf('Iter %2d: x(1)= %f, x(2)= %f, x(3)= %f, R = (%10.6f,%10.6f,%10.6f) -> norm(R)= %e \n',...
             k,x_new(1),x_new(2),x_new(3),...
             R(1),R(2),R(3),norm(R));
         
    % calculate error
    Error(k) = norm(R);
    numItr(k) = k;
    % increment iterator
    k = k + 1;
    
    
    % swap solutions for the next iteration
    x_old = x_new;
end

semilogy(numItr,Error)
xlim([0 9])
ylim([0 .5])
numItr = k
