close all
clc
clear

%% jacobi iteration
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
% old and new solutions
x_old = x;
x_new = x_old;
% Residual vector
R = zeros(n,1);
% Jacobi Iterations
numIter = 0;
% iterative loop
Error = 10;
epsilon = 1e-8;
k = 0; 
fprintf('Itr %d: x(1)= %f, x(2)= %f, x(3)= %f \n',...        
  k,x_new(1),x_new(2),x_new(3));
while (Error > epsilon)
  % increment iterator    
  k = k + 1; 
  
  for i = 1:n        
      % calculate summation term        
      % % Sum_{j = 1:n} a_ij * x_j        
   sum = 0.0;        
   for j = 1:n           
       sum = sum + A(i,j)*x_old(j);       
   end        
   % calculate residual term       
   % R_i = (1/a_ii)*(b_i - sum)        
   R(i) = (1/A(i,i))*(b(i) - sum);
   
    % update solution        
       % x^(k+1) = x^(k) + R^(k)        
       % x^(new) = x^(old) + R^(old)        
       x_new(i) = x_old(i) + R(i);    
         
  
  end
  
   % print new solution & current residual    
 fprintf('Iter %2d: x(1)= %f, x(2)= %f, x(3)= %f, R = (%10.6f,%10.6f,%10.6f) -> norm(R)= %e \n',...             
        k,x_new(1),x_new(2),x_new(3),...        
       R(1),R(2),R(3),norm(R));    
  % recalculate error value    
  Error(k) = norm(R);
  numItr(k) = k;
  % swap solutions for the next iteration (swap old and new solutions)    
  x_old = x_new;
  
end
semilogy(numItr,Error)
xlim([0 21])
ylim([0 .5])
numItr = k

       
  

  