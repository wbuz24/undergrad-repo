% HW 1

clc
clear all
clear vars
%% Initialize values
E = 206.8*10^9;  
G = 80.8*10^9;
p_rat = .28;

sig_x = 372; 
sig_y = 25;
sig_z = 17;
tao_xy = 52;
tao_yz = 177;
tao_xz = 108;

sig = [sig_x, tao_xy, tao_xz;
    tao_xy, sig_y, tao_yz;
    tao_xz, tao_yz, sig_z].*10^6;


%% principle stresses
%principle stresses are displayed in descending order

p_stress = sort(eig(sig), 'descend');

%% maximum shear stress

tao_max = (p_stress(1)-p_stress(3))/2;
%% strains 

strain = [1/E, -p_rat/E, -p_rat/E, 0, 0, 0;
    -p_rat/E, 1/E, -p_rat/E, 0, 0, 0;
    -p_rat/E, -p_rat/E, 1/E, 0, 0, 0;
    0, 0, 0, 1/G, 0, 0;
    0, 0, 0, 0, 1/G, 0;
    0, 0, 0, 0, 0, 1/G];

sigma = [sig_x; sig_y; sig_z; tao_xy; tao_yz; tao_xz]*10^6;
app_strain  = strain*sigma.*1000;

str_x = app_strain(1);
str_y = app_strain(2);
str_z = app_strain(3);
gamma_x = app_strain(4);
gamma_y = app_strain(5);
gamma_z = app_strain(6);

%% principle strains
% principle strains are displayed in descending order
e = [str_x, gamma_x, gamma_z;
    gamma_x, str_y, gamma_y;
    gamma_z, gamma_y, str_z];
p_strain = sort(eig(e),'descend');
