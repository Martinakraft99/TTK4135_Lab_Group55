% Data 1, init guess. 
% recordedDataD4_1 = load('x_encQ(10,5,.1.1,1,1)R(.1,.1).mat');
% recordedInputD4_1 = load('u_vecQ(10,5,.1.1,1,1)R(.1,.1).mat');

% Data 1, init guess. 
recordedDataD4_1 = load('../x_enc.mat');
recordedInputD4_1 = load('../u_vec.mat');

% Data 2, init guess. 
% recordedDataD4_2 = load('x_encQ(10,5,.1.1,10,10)R(.1,.1).mat');
% recordedInputD4_2 = load('u_vecQ(10,5,.1.1,10,10)R(.1,.1).mat');


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
% rec_timeD4_2 = recordedDataD4_2.ans(1,:);
% rec_lambdaD4_2 = recordedDataD4_2.ans(2,:);
% rec_lambdaDotD4_2 = recordedDataD4_2.ans(3,:);
% rec_pitchD4_2 = recordedDataD4_2.ans(4,:);
% rec_pitchDotD4_2 = recordedDataD4_2.ans(5,:);
% rec_elevD4_2 = recordedDataD4_2.ans(6,:);
% rec_elevDotD4_2 = recordedDataD4_2.ans(7,:);
% 
% rec_input1D4_2 = recordedInputD4_2.ans(2,:);
% rec_input2D4_2 = recordedInputD4_2.ans(3,:);

% 
% figure(1)
% plot(rec_timeD4_1, rec_elevD4_1,'Color','[0, 0.4470, 0.7410]','LineWidth',3)
% set(gca,'YTick',[-pi/16,-pi/32,0,pi/32,pi/16])
% set(gca,'YTickLabel', {'-\pi/16','-\pi/32','0','\pi/32','\pi/16'})
% hold on;
% plot(t,x5,'--','Color','[0.9290, 0.6940, 0.1250]','LineWidth',3)
% xline(5,'--','Color','red','LineWidth',2);
% xline(20,'--','Color','red','LineWidth',2);
% legend('$e$','$e^*$','Interpreter','latex','FontSize',20)
% ylabel('$e[rad]$','Interpreter','latex')
% xlabel('t[$s$]','Interpreter','latex')
% grid on;
% ylim([-pi/32,pi/16])
% 
% figure(4)
% plot(rec_timeD4_1, rec_pitchD4_1,'Color','[0, 0.4470, 0.7410]','LineWidth',3)
% set(gca,'YTick',[-pi/6,-pi/12,0,pi/12,pi/6])
% set(gca,'YTickLabel', {'-\pi/6','-\pi/12','0','\pi/12','\pi/6'})
% hold on;
% plot(t,x3,'--','Color','[0.9290, 0.6940, 0.1250]','LineWidth',3)
% xline(5,'--','Color','red','LineWidth',2);
% xline(20,'--','Color','red','LineWidth',2);
% legend('$p$','$p^*$','Interpreter','latex','FontSize',20)
% ylabel('$p[rad]$','Interpreter','latex')
% xlabel('t[$s$]','Interpreter','latex')
% grid on;

figure(5)
plot(rec_timeD4_1, rec_elevDotD4_1,'Color','[0, 0.4470, 0.7410]','LineWidth',3)

set(gca,'YTick',[-pi/6,-pi/12,0,pi/12,pi/6])
set(gca,'YTickLabel', {'-\pi/6','-\pi/12','0','\pi/12','\pi/6'})
hold on;
% plot(rec_timeD4_1, rec_elevDotD4_1,'Color','[0.8500, 0.3250, 0.0980]','LineWidth',3)
plot(t,x6,'--','Color','[0.9290, 0.6940, 0.1250]','LineWidth',3)
xline(5,'--','Color','red','LineWidth',2);
xline(20,'--','Color','red','LineWidth',2);
legend('$p$','$\dot{e}$','$\dot{e}$','Interpreter','latex','FontSize',20)
ylabel('$p[rad]$','Interpreter','latex')
xlabel('t[$s$]','Interpreter','latex')
grid on;
xlim([5,20])

% 
% figure(2)
% plot(rec_lambdaD4_1(1,2600:end), rec_elevD4_1(1,2600:end),'Color','[0, 0.4470, 0.7410]','LineWidth',3)
% set(gca,'YTick',[0,pi/32,pi/16])
% set(gca,'YTickLabel', {'0','\pi/32','\pi/16'})
% set(gca,'XTick',0:pi)
% set(gca,'XTickLabel', {'0','-\pi/3','-2\pi/3','-\pi'})
% hold on;
% plot(x1,x5,'--','Color','[0.9290, 0.6940, 0.1250]','LineWidth',3)
% plot(x1,econ,'Color','red','LineWidth',2)
% legend('$e$','$e^*$','$c$','Interpreter','latex','FontSize',20)
% ylabel('$e[rad]$','Interpreter','latex')
% xlabel('$\lambda[rad]$','Interpreter','latex')
% grid on;





% figure(3)
% plot(rec_timeD4_1, rec_input1D4_1,rec_timeD4_1, rec_input2D4_1,rec_timeD4_2, rec_input1D4_2,rec_timeD4_2, rec_input2D4_2)
% %set(gca,'YTick',-pi:3*pi)
% %set(gca,'YTickLabel', {'-\pi','0','\pi','2\pi'})
% xline(5,'--','Color','red');
% xline(20,'--','Color','red');
% legend('D1u1','D1u2')
% grid on;


%% Not working, plot elev against lambda and with nonlinear constraint
% figure(3)
% plot(rec_lambdaD4_1,rec_elevD4_1)
% hold on;
% plot(econ);