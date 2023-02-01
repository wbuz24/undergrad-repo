clc
clear all

% Project 1 ME 466
% Will Buziak
% Submission date: 2/22/2022
% Assignment is to perform stress analysis
% on bike arm in given loading conditions

%% Section 1: Initialize

F = 20; %lb
h = .5; %in
r = 2; %in
t = 1.4; %in
L = 4; %in
d = .5; %in
x = linspace(0,L,1000);
y = linspace(0,.25,1000);
z = linspace(0,.7,1000);
%% Section 2: Reactions

%Horizontal

R_yh = F;
M_zh = -(L-d)*(F);
M_xh = -(r+t/2)*F;
%Angled

theta = 45; %deg
F_xa = F*cos(theta); 
F_ya = -F*sin(theta); 

R_xa = -F_xa; 
R_ya = -F_ya;

M_za = -(L-d)*(F*sin(theta));
M_ya = (r+t/2)*(F*cos(theta));
M_xa = (r+t/2)*(F*sin(theta));

%Vertical

R_xv = -F;
M_yv = (r+t/2)*F;

%% Section 3: Singularity Functions

% shear

%horizontal

Vh_x = R_yh - F.*(x>3.5);
Mh_x = M_zh + R_yh*x - F.*(x>3.5).*(x-3.5);

% angled
Va_x = R_ya - R_ya.*(x>3.5);
Ma_x = M_za + R_ya*x - R_ya.*(x>3.5).*(x-3.5);

% Axial

%angled

Va_y = -R_xa + R_xa.*(y>.25);
Ma_y = M_xa - R_xa*x + R_xa.*(x>.25).*(x-.25);

%vert

Vv_y = -F + F.*(y>.25);
Mv_y = M_xa - F*x + F.*(y>.25).*(y-.25);

% z

%angled
Ma_z = M_ya-M_ya.*(z>.7);

%vert
Mv_z = M_yv-M_yv.*(z>.7);

figure (1)

subplot(10,1,1)
area(x,Vh_x)
[maxvalue1,i] = max(abs(Vh_x));
hold on
plot(x(i),Vh_x(i),'*')
ylabel('V(x)')
ylim([min([1.2*min(Vh_x),0,-1.2*min(Vh_x)]),max([0,1.2*max(Vh_x),-1.2*max(Vh_x)])]);
xlim([0,1.2*L])
hold off

subplot(10,1,2)
area(x,Mh_x)
[maxvalue2,n] = max(abs(Mh_x));
hold on
plot(x(n),Mh_x(n),'*')
ylabel('M(x)')
ylim([min([1.2*min(Mh_x),0,-1.2*min(Mh_x)]),max([0,1.2*max(Mh_x),-1.2*max(Mh_x)])]);
xlim([0,1.2*L])
hold off

subplot(10,1,3)
area(x,Va_x)
[maxvalue3,k] = max(abs(Va_x));
hold on
plot(x(k),Va_x(k),'*')
ylabel('V(x)')
ylim([min([1.2*min(Va_x),0,-1.2*min(Va_x)]),max([0,1.2*max(Va_x),-1.2*max(Va_x)])]);
xlim([0,1.2*L])
hold off

subplot(10,1,4)
area(x,Ma_x)
[maxvalue4,m] = max(abs(Ma_x));
hold on
plot(x(m),Ma_x(m),'*')
ylabel('M(x)')
ylim([min([1.2*min(Ma_x),0,-1.2*min(Ma_x)]),max([0,1.2*max(Ma_x),-1.2*max(Ma_x)])]);
xlim([0,1.2*L])
hold off

subplot(10,1,5)
area(y,Va_y)
[maxvalue5,q] = max(abs(Va_y));
hold on
plot(x(q),Va_y(q),'*')
ylabel('V(y)')
ylim([min([1.2*min(Va_y),0,-1.2*min(Va_y)]),max([0,1.2*max(Va_y),-1.2*max(Va_y)])]);
xlim([0,1.2*.25])
hold off

subplot(10,1,6)
area(y,Ma_y)
[maxvalue6,s] = max(abs(Ma_y));
hold on
plot(y(s),Ma_y(s),'*')
ylabel('M(y)')
ylim([min([1.2*min(Ma_y),0,-1.2*min(Ma_y)]),max([0,1.2*max(Ma_y),-1.2*max(Ma_y)])]);
xlim([0,1.2*.25])
hold off

subplot(10,1,7)
area(y,Vv_y)
[maxvalue7,o] = max(abs(Vv_y));
hold on
plot(y(o),Vv_y(o),'*')
ylabel('V(y)')
ylim([min([1.2*min(Vv_y),0,-1.2*min(Vv_y)]),max([0,1.2*max(Vv_y),-1.2*max(Vv_y)])]);
xlim([0,1.2*.25])
hold off

subplot(10,1,8)
area(y,Mv_y)
[maxvalue8,p] = max(abs(Mv_y));
hold on
plot(y(p),Mv_y(p),'*')
ylabel('M(y)')
ylim([min([1.2*min(Mv_y),0,-1.2*min(Mv_y)]),max([0,1.2*max(Mv_y),-1.2*max(Mv_y)])]);
xlim([0,1.2*.25])
hold off

subplot(10,1,9)
area(z,Ma_z)
[maxvalue9,u] = max(abs(Ma_z));
hold on
plot(z(u),Ma_z(u),'*')
ylabel('M(z)')
ylim([min([1.2*min(Ma_z),0,-1.2*min(Ma_z)]),max([0,1.2*max(Ma_z),-1.2*max(Ma_z)])]);
xlim([0,1.2*.7])
hold off

subplot(10,1,10)
area(z,Mv_z)
[maxvalue10,v] = max(abs(Mv_z));
hold on
plot(z(v),Mv_z(v),'*')
ylabel('M(z)')
ylim([min([1.2*min(Mv_z),0,-1.2*min(Mv_z)]),max([0,1.2*max(Mv_z),-1.2*max(Mv_z)])]);
xlim([0,1.2*.7])
hold off

%% Section 4
%horizontal
sigh = [-1200, 1166.4,0
    1166.4, 0, 0
    0,0,0];
ph = sort(eig(sigh),'descend');

VSh = sqrt((ph(1).^2)+(ph(2).^2)+(ph(3)).^2 - (ph(1)*ph(2)+ph(2)*ph(3)+ph(3)*ph(1)));

%angled
siga = [-1021.714, 1101.6,0
    1101.6,0,0
    0,0,0];
pa = sort(eig(siga),'descend');

VSa = sqrt((pa(1).^2)+(pa(2).^2)+(pa(3)).^2 - (pa(1)*pa(2)+pa(2)*pa(3)+pa(3)*pa(1)));

%vertical
sigv = [2592,0,0
    0,0,0
    0,0,0];
pv = sort(eig(sigv),'descend');

VSv = sqrt((pv(1).^2)+(pv(2).^2)+(pv(3)).^2 - (pv(1)*pv(2)+pv(2)*pv(3)+pv(3)*pv(1)));
