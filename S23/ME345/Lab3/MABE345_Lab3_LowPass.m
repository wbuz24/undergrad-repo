% MABE 345  - Lab 3 (Low Pass)
% Summer 2020
  fprintf('  \n')
  fprintf('------------------')
  fprintf('  \n')
  fprintf(' Low Pass Filter')
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
    X1 = LP5HzAxes1XData;
    Y1 = LP5HzAxes1YData;
    X2 = LP5HzAxes2XData;
    Y2 = LP5HzAxes2YData; 
elseif A == 2
    X1 = LP10HzAxes1XData;
    Y1 = LP10HzAxes1YData;
    X2 = LP10HzAxes2XData;
    Y2 = LP10HzAxes2YData; 
elseif A == 3
    X1 = LP20HzAxes1XData;
    Y1 = LP20HzAxes1YData;
    X2 = LP20HzAxes2XData;
    Y2 = LP20HzAxes2YData; 
elseif A == 4
    X1 = LP40HzAxes1XData;
    Y1 = LP40HzAxes1YData;
    X2 = LP40HzAxes2XData;
    Y2 = LP40HzAxes2YData;
elseif A == 5 
    X1 = LP80HzAxes1XData;
    Y1 = LP80HzAxes1YData;
    X2 = LP80HzAxes2XData;
    Y2 = LP80HzAxes2YData; 
elseif A == 6
    X1 = LP160HzAxes1XData;
    Y1 = LP160HzAxes1YData;
    X2 = LP160HzAxes2XData;
    Y2 = LP160HzAxes2YData; 
elseif A == 7
    X1 = LP320HzAxes1XData;
    Y1 = LP320HzAxes1YData;
    X2 = LP320HzAxes2XData;
    Y2 = LP320HzAxes2YData; 
elseif A == 8
    X1 = LP640HzAxes1XData;
    Y1 = LP640HzAxes1YData;
    X2 = LP640HzAxes2XData;
    Y2 = LP640HzAxes2YData; 
elseif A == 9
    X1 = LP1280HzAxes1XData;
    Y1 = LP1280HzAxes1YData;
    X2 = LP1280HzAxes2XData;
    Y2 = LP1280HzAxes2YData; 
elseif A == 10
    X1 = LP2560HzAxes1XData;
    Y1 = LP2560HzAxes1YData;
    X2 = LP2560HzAxes2XData;
    Y2 = LP2560HzAxes2YData;
    
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
title('Low Pass - Time Domain')
hold on

subplot(2,1,2)
plot(X2,Y2)
grid on 
xlabel('Frequency (Hz)')
xlim([0 2600])
ylabel('Voltage (V)')
ylim([0 8])
title('Low Pass - Frequency Domain')

hold on

