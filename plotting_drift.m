% Load encoder values
plots = [load('drift.mat')];

T = plots(1).ans(1,:);
X = [plots(1).ans(2,:)]; % extract lambda
labels = ['regular drift'];

figure(1)

correction = @(T) - pi/5*(1-exp(-T/21)).*T;
correction_offset = @(T) 0;

numX = size(X,1);
for i = 1:numX
    plot(T, X(i,:) + correction_offset(T), 'LineWidth', 2)
    hold on
end

% figure(1)
% xline(-5,'--','Color', 'black', 'LineWidth', 1.5);
% hold on
% plot(t,lambda10, '--', 'LineWidth', 1.5, 'Color' ,[0 0.45 0.74])
% hold on
% plot(t,lambda1, '--', 'LineWidth', 1.5, 'Color' ,[0.85 0.33 0.1])
% hold on
% plot(t,lambda01, '--', 'LineWidth', 1.5, 'Color' ,[0.93 0.69 0.13])
% hold on
% plot(T, correction(T))

% legend(labels, 'optimal travel', 'interpreter', 'latex')

% xline(5,'--','Color', 'red', 'LineWidth', 1);
% xline(20,'--','Color','red', 'LineWidth', 1);

legend(labels, 'interpreter', 'latex')
% legend(labels, 'optimal travel', 'interpreter', 'latex')

ylabel('$\lambda$ [rad]', 'interpreter', 'latex')
xlabel('$t$ [s]', 'interpreter', 'latex')

yticks([-3*pi -5*pi/2 -2*pi -3*pi/2 -pi -pi/2 0 pi/2 pi 3*pi/2 2*pi 5*pi/2 3*pi 7*pi/2 4*pi])
yticklabels({'-3\pi','-5\pi/2','-2\pi','-3\pi/2','-\pi','-\pi/2','0','\pi/2','\pi','3\pi/2','2\pi','5\pi/2','3\pi','7\pi/2','4\pi'})
% 
% yticks((0:10) * pi);
% yticklabels( string(0:10) + "\pi" )
% ylim([-pi/2 3*pi/2])
xlim([0 25])
grid on