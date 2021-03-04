%% Initialization and model definition
clc 
clear all
init01; % Change this to the init file corresponding to your helicopter

A_c = [0 1 0 0 0 0;0 0, -K_2 0 0 0; 0 0 0 1 0 0;0 0, -K_1*K_pp, -K_1*K_pd 0 0;0 0 0 0 0 1;0 0 0 0, -K_3*K_ep, -K_3*K_ed];

B_c = [0 0;0 0;0 0;K_1*K_pp 0;0 0;0, K_3*K_ep];

% Number of states and inputs
mx = size(A_c,2); % Number of states (number of columns in A)
mu = size(B_c,2); % Number of inputs(number of columns in B)

% Discrete time system model. x = [lambda r p p_dot]'
delta_t	= 0.25; % sampling time
A_d = eye(mx) + delta_t*A_c;
B_d = B_c*delta_t;



% Initial values
x1_0 = 1;                               % Lambda
x2_0 = 0;                               % r
x3_0 = 0;                               % p
x4_0 = 0;                               % p_dot
x5_0 = 0;                               % e
x6_0 = 0;                               %e_dot
x0 = [x1_0 x2_0 x3_0 x4_0 x5_0 x6_0]';           % Initial values

% Time horizon and initialization
N  = 100;                                  % Time horizon for states
M  = N;                                 % Time horizon for inputs
z  = zeros(N*mx+M*mu,1);                % Initialize z for the whole horizon
z0 = z;                                 % Initial value for optimization

%Parameters
alpha = 0.2;
beta = 20;
lambda_t = 2/3*pi;



