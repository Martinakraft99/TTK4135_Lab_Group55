%% Initialization and model definition
clc 
clear all
init01; % Change this to the init file corresponding to your helicopter

A_c = [0  1  0          0          0          0;
       0  0  -K_2       0          0          0; 
       0  0  0          1          0          0;
       0  0  -K_1*K_pp  -K_1*K_pd  0          0; 
       0  0  0          0          0          1;
       0  0  0          0          -K_3*K_ep  -K_3*K_ed];

B_c = [0         0;
       0         0;
       0         0;
       K_1*K_pp  0;
       0         0;
       0         K_3*K_ep];

% Number of states and inputs
mx = size(A_c,2); % Number of states (number of columns in A)
mu = size(B_c,2); % Number of inputs(number of columns in B)

% Discrete time system model. x = [lambda r p p_dot]'
delta_t	= 0.25; % sampling time
A_d = eye(mx) + delta_t*A_c;
B_d = B_c*delta_t;

% Initial values
x1_0 = pi;                              % Lambda
x2_0 = 0;                               % r
x3_0 = 0;                               % p
x4_0 = 0;                               % p_dot
x5_0 = 0;                               % e
x6_0 = 0;                               %e_dot
x0 = [x1_0 x2_0 x3_0 x4_0 x5_0 x6_0].'; % Initial values

% Time horizon and initialization
N  = 40;                                 % Time horizon for states [MUST CHANGE IN get_elevation_constraint() as well] 
M  = N;                                 % Time horizon for inputs
z  = zeros(N*mx+M*mu,1);                % Initialize z for the whole horizon
z0 = z;                                 % Initial value for optimization
z(1:6) = x0;                           

% Bounds
ul 	    = [-30*pi/180, -inf].';                   % Lower bound on control
uu 	    = [30*pi/180, inf].';                   % Upper bound on control


xl      = -Inf*ones(mx,1);              % Lower bound on states (no bound)
xu      = Inf*ones(mx,1);               % Upper bound on states (no bound)
xl(3)   = ul(1);                           % Lower bound on state x3
xu(3)   = uu(1);                           % Upper bound on state x3


% Generate constraints on measurements and inputs
[vlb, vub]      = gen_constraints(N,M,xl,xu,ul,uu);    % hint: gen_constraints [NB N+1 is modified]

%vlb(N*mx+M*mu)  = 0;                    % We want the last input to bezero 
%vub(N*mx+M*mu)  = 0;                    % We want the last input to be zero

vlb(end) = 0;
vlb(end-1) = 0;
vub(end) = 0;
vub(end-1) = 0;



%% Parameters for fmincon
alpha = 0.2;
beta = 20;
lambda_t = 2/3*pi;
lambda_f = 1;


Qt = diag([1,1,1,1,10, 1]);
Rt = diag([.1,.1]);
c = zeros((mu+mx)*N, 1);
for i=0:N-1
    c(1+i*mx) = -2*lambda_f;
end

%c = [ kron( [2*lambda_f 0 0 0 0 0], ones(1, N)) zeros(1, N*mu)].'

%% LQR

LQR_Q = diag([1;1;1;1;1;1]);  %Rank = mx
LQR_R = diag([1;1]);        %Rank = mu

K = dlqr(A_d,B_d,LQR_Q,LQR_R);

%% Generate system matrixes for linear model
Aeq = gen_aeq(A_c, B_c, N, mx, mu);             % Generate A, hint: gen_aeq
Beq = [A_c*x0;zeros(mx*N-mx,1)];  

G = gen_q(Qt, Rt, N, M);


ofun = @(z) 1/2 * z.'* G * z;
%econ = @(z)get_elevation_constraint(z,alpha,beta,lambda_t,N,mx);

% z = fmincon(ofun, z, [], [], Aeq, Beq, vlb,vub,@get_elevation_constraint);
z = fmincon(ofun, z, [], [], Aeq, Beq, vlb,vub,[]);



%% Extract control inputs and states
u1  = [z(N*mx+1:mu:end); z(N*mx+M*mu-1)];                % Control input from solution
u2  = [z(N*mx+2:mu:end); z(N*mx+M*mu)];                % Control input from solution

x1 = [x0(1);z(1:mx:N*mx)];              % State x1 from solution
x2 = [x0(2);z(2:mx:N*mx)];              % State x2 from solution
x3 = [x0(3);z(3:mx:N*mx)];              % State x3 from solution
x4 = [x0(4);z(4:mx:N*mx)];              % State x4 from solution
x5 = [x0(5);z(5:mx:N*mx)];              % State x3 from solution
x6 = [x0(6);z(6:mx:N*mx)];              % State x4 from solution

num_variables = 5/delta_t;
zero_padding = zeros(num_variables,1);
unit_padding  = ones(num_variables,1);

u1   = [zero_padding; u1; zero_padding];
u2   = [zero_padding; u2; zero_padding];
x1  = [pi*unit_padding; x1; zero_padding];
x2  = [zero_padding; x2; zero_padding];
x3  = [zero_padding; x3; zero_padding];
x4  = [zero_padding; x4; zero_padding];
x5  = [zero_padding; x5; zero_padding];
x6  = [zero_padding; x6; zero_padding];

x = [x1 x2 x3 x4 x5 x6];
u = [u1 u2];

time_steps = [0:delta_t:(N+2*num_variables)*delta_t];
ts_u = timeseries(u, time_steps);
ts_x = timeseries(x, time_steps);



%% Plotting


[c,ceq] = get_elevation_constraint(z);

t = 0:delta_t:delta_t*(length(u)-1);

figure(1)                                                                                        
plot(c)


figure(2)
subplot(711)
stairs(t,u),grid
ylabel('u')
subplot(712)
plot(t,x1,'m',t,x1,'mo'),grid
ylabel('lambda')
subplot(713)
plot(t,x2,'m',t,x2','mo'),grid
ylabel('r')
subplot(714)
plot(t,x3,'m',t,x3,'mo'),grid
ylabel('p')
subplot(715)
plot(t,x4,'m',t,x4','mo'),grid
subplot(716)
plot(t,x5,'m',t,x5','mo'),grid
ylabel('e')
subplot(717)
plot(t,x6,'m',t,x6','mo'),grid
xlabel('tid (s)'),ylabel('edot')





