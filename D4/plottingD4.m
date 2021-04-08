% Data 1, init guess. 
recordedDataD4_1 = load('x_encQ(10,5,.1.1,1,1)R(.1,.1).mat');
recordedInputD4_1 = load('u_vecQ(10,5,.1.1,1,1)R(.1,.1).mat');

% Data 2, init guess. 
recordedDataD4_2 = load('x_encQ(10,5,.1.1,10,10)R(.1,.1).mat');
recordedInputD4_2 = load('u_vecQ(10,5,.1.1,10,10)R(.1,.1).mat');


% Data 1 
rec_timeD4_1 = recordedDataD4_1.ans(1,:);
rec_lambdaD4_1 = recordedDataD4_1.ans(2,:);
rec_lambdaDotD4_1 = recordedDataD4_1.ans(3,:);
rec_pitchD4_1 = recordedDataD4_1.ans(4,:);
rec_pitchDotD4_1 = recordedDataD4_1.ans(5,:);
rec_elevD4_1 = recordedDataD4_1.ans(6,:);
rec_elevDotD4_1 = recordedDataD4_1.ans(7,:);

rec_input1D4_1 = recordedInputD4_1.ans(2,:);
rec_input2D4_1 = recordedInputD4_1.ans(3,:);

% Data 2
rec_timeD4_2 = recordedDataD4_2.ans(1,:);
rec_lambdaD4_2 = recordedDataD4_2.ans(2,:);
rec_lambdaDotD4_2 = recordedDataD4_2.ans(3,:);
rec_pitchD4_2 = recordedDataD4_2.ans(4,:);
rec_pitchDotD4_2 = recordedDataD4_2.ans(5,:);
rec_elevD4_2 = recordedDataD4_2.ans(6,:);
rec_elevDotD4_2 = recordedDataD4_2.ans(7,:);

rec_input1D4_2 = recordedInputD4_2.ans(2,:);
rec_input2D4_2 = recordedInputD4_2.ans(3,:);


figure(1)
plot(rec_timeD4_1, rec_lambdaD4_1, rec_timeD4_2, rec_lambdaD4_2)
%set(gca,'YTick',-pi:3*pi)
%set(gca,'YTickLabel', {'-\pi','0','\pi','2\pi'})
xline(5,'--','Color','red');
xline(20,'--','Color','red');
legend('D1','D2')
grid on;
hold on;

figure(2)
plot(rec_lambdaD4_1, rec_elevD4_1, rec_lambdaD4_2, rec_lambdaD4_2)
%set(gca,'YTick',-pi:3*pi)
%set(gca,'YTickLabel', {'-\pi','0','\pi','2\pi'})
xline(5,'--','Color','red');
xline(20,'--','Color','red');
legend('D1','D2')
grid on;
hold on;
x1_padded = [zeros(2500,1);x1];
econ_padded = [zeros(2500,1);econ];
plot(x1_padded,econ_padded)

figure(3)
plot(rec_timeD4_1, rec_input1D4_1,rec_timeD4_1, rec_input2D4_1,rec_timeD4_2, rec_input1D4_2,rec_timeD4_2, rec_input2D4_2)
%set(gca,'YTick',-pi:3*pi)
%set(gca,'YTickLabel', {'-\pi','0','\pi','2\pi'})
xline(5,'--','Color','red');
xline(20,'--','Color','red');
legend('D1u1','D1u2')
grid on;


%% Not working, plot elev against lambda and with nonlinear constraint
% figure(3)
% plot(rec_lambdaD4_1,rec_elevD4_1)
% hold on;
% plot(econ);