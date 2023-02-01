%% P2 Bike arm contin.

%% initialize vars

Sy = 77;
Sut = 91;
L = 6; % in
a = 4; % in to center of pedal
F2 = 7; % lbs (weight of pedal)
F1 = 120; % lbs (combined weight)
Y = 14; % years
minutes = 14*300*4*60; % minutes bike will be in service
N = minutes * 2; % cycles
D = 10; % diameter of bar
d = 2.2; % diameter of hole
J = (pi()*D.^4)/32; % moment of inertia
J2 = (pi()*(D.^4-d.^4))/32;
I = (pi()*D.^4)/64; % mass moment of inertia
Iadjust = I-((D*d.^3)/12);
weight = F1-F2; % weight of person
theta = 0;
wbar = ((pi()*(D/2).^2)*.8); % distributed load w

%Csize = .6; % larger D
Csize = .869*D.^(-.097);
Csurf = min(2.7*Sut.^(-.265),1);
Sm = .75*Sut;
sqa = ((.062-.07)/10)+.07;
sqr = sqrt(d);
Se = Csize*Csurf*.7*.868*(Sut/2);


b = (1/(log(1000)-log(1000000))*log(Sm/Se));
la = log(Sm)-3*b;
A = log(la);
strength = A*N.^b;

q = 1/(1+(sqa/sqr));
Ktz = 1.58990-.63550*log(d/D);
Ktx = 3.92150 - 24.435*(d/D) + 234.06*(d/D).^2 - 1200.5*(d/D).^3 + 3059.5*(d/D).^4 - 3042.4*(d/D).^5;
Kfz = 1+q*(Ktz-1);
Kfx = 1+q*(Ktx-1);



%% Loop positions 1-8

for i = 1:8
 zero = zeros([1,8]);
  if (theta > -90)
      F = F1;  
  else 
      F = F2;
  end
  % Reactions
  Ry(i) = F*cosd(theta) + wbar*L*cosd(theta);
  Rx(i) = (F*sind(theta) + wbar*D*sind(theta));
  Mz(i) = (F*cosd(theta))*(L-(3*d/2)) + (wbar*(L/2)*L*cosd(theta));
  Mx(i) = (F*cosd(theta))*a;
  My(i) = (F*sind(theta))*a;
  
  %maximum stresses
  sigx(i) = Rx(i)/(pi()*(D/2).^2);
  sigxa(i) = Rx(i)/((pi()*(D/2).^2)-(D*d));
  
  sigy(i) = (4*Ry(i))/(3*(pi()*(D./2).^2));
  sigya(i) = (4*Ry(i))/(3*((pi()*(D/2).^2)-(D*d)));
  
  taoxy(i) = (Mx(i)*(D/2))/J;
  taoxya(i) = Ktx*((Mx(i)*(D/2))/J2);
  
  taoyzb(i) = (My(i)*(D/2))/I;
 
  taoxz(i) = Mz(i)*(D./2)/I;
  taoxza(i) = Ktz*(Mz(i)*((D-d)./2)/Iadjust);
  
  
% Principle Stresses
   p(i, :) = sort(eig([ sigx(i), taoxy(i), taoxz(i);
                taoxy(i), sigy(i), 0;
                taoxz(i), 0, 0]), 'descend');
   pb(i, :) = sort(eig([sigx(i), taoxy(i), 0;
                    taoxy(i), 0, taoyzb(i);
                    0, taoyzb(i), 0]), 'descend');
   pa(i, :) = sort(eig([ sigxa(i), taoxya(i), taoxza(i);
                taoxya(i), sigya(i), 0;
                taoxza(i), 0, 0]), 'descend');
            
%Von Mises Stresses
 vm(i) = sqrt((p(i,1).^2)+(p(i,2).^2)+(p(i,3).^2)+(p(i,1)*p(i,2)+p(i,2)*p(i,3)+p(i,3)*p(i,1)));
 vmb(i) = sqrt((pb(i,1).^2)+(pb(i,2).^2)+(pb(i,3).^2)+(pb(i,1)*pb(i,2)+pb(i,2)*pb(i,3)+pb(i,3)*pb(i,1)));
 vma(i) = sqrt((pa(i,1).^2)+(pa(i,2).^2)+(pa(i,3).^2)+(pa(i,1)*pa(i,2)+pa(i,2)*pa(i,3)+pa(i,3)*pa(i,1)));

theta = theta - 45;
end
% peak and base
 peak = max(vm);
 base = min(vm);
 
 peakb = max(vmb);
 baseb = min(vmb);
 
 peaka = max(vma);
 basea = min(vma);
 
 mean = (peak+base)/2;
 alt = (peak-base)/2;
 
 meanb = (peakb+baseb)/2;
 altb = (peakb-baseb)/2;
 
 meana = (peaka+basea)/2;
 alta = (peaka-basea)/2;
 
 
 Kfm = (Sy - max(Kfz,Kfx)*mean)/(abs(mean));

 FOSy = Sy/(alt+mean);
 FOSf = (Sut*strength)/((Sut*alt)+(strength*mean));

 FOSyb = Sy/(altb+meanb);
 FOSfb = (Sut*strength)/((Sut*altb)+(strength*meanb));
 
 FOSya = Sy/(alta+meana);
 FOSfa = (Sut*strength)/((Sut*alta)+(strength*meana));