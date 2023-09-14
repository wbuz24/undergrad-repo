%% Project 2

% Will Buziak
% create a video of a wave pendulum head on

% initialize 
freqs  = 5:15;
num = numel(freqs);
lengths = 1./sqrt(freqs);
piover6 = pi/6;

% plot
figure
axis([-0.3 0.3 -0.5 0]);
axis off;
org=zeros(size(freqs));
xpos=zeros(size(freqs));
ypos=zeros(size(freqs));
pendula =  line([org;org],[org;org],'LineWidth',1,'Marker','.','MarkerSize',25 ...
                ,'Color',['r' 0 0],'visible','off' );

% Open the avi file
vidObj = VideoWriter('P2.MP4');
open(vidObj);

count =0;
for t=0:0.001:10
    count=count+.01;
omegas = 2*pi*freqs*t;
xpos = sin(piover6*cos(omegas)).*lengths;
ypos = -cos(piover6*cos(omegas)).*lengths;

 for i=1:num
 set(pendula(i),'visible','on');
 set(pendula(i),'XData',[0 xpos(i)]);
 set(pendula(i),'YData',[0 ypos(i)]);
 drawnow
 end
 currFrame = getframe;
 writeVideo(vidObj,currFrame)

 F(i) = getframe;
end

% Close the file.
close(vidObj);


