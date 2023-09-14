clear all
clc

%% HW 5, problem 1

% initialize

D = .399;
r = D/2;
Lhub = .53;
Ta = 99;
Tm = Ta;
Sy = 44000;
Sut = 53000;
Se = 22900;

F = Ta/r;
Abear = Lhub*(.093/2);
sigx = F/Abear;
FOSb = Sy/sigx;


Ta2 = 104;
L = .74;

r2 = .529/2;


F2 = Ta2/r2;
A = L*(.125);
tao = F2/A;
siga = [tao;
        0;
        -tao];
vms = sqrt(siga(1).^2 + siga(2).^2 + siga(3).^2 - (siga(1)*siga(2) + siga(2)*siga(3) + siga(3)*siga(1)));
FOSy = (vms/Se) + (vms/Sut);
FOS2 = 1/FOSy;


%% Problem 2

R = 95;
kR = .62;
C = 11600;
D2 = 45;
a = 30;
b = 100;
P = 2500;


life1 = kR*(C/2400).^3;
life2 = .53*(C/1800).^3;
life119 = kR*(3550/P).^3;
life215 = kR*(900/P).^3;
life245 = kR*(1400/P).^3;

OD = 6;
ID = 4;
length = 156;

Syc = 752;
E = 103.4;

area = pi()*(OD.^2- ID.^2);
I = (1/12)*area;
k = sqrt(I/area);
Sr = length/k;
Pcr = area*((pi().^2*E)/Sr.^2);

leff = 2.1*119;
OD2 = 20;
ID2 = 18;

area2 = pi()*(OD2.^2 - ID2.^2);
I2 = (1/12)*area2;
k2 = sqrt(I2/area2);
Sr2 = leff/k2;
Pcr2 = area2*((pi().^2*E)/Sr2.^2);
