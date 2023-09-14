%% HW 3
clear 
clc
%% P1
d = 4.17;
D = 7.7;
r = (D-d)/2;
K_t = .90879*(r/d).^(-.28598);
sig_0 = 5400; 
c = 4.17/2;
I = (pi*d.^4)/64;
sig_nom1 = sig_0*c/I;
sig_max1 = K_t*sig_nom1;

%% P2

s_y = 26000;
sig_x = -30;
sig_y = 1070;
sig_z = -1190;
tao_xy = -260;
tao_yz = 1080;
tao_xz = -50;

sig_app = [sig_x, tao_xy, tao_yz
            tao_xy, sig_y, tao_xz
            tao_yz, tao_xz, sig_z];
sig_prin = sort(eig(sig_app),'descend');
sig_vm = sqrt((sig_prin(1).^2) + (sig_prin(2).^2) + (sig_prin(3).^2) - (sig_prin(1)*sig_prin(2)+sig_prin(2)*sig_prin(3)+sig_prin(3)*sig_prin(1)));

FOSa = s_y/sig_vm;

%% P3

s_ut = 22000;
s_uc = 83000;

sig_a = -1180;
sig_b = 250;
sig_c = -420;
tao_yx = 650;
tao_zy = -920;
tao_zx = -1170;

sig_ap = [sig_a, tao_yx, tao_zy
            tao_yx, sig_b, tao_zx
            tao_zy, tao_zx, sig_c];
        
p = sort(eig(sig_ap),'descend');        


C1 = .5*(abs(p(1)-p(2))+((2*s_ut-abs(s_uc))/-abs(s_uc))*(p(1)+p(2)));
C2 = .5*(abs(p(2)-p(3))+((2*s_ut-abs(s_uc))/-abs(s_uc))*(p(2)+p(3)));
C3 = .5*(abs(p(3)-p(1))+((2*s_ut-abs(s_uc))/-abs(s_uc))*(p(3)+p(1)));

maxi = [C1, C2, C3, p(1), p(2), p(3), 0];
sig_p = max(maxi);
FOSb = s_ut/sig_p;
