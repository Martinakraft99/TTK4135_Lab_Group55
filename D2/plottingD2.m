% %% Plotting Day 2

lambda_ref_Q10;
lambda_ref_Q1;
lambda_ref_Q01;

% Load encoder values
plots = [load('q10.mat'), load('q1.mat'), load('q_1.mat')];

T = plots(1).ans(1,:);
X = [plots(1).ans(2,:); plots(2).ans(2,:); plots(3).ans(2,:)]; % extract lambda
labels = ['$q=10$ '; '$q=1$  '; '$q=0.1$'; 'optimal'];

figure(1)

correction = @(T) - pi/5*(1-exp(-T/20)).*T;
correction_offset = @(T) pi;

numX = size(X,1);
for i = 1:numX
    plot(T, X(i,:) + correction(T), 'LineWidth', 2)
    hold on
end

figure(1)
plot(t,lambda10, '--b', 'LineWidth', 2)
hold on
plot(t,lambda1, '--r', 'LineWidth', 2)
hold on
plot(t,lambda01, '--y', 'LineWidth', 2)
hold on
% plot(T, correction(T))

% legend(labels, 'optimal travel', 'interpreter', 'latex')

xline(5,'--','Color', 'red', 'LineWidth', 1);
xline(20,'--','Color','red', 'LineWidth', 1);

legend(labels, 'interpreter', 'latex')
% legend(labels, 'optimal travel', 'interpreter', 'latex')

ylabel('$\lambda$ [rad]', 'interpreter', 'latex')
xlabel('$t$ [s]', 'interpreter', 'latex')

yticks((0:10) * pi);
yticklabels( string(0:10) + "\pi" )


xlim([0 25])
grid on


%%

% recordedDataD2Q10 = load('x_encQ(10,0,0,0).mat');
% 
% recordedDataD2Q1 = load('x_encQ1(1,0,0,0).mat');
% 
% recordedDataD2Q_1 = load('x_encQ_1.mat');
% 
% 
% 
% rec_timeD2Q10 = recordedDataD2Q10.ans(1,:);
% rec_lambdaD2Q10 = recordedDataD2Q10.ans(2,:);
% rec_lambdaDotD2Q10 = recordedDataD2Q10.ans(3,:);
% rec_pitchD2Q10 = recordedDataD2Q10.ans(4,:);
% rec_pitchDotD2Q10 = recordedDataD2Q10.ans(5,:);
% rec_elevD2Q10 = recordedDataD2Q10.ans(6,:);
% rec_elevDotD2Q10 = recordedDataD2Q10.ans(7,:);
% 
% rec_timeD2Q1 = recordedDataD2Q1.ans(1,:);
% rec_lambdaD2Q1 = recordedDataD2Q1.ans(2,:);
% rec_lambdaDotD2Q1 = recordedDataD2Q1.ans(3,:);
% rec_pitchD2Q1 = recordedDataD2Q1.ans(4,:);
% rec_pitchDotD2Q1 = recordedDataD2Q1.ans(5,:);
% rec_elevD2Q1 = recordedDataD2Q1.ans(6,:);
% rec_elevDotD2Q1 = recordedDataD2Q1.ans(7,:);
% 
% rec_timeD2Q_1 = recordedDataD2Q_1.ans(1,:);
% rec_lambdaD2Q_1 = recordedDataD2Q_1.ans(2,:);
% rec_lambdaDotD2Q_1 = recordedDataD2Q_1.ans(3,:);
% rec_pitchD2Q_1 = recordedDataD2Q_1.ans(4,:);
% rec_pitchDotD2Q_1 = recordedDataD2Q_1.ans(5,:);
% rec_elevD2Q_1 = recordedDataD2Q_1.ans(6,:);
% rec_elevDotD2Q_1 = recordedDataD2Q_1.ans(7,:);
% 
% 
% 
% figure(1)
% plot(rec_timeD2Q10, rec_lambdaD2Q10)
% hold on
% plot(rec_timeD2Q1, rec_lambdaD2Q1)
% plot(rec_timeD2Q_1, rec_lambdaD2Q_1)
% set(gca,'YTick',-pi:3*pi)
% set(gca,'YTickLabel', {'-\pi','0','\pi','2\pi'})
% 
% yticks((0:10) * pi);
% yticklabels( string(0:10) + "\pi" )
% 
% xline(5,'--','Color','red');
% xline(20,'--','Color','red');
% legend('Q10','Q1','Q_1')
% grid on;