%% A8 P1

d = 10/21;

a = 1/9;
b = 1.25/6;

d1 = 32/8;
a1 = 1/8;
d0 = d1 + 2*a1;

Ct = 1.571/6;

w = 4394/261;
T = (63025*1.7)/w;

Gr = 149.^2/15.^2;
R = 80 + 2*24; % 80 instead of 40, incorrect numbers

gp = (80 + 24)/80; % same error here

daxis = (2*128 + 2*19)/(2*10);

%% problem 2

P = 5000*0.224809; % lb
Dc = 8.7*0.393701; % in
Do = 2; %in
p = .25;
Dp = 1.875;
Di = 1.75;
at = 2.58;
mu1 = .15;
mu2 = .015;

L = 2*p;
alpha = 14.5;

taou11 = P*(Dp/2)*((mu1*pi()*Dp + L*cosd(alpha))/(pi()*Dp*cosd(alpha) - mu1*L)) + mu1*P*(Dc/2);

taod11 = P*(Dp/2)*((mu1*pi()*Dp - L*cosd(alpha))/(pi()*Dp*cosd(alpha) + mu1*L)) + mu1*P*(Dc/2);

taod22 = P*(Dp/2)*((mu2*pi()*Dp - L*cosd(alpha))/(pi()*Dp*cosd(alpha) + mu2*L)) + mu2*P*(Dc/2);

taou22 = P*(Dp/2)*((mu2*pi()*Dp + L*cosd(alpha))/(pi()*Dp*cosd(alpha) - mu2*L)) + mu2*P*(Dc/2);

e1 = (P*L)/(2*pi()*taou11);
e2 = (P*L)/(2*pi()*taou22); 

lock = (L*cosd(alpha))/(pi()*Dp);

