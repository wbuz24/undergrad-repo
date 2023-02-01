%% HW 4
clear
clc
%% P1
p = [125; 64; -51];
d = 60;
sig_vm = sqrt(p(1).^2 + p(2).^2 + p(3).^2 - (p(1)*p(2)+p(2)*p(3)+p(3)*p(1)));

%% P2

FOSf = 2.3;

strength = FOSf*sig_vm;
A95 = .010462*(d.^2);
deq = sqrt(A95/.07066);

Csize = 1.189*60.^(-.097);
Csurf = min(4.51*524.^(-.265),1);

Sm = .9*524;
Strengthe = Csize*Csurf*.868*.5*524;
b = (1/(log(1000)-log(1000000)))*log(Sm/Strengthe);
a = Sm/(1000.^(b));

N = (strength/a).^(1/b);