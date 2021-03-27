%recordedDataD2 = load('x_encQ(10,0,0,0).mat');
recordedDataD2Q10 = load('x_encQ(10,0,0,0).mat');
recordedDataD2Q1 = load('x_encQ1(1,0,0,0).mat');
recordedDataD2Q_1 = load('x_encQ_1.mat');


rec_timeD2Q10 = recordedDataD2Q10.ans(1,:);
rec_lambdaD2Q10 = recordedDataD2Q10.ans(2,:);
rec_lambdaDotD2Q10 = recordedDataD2Q10.ans(3,:);
rec_pitchD2Q10 = recordedDataD2Q10.ans(4,:);
rec_pitchDotD2Q10 = recordedDataD2Q10.ans(5,:);
rec_elevD2Q10 = recordedDataD2Q10.ans(6,:);
rec_elevDotD2Q10 = recordedDataD2Q10.ans(7,:);

rec_timeD2Q1 = recordedDataD2Q1.ans(1,:);
rec_lambdaD2Q1 = recordedDataD2Q1.ans(2,:);
rec_lambdaDotD2Q1 = recordedDataD2Q1.ans(3,:);
rec_pitchD2Q1 = recordedDataD2Q1.ans(4,:);
rec_pitchDotD2Q1 = recordedDataD2Q1.ans(5,:);
rec_elevD2Q1 = recordedDataD2Q1.ans(6,:);
rec_elevDotD2Q1 = recordedDataD2Q1.ans(7,:);

rec_timeD2Q_1 = recordedDataD2Q_1.ans(1,:);
rec_lambdaD2Q_1 = recordedDataD2Q_1.ans(2,:);
rec_lambdaDotD2Q_1 = recordedDataD2Q_1.ans(3,:);
rec_pitchD2Q_1 = recordedDataD2Q_1.ans(4,:);
rec_pitchDotD2Q_1 = recordedDataD2Q_1.ans(5,:);
rec_elevD2Q_1 = recordedDataD2Q_1.ans(6,:);
rec_elevDotD2Q_1 = recordedDataD2Q_1.ans(7,:);



figure(1)
plot(rec_timeD2Q10,rec_lambdaD2Q10,rec_timeD2Q1,rec_lambdaD2Q1,rec_timeD2Q_1,rec_lambdaD2Q_1)
%set(gca,'YTick',-pi:3*pi)
%set(gca,'YTickLabel', {'-\pi','0','\pi','2\pi'})
xline(5,'--','Color','red');
xline(20,'--','Color','red');
legend('Q10','Q1','Q_1')
grid on;