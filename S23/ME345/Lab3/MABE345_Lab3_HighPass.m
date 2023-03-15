% MABE 345  - Lab 3 (High Pass)
% Summer 2020
  fprintf('  \n')
  fprintf('------------------')
  fprintf('  \n')
  fprintf(' High Pass Filter')
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
    X1 = HP5HzAxes1XData;
    Y1 = HP5HzAxes1YData;
    X2 = HP5HzAxes2XData;
    Y2 = HP5HzAxes2YData; 
elseif A == 2
    X1 = HP10HzAxes1XData;
    Y1 = HP10HzAxes1YData;
    X2 = HP10HzAxes2XData;
    Y2 = HP10HzAxes2YData; 
elseif A == 3
    X1 = HP20HzAxes1XData;
    Y1 = HP20HzAxes1YData;
    X2 = HP20HzAxes2XData;
    Y2 = HP20HzAxes2YData; 
elseif A == 4
    X1 = HP40HzAxes1XData;
    Y1 = HP40HzAxes1YData;
    X2 = HP40HzAxes2XData;
    Y2 = HP40HzAxes2YData;
elseif A == 5 
    X1 = HP80HzAxes1XData;
    Y1 = HP80HzAxes1YData;
    X2 = HP80HzAxes2XData;
    Y2 = HP80HzAxes2YData; 
elseif A == 6
    X1 = HP160HzAxes1XData;
    Y1 = HP160HzAxes1YData;
    X2 = HP160HzAxes2XData;
    Y2 = HP160HzAxes2YData; 
elseif A == 7
    X1 = HP320HzAxes1XData;
    Y1 = HP320HzAxes1YData;
    X2 = HP320HzAxes2XData;
    Y2 = HP320HzAxes2YData; 
elseif A == 8
    X1 = HP640HzAxes1XData;
    Y1 = HP640HzAxes1YData;
    X2 = HP640HzAxes2XData;
    Y2 = HP640HzAxes2YData; 
elseif A == 9
    X1 = HP1280HzAxes1XData;
    Y1 = HP1280HzAxes1YData;
    X2 = HP1280HzAxes2XData;
    Y2 = HP1280HzAxes2YData; 
elseif A == 10
    X1 = HP2560HzAxes1XData;
    Y1 = HP2560HzAxes1YData;
    X2 = HP2560HzAxes2XData;
    Y2 = HP2560HzAxes2YData;
    
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
title('High Pass - Time Domain')
hold on

subplot(2,1,2)
plot(X2,Y2)
grid on 
xlabel('Frequency (Hz)')
xlim([0 2600])
ylabel('Voltage (V)')
ylim([0 8])
title('High Pass - Frequency Domain')

hold on

