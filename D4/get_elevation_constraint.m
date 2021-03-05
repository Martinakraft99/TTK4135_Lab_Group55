function [c, ceq] = get_elevation_constraint(z)
%Yield the constraint defined by eq22


alpha = 0.2;
beta = 20;
N = 40;
lambda_t = 2/3*pi;
mx = 6;

c = zeros(N,1);
ceq = zeros(N,1);

for i=0:N-1
    c(i+1) = alpha*exp(-beta*(z(1+i*mx)-lambda_t)^2)-z(5+i*mx);
end


end