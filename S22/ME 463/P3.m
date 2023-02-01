%% P3

time = 0:652;
a= Acceleration; 
zerotime= a.Timestamp(1); 
for i=1:length(a.Timestamp) 
t(i)= seconds(a.Timestamp(i)-zerotime); 
end 
t= t.'; 
a= [a.X,a.Y,a.Z]; 
x = a(:,1);
y = a(:,2);
z = a(:,3);
mag = sqrt(sum(x.^2 + y.^2 + z.^2, 2));
magNoG = mag - mean(mag);

plot(t,magNoG);
hold on;
xlabel('Relative Time (s)');
ylabel('Acceleration (m/s^2)');
title('A walk for Vibration');


title('Counting Steps');

hold off;
