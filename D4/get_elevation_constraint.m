function [c_ie] = get_elevation_constraint(z,alpha,beta,lambda_t,N,mx)
%Yield the constraint defined by eq22
c_ie = ones(N,1);
for i=0:N-1
    c_ie(i) = alpha*exp(-beta*(z(1+i*mx)-lambda_t)^2)-z(5+i*mx);
end

c_ie
