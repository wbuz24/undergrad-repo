%% project 3
format short G
clc
clear 


%% initialize


L = 14; % in
torquemax = 200; %lb-in
torquemin = 110; %lb-in 
Fapplied = 46; % lb



% material 
Sy = 66; %kpsi
Sut = 120; 
stre = .5*Sut;
Csurf = min(14.4*Sut.^(-.718),1);
d = .743;
rshaft = d/2;


% moments shaft
area = pi()*rshaft.^2;

wload = area*.28;
wsprock = .28*(pi()*(4.^2-(d.^2))/4);


R = Fapplied + (wload*(L/2)) + wsprock*(3/4);
Mmid = -(wsprock*(.5*L-(L/3))) - ((L/4)*(L/2)*wload) - (Fapplied *((L/2)-(L/3))) + R*(L/2);
Ma = -46*(3/8) - wsprock*(3/8)*(3/4) - wload*((L/3 + 3/8)*((L/3 + (3/8))/2)) - R*((L/3) + (3/8)); 

% Torques
Talt = (torquemax-torquemin)/2;
Tmean = (torquemax+torquemin)/2;

Fa = Talt/rshaft;
Fm = Tmean/rshaft;



% Correction factors- shaft
if (d <= .3)
    Csize = 1;
elseif (d <= 10)
    Csize = .869*d.^(-.097);
else 
    Csize = .6;
end 

Se = Csize*.753*stre*Csurf; % Creliab = .753



% key
Csurfkey = .9074;
Cloadkey = 1;
Csizekey = Cloadkey;
Ctempkey = Cloadkey;
Creliabkey = .868;
Sykey = 26; %kpsi
Sutkey = 55;
Lkey = .195; %in
Wkey = .25; 
hkey = .25;
strekey = Sutkey*.5;

% keyway
rdkeyway = .021;
Ktskeyway = 3;
Ktkeyway = 2.2;
Ashear = Lkey*Wkey;
Sekey = Cloadkey*Creliabkey*strekey;
rta = .049;
rtr = .021*d;

taoA = Fa/Ashear;
taoM = Fm/Ashear;

Fbear = Fa + Fm;
Abear = (Lkey * (hkey/2));
sigx = Fbear/Abear;



q = 1/(1+(rta/rtr));
Kf = 1+q*(Ktkeyway-1);

signoma = (32*Ma/pi()*d.^3);
sigpeaknoma = signoma*2;

throwa = abs(Kf*sigpeaknoma);

Kfm = Kf;

Tanom = (16*Talt)/(pi()*d.^3);

Tsignoma = sqrt(3)*Tanom;

Tsigpeaknom = Tsignoma*2;


Kfs = 1 + q*(Ktskeyway-1);

Ksthrow = abs(Kfs*Tsigpeaknom);

Kfsm = Kfs;


% moments key
Makey = Fapplied*((4+d)/2);
siga = [taoA;
        0;
        -taoA];
sigm = [taoM;
        0;
        -taoM]; 

sigaprime = sqrt(siga(1).^2 + siga(2).^2 + siga(3).^2 - siga(1)*siga(2) - siga(2)*siga(3) - siga(3)*siga(1));
sigmprime = sqrt(sigm(1).^2 + sigm(2).^2 + sigm(3).^2 - sigm(1)*sigm(2) - sigm(2)*sigm(3) - sigm(3)*sigm(1));


% factor of safety calcs
FOSthrow = (sigaprime/(1000*Se)) + (sigmprime/(1000*Sut));

FOSmkey = 1/FOSthrow;
FOSm = ((pi()*d.^3)/32)/(((sqrt(Mmid.^2+(.75*Talt).^2))/(1000*Se))+(sqrt((.75*Tmean).^2))/(1000*Sut));
FOSkeyway = ((pi()*d.^3)/32)/((sqrt((Kf*Ma).^2+(.75*(Kfs*Talt).^2))/(1000*Se))+(sqrt((.75*(Kfsm*Tmean).^2)))/(1000*Sut));
FOSbear = ((1000*Sy)/(sigx));





