
% Data 1, init guess. 
recordedDataD3_1 = load('x_encQ(1,1,1,1)R(1).mat');
recordedInputD3_1 = load('u_vecQ(1,1,1,1)R(1).mat');

% Data 2, try to increase lambda
recordedDataD3_2 = load('x_encQ(10,1,1,1)R(1).mat');
recordedInputD3_2 = load('u_vecQ(10,1,1,1)R(1).mat');

% Data 3, try to decrease lambda dot
recordedDataD3_3 = load('x_encQ(10,.1,1,1)R(1).mat');
recordedInputD3_3 = load('u_vecQ(10,.1,1,1)R(1).mat');

% Data 4, try to decrease input
recordedDataD3_4 = load('x_encQ(10,.1,1,1)R(.1).mat');
recordedInputD3_4 = load('u_vecQ(10,.1,1,1)R(.1).mat');

% Data 5, try to decrease lambda. Meant to be terrible
recordedDataD3_5 = load('x_encQ(.1,.1,1,1)R(.1).mat');
recordedInputD3_5 = load('u_vecQ(.1,.1,1,1)R(.1).mat');

% Data 6, try to decrease decrease pitch
recordedDataD3_6 = load('x_encQ(10,5,.1,.1)R(.1).mat');
recordedInputD3_6 = load('u_vecQ(10,5,.1,.1)R(.1).mat');





% Data 1 
rec_timeD3_1 = recordedDataD3_1.ans(1,:);
rec_lambdaD3_1 = recordedDataD3_1.ans(2,:);
rec_lambdaDotD3_1 = recordedDataD3_1.ans(3,:);
rec_pitchD3_1 = recordedDataD3_1.ans(4,:);
rec_pitchDotD3_1 = recordedDataD3_1.ans(5,:);
rec_elevD3_1 = recordedDataD3_1.ans(6,:);
rec_elevDotD3_1 = recordedDataD3_1.ans(7,:);

rec_inputD3_1 = recordedInputD3_1.ans(2,:);

% Data 2
rec_timeD3_2 = recordedDataD3_2.ans(1,:);
rec_lambdaD3_2 = recordedDataD3_2.ans(2,:);
rec_lambdaDotD3_2 = recordedDataD3_2.ans(3,:);
rec_pitchD3_2 = recordedDataD3_2.ans(4,:);
rec_pitchDotD3_2 = recordedDataD3_2.ans(5,:);
rec_elevD3_2 = recordedDataD3_2.ans(6,:);
rec_elevDotD3_2 = recordedDataD3_2.ans(7,:);

rec_inputD3_2 = recordedInputD3_2.ans(2,:);


% Data 3
rec_timeD3_3 = recordedDataD3_3.ans(1,:);
rec_lambdaD3_3 = recordedDataD3_3.ans(2,:);
rec_lambdaDotD3_3 = recordedDataD3_3.ans(3,:);
rec_pitchD3_3 = recordedDataD3_3.ans(4,:);
rec_pitchDotD3_3 = recordedDataD3_3.ans(5,:);
rec_elevD3_3 = recordedDataD3_3.ans(6,:);
rec_elevDotD3_3 = recordedDataD3_3.ans(7,:);

rec_inputD3_3 = recordedInputD3_3.ans(2,:);


% Data 4
rec_timeD3_4 = recordedDataD3_4.ans(1,:);
rec_lambdaD3_4 = recordedDataD3_4.ans(2,:);
rec_lambdaDotD3_4 = recordedDataD3_4.ans(3,:);
rec_pitchD3_4 = recordedDataD3_4.ans(4,:);
rec_pitchDotD3_4 = recordedDataD3_4.ans(5,:);
rec_elevD3_4 = recordedDataD3_4.ans(6,:);
rec_elevDotD3_4 = recordedDataD3_4.ans(7,:);

rec_inputD3_4 = recordedInputD3_4.ans(2,:);


% Data 5
rec_timeD3_5 = recordedDataD3_5.ans(1,:);
rec_lambdaD3_5 = recordedDataD3_5.ans(2,:);
rec_lambdaDotD3_5 = recordedDataD3_5.ans(3,:);
rec_pitchD3_5 = recordedDataD3_5.ans(4,:);
rec_pitchDotD3_5 = recordedDataD3_5.ans(5,:);
rec_elevD3_5 = recordedDataD3_5.ans(6,:);
rec_elevDotD3_5 = recordedDataD3_5.ans(7,:);

rec_inputD3_5 = recordedInputD3_5.ans(2,:);


% Data 6
rec_timeD3_6 = recordedDataD3_6.ans(1,:);
rec_lambdaD3_6 = recordedDataD3_6.ans(2,:);
rec_lambdaDotD3_6 = recordedDataD3_6.ans(3,:);
rec_pitchD3_6 = recordedDataD3_6.ans(4,:);
rec_pitchDotD3_6 = recordedDataD3_6.ans(5,:);
rec_elevD3_6 = recordedDataD3_6.ans(6,:);
rec_elevDotD3_6 = recordedDataD3_6.ans(7,:);

rec_inputD3_6 = recordedInputD3_6.ans(2,:);


figure(1)
plot(rec_timeD3_6, rec_lambdaD3_6,'LineWidth',3)
hold on;
plot(t(:,1:101),x1(1:101,:),'--','LineWidth',3,'Color','#EDB120')
xline(5,'--','Color','red','LineWidth',2);
xline(20,'--','Color','red','LineWidth',2);
legend('$\lambda$','$\lambda^*$','Interpreter','latex','FontSize',20)
title('$\lambda$ vs $\lambda^*$','Interpreter','latex')
xlabel('Time [$s$]','Interpreter','latex')
ylabel('Travel[rad]','Interpreter','latex')
grid on;

figure(3)
plot(rec_timeD3_6, rec_pitchD3_6,'LineWidth',3)
hold on;
plot(t(:,1:101),x3(1:101,:),'--','LineWidth',3,'Color','#EDB120')
xline(5,'--','Color','red','LineWidth',2);
xline(20,'--','Color','red','LineWidth',2);
legend('$\lambda$','$\lambda^*$','Interpreter','latex','FontSize',20)
title('$\lambda$ vs $\lambda^*$','Interpreter','latex')
xlabel('Time [$s$]','Interpreter','latex')
ylabel('Travel[rad]','Interpreter','latex')
grid on;



figure(2)
plot(rec_timeD3_6, rec_inputD3_6,'LineWidth',2)
hold on;
plot(t(:,1:101),u(1:101,:),'--','LineWidth',2,'Color','#EDB120')
xline(5,'--','Color','red','LineWidth',2);
xline(20,'--','Color','red','LineWidth',2);
legend('u_k','u_k^*')
title('Input')
xlabel('time(s)')
ylabel('input(rad)')
grid on;