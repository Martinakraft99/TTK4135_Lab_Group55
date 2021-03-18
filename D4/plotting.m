x_enc = load('x_enc');

numPlots = size(x_enc.ans, 1) - 1;

figure(1)
for i = 1 : numPlots
   subplot(numPlots, 1, i)
   plot(x_enc.ans(1,:), x_enc.ans(i+1,:))
end

