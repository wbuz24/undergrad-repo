% MABE 345  - Lab 3 (High Pass)
% Summer 2020
  fprintf('  \n')
  fprintf('------------------')
  fprintf('  \n')
  fprintf(' Band Pass Filter')
  fprintf('  \n')
  fprintf('------------------')
  fprintf('  \n')
  fprintf('  \n')
  fprintf('Freq: 5Hz, 10Hz, 20Hz, 40Hz, 80Hz, 160Hz, 320Hz, 640Hz, 1280Hz, 2560Hz')
  fprintf('  \n')
  fprintf('       |    |      |     |     |     |      |      |       |       |  ')
  fprintf('  \n')
  fprintf('       v    v      v     v     v     v      v      v       v       v  ')
  fprintf('  \n')
  fprintf('Case:  1    2      3     4     5     6      7      8       9      10')
fprintf('  \n')
fprintf('  \n')
A = input('Enter the frequency case you would like to view: ');
fprintf('  \n')


if     A == 1
    X1 = BP5HzAxes1XData;
    Y1 = BP5HzAxes1YData;
    X2 = BP5HzAxes2XData;
    Y2 = BP5HzAxes2YData; 
elseif A == 2
    X1 = BP10HzAxes1XData;
    Y1 = BP10HzAxes1YData;
    X2 = BP10HzAxes2XData;
    Y2 = BP10HzAxes2YData; 
elseif A == 3
    X1 = BP20HzAxes1XData;
    Y1 = BP20HzAxes1YData;
    X2 = BP20HzAxes2XData;
    Y2 = BP20HzAxes2YData; 
elseif A == 4
    X1 = BP40HzAxes1XData;
    Y1 = BP40HzAxes1YData;
    X2 = BP40HzAxes2XData;
    Y2 = BP40HzAxes2YData;
elseif A == 5 
    X1 = BP80HzAxes1XData;
    Y1 = BP80HzAxes1YData;
    X2 = BP80HzAxes2XData;
    Y2 = BP80HzAxes2YData; 
elseif A == 6
    X1 = BP160HzAxes1XData;
    Y1 = BP160HzAxes1YData;
    X2 = BP160HzAxes2XData;
    Y2 = BP160HzAxes2YData; 
elseif A == 7
    X1 = BP320HzAxes1XData;
    Y1 = BP320HzAxes1YData;
    X2 = BP320HzAxes2XData;
    Y2 = BP320HzAxes2YData; 
elseif A == 8
    X1 = BP640HzAxes1XData;
    Y1 = BP640HzAxes1YData;
    X2 = BP640HzAxes2XData;
    Y2 = BP640HzAxes2YData; 
elseif A == 9
    X1 = BP1280HzAxes1XData;
    Y1 = BP1280HzAxes1YData;
    X2 = BP1280HzAxes2XData;
    Y2 = BP1280HzAxes2YData; 
elseif A == 10
    X1 = BP2560HzAxes1XData;
    Y1 = BP2560HzAxes1YData;
    X2 = BP2560HzAxes2XData;
    Y2 = BP2560HzAxes2YData;
end


% This generates the plots for you to analyze
%figure()
subplot(2,1,1)
plot(X1,Y1)
grid on 
xlabel('Time (s)')
xlim([0 0.25])
ylabel('Voltage (V) ')
ylim([-10 10])
title('Band Pass - Time Domain')
hold on

subplot(2,1,2)
plot(X2,Y2)
grid on 
xlabel('Frequency (Hz)')
xlim([0 2600])
ylabel('Voltage (V)')
ylim([0 8])
title('Band Pass - Frequency Domain')

hold on

