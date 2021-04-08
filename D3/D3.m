% TTK4135 - Helicopter lab
% Hints/template for problem 2.
% Updated spring 2018, Andreas L. Fl�ten

%% Initialization
clc 
clear 
init01;

%% Continuous time state space:
A_c = [0  1          0          0;
       0  0       -K_2          0; 
       0  0          0          1;
       0  0  -K_1*K_pp  -K_1*K_pd ];

B_c = [0  0  0  K_1*K_pp].';

nx = size(A_c, 2);          % Number of states
nu = size(B_c, 2);          % Number of inputs

%% Forward Euler discretization:
delta_t	= 0.25;             % [s]
A_d = eye(nx) + delta_t*A_c;
B_d = delta_t*B_c;

%% Time horizon:
N  = 100;                   % Time horizon for states
M  = N;                     % Time horizon for inputs

n = N*nx+M*nu;

%% Bounds:
pk    = deg2rad(30);        % Absolute bound on pitch
ul 	  = -pk;                % Lower bound on control
uu 	  =  pk;                % Upper bound on control

xl    = -Inf*ones(nx, 1);   % Lower bound on states
xu    =  Inf*ones(nx, 1);   % Upper bound on states
xl(3) = ul;                 % Lower bound on pitch
xu(3) = uu;                 % Upper bound on pitch

% Bounds on states and inputs
[vlb, vub] = gen_constraints(N, M, xl, xu, ul, uu);
vlb(n)     = 0;             % Want the last input to be zero
vub(n)     = 0;             % Want the last input to be zero

%% Initial values:
lambda_0 = pi;
lambda_f = 0;

x0 = [lambda_0; 0 ; 0; 0];

z  = zeros(n, 1);           % Initialize z for horizon
z0 = z;                     % Initial value

%% Matrices in objective function:
q = 1;                      % Weight on input (0.1, 1, 10)
Q1 = diag([1 0 0 0]);       % Weight on states

Q = gen_q(Q1, q, N, M);
c = zeros(n, 1);            % Linear term

%% Linear constraints for objective function:
Aeq = gen_aeq(A_d, B_d, N, nx, nu);
beq = [A_d*x0; 
       zeros(nx*(N-1), 1)];
   
%% LQR
LQR_Q = diag([10; 5; .1; .1]);  %Rank = nx
LQR_R = diag(.1);               %Rank = nu

K = dlqr(A_d, B_d, LQR_Q, LQR_R);

%% Solve QP problem with linear model
tic
[z, lambda] = quadprog(2*Q, c, [], [], Aeq, beq, vlb, vub);
t1=toc;

% Calculate objective value
phi1 = 0.0;
PhiOut = zeros(n, 1);
for i=1:n
  phi1 = phi1 + Q(i, i)*z(i)*z(i);
  PhiOut(i) = phi1;
end

%% Extract control inputs and states from solution
u  = [z(N*nx+1:n); z(n)];   % Control input
x1 = [x0(1); z(1:nx:N*nx)];              
x2 = [x0(2); z(2:nx:N*nx)];              
x3 = [x0(3); z(3:nx:N*nx)];              
x4 = [x0(4); z(4:nx:N*nx)];              

padding_t = 5;      % [s]
padding_n = padding_t/delta_t;

zero_padding = zeros(padding_n, 1);
unit_padding  = ones(padding_n, 1);

u   = [zero_padding;            u;  zero_padding];
x1  = [lambda_0*unit_padding;  x1;  zero_padding];
x2  = [zero_padding;           x2;  zero_padding];
x3  = [zero_padding;           x3;  zero_padding];
x4  = [zero_padding;           x4;  zero_padding];

x = [x1 x2 x3 x4];

%% Export to simulink
time_steps = [0:delta_t:(N + 2*padding_n)*delta_t].';
ts_u = timeseries(u, time_steps);
ts_x = timeseries(x, time_steps);

%% Plotting
t = 0:delta_t:delta_t*(length(u)-1);

figure(2)
subplot(511)
stairs(t,u),grid
ylabel('u')
subplot(512)
plot(t,x1,'m',t,x1,'mo'),grid
ylabel('lambda')
subplot(513)
plot(t,x2,'m',t,x2','mo'),grid
ylabel('r')
subplot(514)
plot(t,x3,'m',t,x3,'mo'),grid
ylabel('p')
subplot(515)
plot(t,x4,'m',t,x4','mo'),grid
xlabel('tid (s)'),ylabel('pdot')

%% Values to be used in plotting:

lambdaQ01 = x1;


