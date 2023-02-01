%% HW 6 

%% P1
%Sy = 10000;

Pi = 109;
Po = 14.7;

ri = 10.32/2;
ro = 15.43/2;
r = (ro-ri)/2;
sigtan = ((Pi*ri).^2-(Po*ro).^2)/(ro.^2-ri.^2) + (ri.^2*ro.^2*(Pi-Po))/(r.^2*(ro.^2-ri.^2));
sigrad = ((Pi*ri).^2-(Po*ro).^2)/(ro.^2-ri.^2) - (ri.^2*ro.^2*(Pi-Po))/(r.^2*(ro.^2-ri.^2));
sigax = ((Pi*ri).^2-(Po*ro).^2)/(ro.^2-ri.^2);
sigbar = [sigtan;
          sigax;
          sigrad];
vm = sqrt(sigtan.^2 + sigax.^2 + sigrad.^2 - sigtan*sigax - sigax*sigrad - sigrad*sigtan);

%FOS = Sy/vm;