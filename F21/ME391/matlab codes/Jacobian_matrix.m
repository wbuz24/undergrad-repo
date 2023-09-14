function out = Jacobian_matrix(x,y)
%
% Calculates the Jacobian matrix
%

out = zeros(2,2);

out(1,1) = 2*x;
out(1,2) = 2*y;
out(2,1) = 2*(x-2);
out(2,2) = 2*(y+1);

end

