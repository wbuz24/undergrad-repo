function out = Jacobian_matrix(x,y)
%
% Calculates the Jacobian matrix
%

out = zeros(2,2);

out(1,1) = 1-2*x;
out(1,2) = -1;
out(2,1) = 5*y-2*x;
out(2,2) = 1+5*x;

end
