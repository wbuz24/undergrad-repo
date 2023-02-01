%% HW 7
clear
clc

G = 11.5;
d = .048;
C = 8.8;
D = C*d;
cycles = 4*10.^5;
reliability = .99;

Fwork = 2.6;
F = .12*Fwork;
Nt = 13;
Na = Nt-1;

k = (d*G)/(8*(C.^3)*Na);
yi = F/k;
yw = Fwork/k;
ycl = .15*yw;
ys = yi + yw + ycl;

Ls = d*Nt;
Lf = Ls + yi + yw + ycl;

Fshut = k*ys;

Sut = 2153.5*d.^(-.1625);
Sus = .67*Sut;
Sys = .6*Sut;
Ks = (1 + (.5/C));
Sfwp = .42*Sut;
Sfw = Sfwp*.814;
Sewp = 465;
m = (.5*Sfw)/(Sus - .5*Sfw);
Sfs = m*Sus;
Sm = .9*Sut;

b = (1/(log(1000)-log(10.^6)))*log(Sm/Sfw);
athrow = log(Sm) - 3*b;
a = log(athrow);

taoshut = Ks*((8*Fshut*C)/(pi()*d.^2));
tao = Ks*((8*F*C)/(pi()*d.^2));

Ns = Sys/tao;

Fa = (Fwork - F)/2;
Fm = (Fwork + F)/2;

taom = Ks*((8*Fm*C)/(pi()*d.^2));
taoa = Ks*((8*Fa*C)/(pi()*d.^2));

sig = [taoa;
        0;
        taom];

vm = sqrt(sig(1).^2 + sig(3).^2 - (sig(1)*sig(2) + sig(2)*sig(3) + sig(3)*sig(1)));
FOSf = Sfs/vm;





