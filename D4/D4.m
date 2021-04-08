% TTK4135 - Helicopter lab
% Hints/template for problem 3.
% Updated spring 2018, Andreas L. Fl�ten

%% Initialization and model definition
clc 
clear 
init01;

A_c = [0  1          0          0          0          0;
       0  0       -K_2          0          0          0; 
       0  0          0          1          0          0;
       0  0  -K_1*K_pp  -K_1*K_pd          0          0; 
       0  0          0          0          0          1;
       0  0          0          0  -K_3*K_ep  -K_3*K_ed ];

B_c = [       0         0;
              0         0;
              0         0;
       K_1*K_pp         0;
              0         0;
              0  K_3*K_ep ];

% Number of states and inputs
nx = size(A_c, 2);          % Number of states
nu = size(B_c, 2);          % Number of inputs

%% Forward Euler discretization:
delta_t	= 0.25;             % [s]
A_d = eye(nx) + delta_t*A_c;
B_d = delta_t*B_c;

%% Time horizon:
N  = 40;                    % Time horizon for states [MUST CHANGE IN get_elevation_constraint() as well]
M  = N;                     % Time horizon for inputs

n = N*nx+M*nu;

%% Initial values:
lambda_0 = pi;
lambda_f = 0;

x0 = [lambda_0; 0 ; 0; 0; 0; 0];

z  = zeros(n, 1);           % Initialize z for horizon
z0 = z;                     % Initial value for optimization
z(1:nx) = x0; 

%% Bounds

% Might add elevation restriciton also, what about table?
pk      = deg2rad(30);      % Absolute bound on pitch
ul 	    = [-pk, -inf].';    % Lower bound on control
uu 	    = [pk,   inf].';    % Upper bound on control

xl    = -Inf*ones(nx, 1);   % Lower bound on states
xu    =  Inf*ones(nx, 1);   % Upper bound on states
xl(3) = ul(1);              % Lower bound on pitch
xu(3) = uu(1);              % Upper bound on pitch

% Generate constraints on measurements and inputs
[vlb,vub] = gen_constraints(N, M, xl, xu, ul, uu);
vlb(n)    = 0;              % Want the last input to be zero
vub(n)    = 0;              % Want the last input to be zero

%% Matrices in objective function:
q = diag([1 1]);            % Weight on inputs p, e
Q1 = diag([1 0 0 0 0 0]);   % Weight on states

Q = gen_q(Q1, q, N, M);
c = zeros(n, 1);            % Linear term

% Generate the matrix Q and the vector c (objecitve function weights in the QP problem) 
% Qt = diag([1,1,1,1,10, 1]);
% Rt = diag([.1,.1]);
% G = gen_q(Qt,Rt,N,M);                                  % Generate Q, hint: gen_q
% c = zeros((mx+mu)*N,1);                                  % Generate c, this is the linear constant term in the QP

%% LQR
LQR_Q = diag([10; 5; .1; .1; 10; 10]);  %Rank = nx
LQR_R = diag([.1;.1]);                  %Rank = nu

K = dlqr(A_d, B_d, LQR_Q, LQR_R);

%% Linear constraints for objective function:
Aeq = gen_aeq(A_d, B_d, N, nx, nu);
beq = [A_d*x0; 
       zeros(nx*(N-1), 1)];

%% Solve QP problem with linear model
tic
ofun = @(z) 1/2 * z.'* Q * z;

% [z,lambda] = quadprog(G,c,[],[],Aeq,beq,vlb,vub); % hint: quadprog. Type 'doc quadprog' for more info 
options = optimoptions('fmincon','MaxFunctionEvaluations',1e4);
% z = fmincon(ofun, z, [], [], Aeq, beq, vlb,vub,@get_elevation_constraint,options);
z = fmincon(ofun, z, [], [], Aeq, beq, vlb, vub, @get_elevation_constraint, options);

t1=toc;

% Calculate objective value
phi1 = 0.0;
PhiOut = zeros(n, 1);
for i=1:n
  phi1 = phi1 + Q(i, i)*z(i)*z(i);
  PhiOut(i) = phi1;
end

%% Extract control inputs and states from solution
u1  = [z(N*nx+1:nu:end); z(N*nx+M*nu-1)];                
u2  = [z(N*nx+2:nu:end); z(N*nx+M*nu)];

x1 = [x0(1); z(1:nx:N*nx)];              
x2 = [x0(2); z(2:nx:N*nx)];              
x3 = [x0(3); z(3:nx:N*nx)];              
x4 = [x0(4); z(4:nx:N*nx)];
x5 = [x0(5); z(5:nx:N*nx)];          
x6 = [x0(6); z(6:nx:N*nx)]; 

padding_t = 5;      % [s]
padding_n = padding_t/delta_t;

zero_padding = zeros(padding_n, 1);
unit_padding  = ones(padding_n, 1);

u1  = [zero_padding;           u1;  zero_padding];
u2  = [zero_padding;           u2;  zero_padding];
x1  = [lambda_0*unit_padding;  x1;  zero_padding];
x2  = [zero_padding;           x2;  zero_padding];
x3  = [zero_padding;           x3;  zero_padding];
x4  = [zero_padding;           x4;  zero_padding];
x5  = [zero_padding;           x5;  zero_padding];
x6  = [zero_padding;           x6;  zero_padding];

x = [x1 x2 x3 x4 x5 x6];
u = [u1 u2];

time_steps = [0:delta_t:(N + 2*padding_n)*delta_t];
ts_u = timeseries(u, time_steps);
ts_x = timeseries(x, time_steps);

%% Plotting


t = 0:delta_t:delta_t*(length(u)-1);
alpha = 0.2;
beta = 20;
N = 40;
lambda_t = 2/3*pi;
mx = 6;

% [c,ceq] = get_elevation_constraint(z);

econ = zeros(length(x1),1);
for i = 1 : length(x1)
    econ(i) = alpha*exp(-beta*(x1(i)-lambda_t)^2);
%     econ(1+i) = alpha*exp(-beta*(z(1+i*mx)-lambda_t)^2);
end

plot(econ)
% 
% 
figure(1)
subplot(711)
stairs(t,u),grid
ylabel('u')
hold on
subplot(712)
plot(t,x1,'m',t,x1,'mo'),grid
ylabel('lambda')
hold on
subplot(713)
plot(t,x2,'m',t,x2','mo'),grid
ylabel('r')
hold on
subplot(714)
plot(t,x3,'m',t,x3,'mo'),grid
ylabel('p')
hold on
subplot(715)
plot(t,x4,'m',t,x4','mo'),grid
hold on
subplot(716)
plot(t,x5,'m',t,x5','mo'),grid
ylabel('e')
hold on
subplot(717)
plot(t,x6,'m',t,x6','mo'),grid
xlabel('tid (s)'),ylabel('edot')
hold on





