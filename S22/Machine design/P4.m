clc
clear
%% Project 4 Machine Design

H = 16; %in: also free length of springs?
Flog = 400; % lbs
F = 4; % lbs from person


%% Spring

ds = .105; %in: diameter of wire
C = 4;
Ds = C*ds; % in: mean diameter of spring
G = 11.5 * 10.^6; %psi
Dos = Ds + ds; % outer diameter
ywork = H;
Fspring = Flog/4;

y = ywork;
yi = .15*y;

Na = (ds*G*(ywork+yi))/(8*Fspring*C.^3); % active coils
Nt = Na + 2;

kdesired = (Fspring)/(ywork + yi);
kactual = (G * ds)/(8 * Na * C.^3);
ks = 1 + (.5/C);



Finitial = yi*kactual;
Fwactual = ywork*kactual;

Ls = ds*Nt;
Lf = Ls + .15*y + ywork;

yshut = Lf - Ls;
Fshut = kactual*yshut;

taoshut = ks*(8*Fshut*Ds)/(pi()*ds.^3);

Sutspring = 146780*Ds.^(-.1833);
Susspring = .67*Sutspring;
Sysspring = .65*Sutspring;

FOSspring = Sysspring/taoshut;
%% planetary gears

Pd = 24; %pitch diameter
Ns = 33; % number of teeth sun
Np = 21; % number of teeth planet
Lhandle = 5; % in

R = 2*Np + Ns; % number of teeth on ring
ratio = (Ns + Np)/Ns;
Dring = (R + 2)/Pd;


%% Power screw

Dmaj = 1; %in
N = 5; %threads per inch
p = .2; % thread pitch
Lead = p; % lead (single start)
dps = .9; %in (pitch diameter)
Dmin = .8; %in
At = .568;
mu = .15;
dc = Dring + .5; %in

lock  = (Lead*cosd(14.5))/(pi()*dps);
lambda = atand(Lead/(pi()*dps));

P = Flog - 2*Fspring;

taou = (P*dps/2)*((mu*pi()*dps + Lead*cosd(14.5))/(pi()*dps*cosd(14.5) - mu*Lead)) + mu*P*(dc/2);
taod = (P*dps/2)*((mu*pi()*dps - Lead*cosd(14.5))/(pi()*dps*cosd(14.5) + mu*Lead)) - mu*P*(dc/2);

taohandle = taou/ratio;
Fhandle = taohandle/Lhandle;

effscrew = (1 - mu*tand(lambda))/(1 + mu*cotd(lambda));

%% Fastener

Sp = 33*1000; %kpsi
Symin = 36*1000;
Sutmin = 60;
E = 27500; %ksi
l = 1.25; % length of the bolt

dmaj = .216; %in
dr = .1619;
at = .0242;
ab = pi()*(dr/2).^2;

Fi = .7*Sp*at;
lth = 2*dmaj + .25;
ls = l - lth;
lt = .25 - ls;

kthrow = (lt/(at*E)) + (ls/(ab*E));
kb = 1/kthrow;
km = (pi()*(dmaj.^2 - dr.^2)*E)/(4*.25);

Cr = kb/(kb+km);
Pb = Cr*Flog;
Pm = Flog - Pb;
Fb = Fi + Pb;
Fm = Fi - Pm;

sigb = Fb/at;
FOSfast = Symin/sigb;

Po = Fi/(1-Cr);
FOSsep = Po/Flog;


