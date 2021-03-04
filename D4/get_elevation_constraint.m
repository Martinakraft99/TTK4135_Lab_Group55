function [c_ie] = get_elevation_constraint(x,alpha,beta,lambda_t)
%Yield the constraint defined by eq22
c_ie = alpha*exp(-beta*(x(1)-lambda_t)^2)-x(5);

end

