## eVtol GUI
import os
import sys
import csv
import tkinter as tk
import numpy as np
from matplotlib import pyplot as plt
import pandas as pd
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
#from cProfile import label

A = [0, 0] #
dummy = [0, 0]
C_L = [0, 0]
C_d_min = [0, 0]
C_D = [0, 0]
D = [0, 0]
alp = [0, 0]
alpha = [0, 0] 
M_b = [0, 0]
E_base = [0, 0]
P_clb = [0, 0]
P_cru = [0, 0]
P_hov = [0, 0]
P_des = [0, 0]
E_dens = [0, 0]
E_hov = [0, 0]
P_dens = [0, 0]
E_res = [0, 0]
E_cru = [0, 0]
E_clb = [0, 0]
E_des = [0, 0]
E_total = [0, 0]
E_clb = [0, 0] 

w_P_hov = [0, 0]
w_P_cru = [0, 0]
w_P_clb = [0, 0]
w_P_des = [0, 0]
w_E_hov = [0, 0]
w_E_clb = [0, 0]
w_E_cru = [0, 0]
w_E_des = [0, 0]
w_E_res = [0, 0]
w_E_base = [0, 0]
w_E_total = [0, 0]
w_E_dens = [0, 0]
w_P_dens = [0, 0]
T_h = [0, 0]
MTOM = [0, 0]
w_T_h = [0, 0]
v_i = [0, 0]
P_hov_ideal = [0, 0]
w_A = [0, 0]
w_v_i = [0, 0]
w_P_hov_ideal = [0, 0]  
w_P_hov = [0, 0]
S = [0, 0]
Ar = [0, 0]
C_d_min = [0, 0]
w_C_D = [0 ,0]
w_D = [0, 0]
w_C_L = [0, 0]
w_M_b = [0, 0]
v_c = [0, 0]

def load():
   global m_pl, ft, v_c, v_max, t_e_10k, t_e_15k, h_max, GTOW, T_max, T_min, t_r, P_e, P_gen, rho, v_clb, b, c_r, c_t, hov_time, climb_time, cruise_time, descent_time, reserve, DL, FOM, e, w_DL, w_FOM, w_e, w_eta_prop, w_swet, w_C_fe
   m_pl = [float(par1bl.get()), float(par1obj.get())] # lb
   ft = [float(par2bl.get()), float(par2obj.get())] #mph
   v_max = [float(par3bl.get()), float(par3obj.get())] #mph
   t_e_10k = [float(par4bl.get()), float(par4obj.get())] # hr
   t_e_15k = [float(par5bl.get()), float(par5obj.get())] #hr
   h_max = [float(par6bl.get()), float(par6obj.get())] #ft
   GTOW = [float(par7bl.get()), float(par7obj.get())] #lb
   T_max = [float(par8bl.get()), float(par8obj.get())] #C
   T_min = [float(par9bl.get()), float(par9obj.get())] #C
   t_r = [float(par10bl.get()), float(par10obj.get())] #min
   P_e = [float(par11bl.get()), float(par11obj.get())] #hp
   P_gen = [float(par12bl.get()), float(par12obj.get())] #W
   rho = [float(par13bl.get()), float(par13obj.get())] #kg/m^3 #
   v_clb = [float(par14bl.get()), float(par14obj.get())] #ft/s
   b = [float(par15bl.get()), float(par15obj.get())] #in
   c_r = [float(par16bl.get()), float(par16obj.get())] #in
   c_t = [float(par17bl.get()), float(par17obj.get())] #in
   hov_time = [float(par18bl.get()), float(par18obj.get())] # hr
   climb_time = [float(par19bl.get()), float(par19obj.get())] #hr
   cruise_time = [float(par20bl.get()), float(par20obj.get())] #hr
   descent_time = [float(par21bl.get()), float(par21obj.get())] #hr
   reserve = [float(par22bl.get()), float(par22obj.get())] #hr
   # conv units
   # wingless params
   DL = [float(par23bl.get()), float(par23obj.get())] # kg/m^2
   FOM = [float(par24bl.get()), float(par24obj.get())]
   e = [float(par25bl.get()), float(par25obj.get())]
   #winged params
   w_DL = [float(par26bl.get()), float(par26obj.get())] #kg/m^2
   w_FOM = [float(par27bl.get()), float(par27obj.get())]
   w_e = [float(par28bl.get()), float(par28obj.get())]
   w_eta_prop = [float(par29bl.get()), float(par29obj.get())]
   w_swet = [float(par30bl.get()), float(par30obj.get())]
   w_C_fe = [float(par31bl.get()), float(par31obj.get())]

def convert():
   for i in range(2):
      MTOM[i] = GTOW[i] * .453592 #kg #
      m_pl[i] = m_pl[i] * .453592 #kg
      v_c[i] = ft[i] * .44704 #m/s #
      v_max[i] = v_max[i] * .44704
      t_e_10k[i] = t_e_10k[i] * 3600 # s
      t_e_15k[i] = t_e_15k[i] * 3600
      h_max[i] = h_max[i] * .3048 # m
      T_max[i] = T_max[i] + 273.15
      T_min[i] = T_min[i] + 273.15
      t_r[i] = t_r[i] * 60 # s
      v_clb[i] = v_clb[i] * .44704 #m/s #
      b[i] = b[i] * .0254 # m
      c_r[i] = c_r[i] * .0254 # m
      c_t[i] = c_t[i] * .0254 
      T_h[i] = MTOM[i] * 9.81
      w_T_h[i] = T_h[i]
      
def csvread():
   filePath = fn.get()
   df = pd.read_csv(filePath)
   
   par1bl.delete(0, 'end')
   par2bl.delete(0, 'end')
   par3bl.delete(0, 'end')
   par4bl.delete(0, 'end')
   par5bl.delete(0, 'end')
   par6bl.delete(0, 'end')
   par7bl.delete(0, 'end')
   par8bl.delete(0, 'end')
   par9bl.delete(0, 'end')
   par10bl.delete(0, 'end')
   par11bl.delete(0, 'end')
   par12bl.delete(0, 'end')
   par13bl.delete(0, 'end')
   par14bl.delete(0, 'end')
   par15bl.delete(0, 'end')
   par16bl.delete(0, 'end')
   par17bl.delete(0, 'end')
   par18bl.delete(0, 'end')
   par19bl.delete(0, 'end')
   par20bl.delete(0, 'end')
   par21bl.delete(0, 'end')
   par22bl.delete(0, 'end')
   par23bl.delete(0, 'end')
   par24bl.delete(0, 'end')
   par25bl.delete(0, 'end')
   par26bl.delete(0, 'end')
   par27bl.delete(0, 'end')
   par28bl.delete(0, 'end')
   par29bl.delete(0, 'end')
   par30bl.delete(0, 'end')
   par31bl.delete(0, 'end')

   par1obj.delete(0, 'end')
   par2obj.delete(0, 'end')
   par3obj.delete(0, 'end')
   par4obj.delete(0, 'end')
   par5obj.delete(0, 'end')
   par6obj.delete(0, 'end')
   par7obj.delete(0, 'end')
   par8obj.delete(0, 'end')
   par9obj.delete(0, 'end')
   par10obj.delete(0, 'end')
   par11obj.delete(0, 'end')
   par12obj.delete(0, 'end')
   par13obj.delete(0, 'end')
   par14obj.delete(0, 'end')
   par15obj.delete(0, 'end')
   par16obj.delete(0, 'end')
   par17obj.delete(0, 'end')
   par18obj.delete(0, 'end')
   par19obj.delete(0, 'end')
   par20obj.delete(0, 'end')
   par21obj.delete(0, 'end')
   par22obj.delete(0, 'end')
   par23obj.delete(0, 'end')
   par24obj.delete(0, 'end')
   par25obj.delete(0, 'end')
   par26obj.delete(0, 'end')
   par27obj.delete(0, 'end')
   par28obj.delete(0, 'end')
   par29obj.delete(0, 'end')
   par30obj.delete(0, 'end')
   par31obj.delete(0, 'end')

   par1bl.insert(0, df.loc[0, 'baseline'])
   par2bl.insert(0, df.loc[1, 'baseline'])
   par3bl.insert(0, df.loc[2, 'baseline'])
   par4bl.insert(0, df.loc[3, 'baseline'])
   par5bl.insert(0, df.loc[4, 'baseline'])
   par6bl.insert(0, df.loc[5, 'baseline'])
   par7bl.insert(0, df.loc[6, 'baseline'])
   par8bl.insert(0, df.loc[7, 'baseline'])
   par9bl.insert(0, df.loc[8, 'baseline'])
   par10bl.insert(0, df.loc[9, 'baseline'])
   par11bl.insert(0, df.loc[10, 'baseline'])
   par12bl.insert(0, df.loc[11, 'baseline'])
   par13bl.insert(0, df.loc[12, 'baseline'])
   par14bl.insert(0, df.loc[13, 'baseline'])
   par15bl.insert(0, df.loc[14, 'baseline'])
   par16bl.insert(0, df.loc[15, 'baseline'])
   par17bl.insert(0, df.loc[16, 'baseline'])
   par18bl.insert(0, df.loc[17, 'baseline'])
   par19bl.insert(0, df.loc[18, 'baseline'])
   par20bl.insert(0, df.loc[19, 'baseline'])
   par21bl.insert(0, df.loc[20, 'baseline'])
   par22bl.insert(0, df.loc[21, 'baseline'])
   par23bl.insert(0, df.loc[22, 'baseline'])
   par24bl.insert(0, df.loc[23, 'baseline'])
   par25bl.insert(0, df.loc[24, 'baseline'])
   par26bl.insert(0, df.loc[25, 'baseline'])
   par27bl.insert(0, df.loc[26, 'baseline'])
   par28bl.insert(0, df.loc[27, 'baseline'])
   par29bl.insert(0, df.loc[28, 'baseline'])
   par30bl.insert(0, df.loc[29, 'baseline'])
   par31bl.insert(0, df.loc[30, 'baseline'])

   par1obj.insert(0, df.loc[0, 'objective'])
   par2obj.insert(0, df.loc[1, 'objective'])
   par3obj.insert(0, df.loc[2, 'objective'])
   par4obj.insert(0, df.loc[3, 'objective'])
   par5obj.insert(0, df.loc[4, 'objective'])
   par6obj.insert(0, df.loc[5, 'objective'])
   par7obj.insert(0, df.loc[6, 'objective'])
   par8obj.insert(0, df.loc[7, 'objective'])
   par9obj.insert(0, df.loc[8, 'objective'])
   par10obj.insert(0, df.loc[9, 'objective'])
   par11obj.insert(0, df.loc[10, 'objective'])
   par12obj.insert(0, df.loc[11, 'objective'])
   par13obj.insert(0, df.loc[12, 'objective'])
   par14obj.insert(0, df.loc[13, 'objective'])
   par15obj.insert(0, df.loc[14, 'objective'])
   par16obj.insert(0, df.loc[15, 'objective'])
   par17obj.insert(0, df.loc[16, 'objective'])
   par18obj.insert(0, df.loc[17, 'objective'])
   par19obj.insert(0, df.loc[18, 'objective'])
   par20obj.insert(0, df.loc[19, 'objective'])
   par21obj.insert(0, df.loc[20, 'objective'])
   par22obj.insert(0, df.loc[21, 'objective'])
   par23obj.insert(0, df.loc[22, 'objective'])
   par24obj.insert(0, df.loc[23, 'objective'])
   par25obj.insert(0, df.loc[24, 'objective'])
   par26obj.insert(0, df.loc[25, 'objective'])
   par27obj.insert(0, df.loc[26, 'objective'])
   par28obj.insert(0, df.loc[27, 'objective'])
   par29obj.insert(0, df.loc[28, 'objective'])
   par30obj.insert(0, df.loc[29, 'objective'])
   par31obj.insert(0, df.loc[30, 'objective'])

def wingless():
   load() # load inputs from text fields
   convert() # convert units
   for i in range (2):
      A[i] = (MTOM[i] / DL[i]) # kg/m^2
      v_i[i] = np.sqrt(T_h[i] / (2 * rho[i] * A[i]))
      P_hov_ideal[i] = T_h[i]*v_i[i]
      P_hov[i] = (P_hov_ideal[i] / FOM[i])
      C_L[i] = (DL[i] * 9.81) / (rho[i] * .5 * (v_c[i]**2))
      C_d_min[i] = C_L[i]**2 / (e[i] * 4)
      C_D[i] = C_d_min[i] + (C_L[i] * C_L[i] / (e[i] * 4))
   
      P_clb[i] = (P_hov[i] * ((v_clb[i] / (v_i[i] * 2)) + (((v_clb[i] / (v_i[i] * 2))**2) + 1)**.5))
      P_des[i] = (P_hov[i] * ((v_clb[i] / (v_i[i] * 2)) - (((v_clb[i] / (v_i[i] * 2))**2) - 1)**.5))
      D[i] = (.5 * rho[i] * (v_c[i]**2) * A[i] * C_D[i])
      alp[i] = np.arctan(D[i] / T_h[i])
      alpha[i] = alp[i] * (180 / np.pi)
   
      P_cru[i] = (T_h[i] * (v_c[i] * np.cos(alp[i]) + v_i[i]))
      E_hov[i] = (P_hov[i] * hov_time[i] + P_hov[i] * hov_time[i])
      E_clb[i] = (P_clb[i] * climb_time[i]) 
      E_cru[i] = (P_cru[i] * cruise_time[i])
      E_des[i] = (P_des[i] * descent_time[i])
      E_res[i] = (P_cru[i] * reserve[i])
      E_base[i] = (P_gen[i] * (2 * hov_time[i] + climb_time[i] + cruise_time[i] + descent_time[i] + reserve[i])) 
      E_total[i] = (2 * (P_hov[i] * hov_time[i]) + P_clb[i] * climb_time[i] + P_cru[i] * cruise_time[i] + P_des[i] * descent_time[i] + P_cru[i] * reserve[i] + E_base[i])

      M_b[i] = ((MTOM[i] * .5))
      E_dens[i] = (E_total[i] / M_b[i])
      P_dens[i] = (np.maximum(P_cru[i], P_clb[i]) / M_b[i])  
      
   return E_base, P_clb, P_cru, P_hov, P_des, E_dens, E_hov, P_dens, E_res, E_cru, E_clb, E_des, E_total, E_clb

def winged():
   load() # load input parameters from text fields
   convert() # convert units
   for i in range(2):
      w_A[i] = (MTOM[i] / w_DL[i])
      w_v_i[i] = (((w_T_h[i] / (2 * w_A[i] * rho[i]))**.5))
      w_P_hov_ideal[i] = (w_v_i[i] * w_T_h[i])
      w_P_hov[i] = (w_P_hov_ideal[i] / w_FOM[i])
      S[i] = ((c_r[i] + c_t[i]) * .5 * b[i])
      Ar[i] = ((b[i]**2) / S[i])
      w_C_L[i] = ((MTOM[i] * 9.81) / ((rho[i] * .5) * (v_c[i]**2) * S[i]))
      C_d_min[i] = (w_swet[i] * w_C_fe[i])
      w_C_D[i] = (C_d_min[i] + (4/3) * (1 / (np.pi * e[i] * Ar[i])) * (w_C_L[i]**2))
      w_D[i] = (w_C_D[i] * .5 * rho[i] * (v_c[i]**2) * S[i]) 
      
      w_P_cru[i] = ((w_D[i] * v_c[i]) / w_eta_prop[i])
      w_P_clb[i] = (w_P_hov[i] * ((v_clb[i] / ((w_v_i[i] * 2))) + (((v_clb[i] / (w_v_i[i] * 2))**2) + 1)**.5))
      w_P_des[i] = (w_P_hov[i] * ((v_clb[i] / ((w_v_i[i] * 2))) - (((v_clb[i] / (w_v_i[i] * 2))**2) - 1)**.5))
      w_E_hov[i] = (w_P_hov[i] * hov_time[i] + w_P_hov[i] * hov_time[i])
      w_E_clb[i] = (w_P_clb[i] * climb_time[i])
      w_E_cru[i] = (w_P_cru[i] * cruise_time[i])
      w_E_des[i] = (w_P_des[i] * descent_time[i])
      w_E_res[i] = (w_P_cru[i] * reserve[i])
      w_E_base = E_base
      w_E_total[i] = (2 * w_P_hov[i] * hov_time[i] + w_P_clb[i] * climb_time[i] + w_P_cru[i] * cruise_time[i] + w_P_des[i] * descent_time[i] + w_P_cru[i] * reserve[i] + w_E_base[i])
      w_M_b[i] = (MTOM[i] * .1)
      w_E_dens[i] = w_E_total[i] / w_M_b[i]
      w_P_dens[i] = (np.maximum(w_P_cru[i], w_P_clb[i]) / w_M_b[i])
   return w_P_hov, w_P_cru, w_P_clb, w_P_des, w_E_hov, w_E_clb, w_E_cru, w_E_des, w_E_res, w_E_base, w_E_dens, w_P_dens

def charts(): 
   chart_window = tk.Toplevel(window)
   chart_window.title("Power Requirements")
   chart_window.geometry("500x500")
   figbar = plt.figure(figsize = (5, 5), dpi = 100)
# bar chart
   plt.bar("Hover", P_hov, width = .2, color = 'r', bottom =None, align = 'edge')
   plt.bar("Hover", w_P_hov, width = -.2, color = 'b',bottom =None, align = 'edge')
   plt.bar("Cruise", P_cru, width = .2, color = 'r', bottom =None, align = 'edge')
   plt.bar("Cruise", w_P_cru, width = -.2, color = 'b', bottom=None, align = 'edge')
   plt.bar("Climb", P_clb, width = .2, color = 'r', bottom=None, align = 'edge')
   plt.bar("Climb", w_P_clb, width = -.2, color = 'b', bottom=None, align = 'edge')
   plt.bar("Descend", P_des, width = .2, color = 'r', bottom=None, align = 'edge')
   plt.bar("Descend", w_P_des, width = -.2, color = 'b', bottom=None, align = 'edge')
   plt.title('Wingless vs. Powered Lift') 
   plt.ylabel('Power (W)')
   #placing the canvas on the Tkinter window
   barcanvas = FigureCanvasTkAgg(figbar, chart_window)
   barcanvas.draw()
   barcanvas.get_tk_widget().pack()
      
# initialize window
window = tk.Tk()
window.geometry("1500x900")
window.title("eVtol Energy Calculator")

fn = tk.Entry(window, width = 20)
fn.grid(row = 1, column = 4, padx = (50, 0), pady = 1)
fn.insert(0, os.getcwd() + '/inputs.csv')

fnLabel = tk.Label(window, text='CSV File Location')
fnLabel.grid(row = 0, column = 4, padx = (50, 0), pady = 1)

file_button = tk.Button(window, text = "Import", command=csvread)
file_button.grid(row = 1, column = 5, pady = 1)

#check_button = tk.Button(window, width=5, text='CheckboxPlaceHolder', command=charts)
#check_button.grid(row = 6, column = 7)

chart_button = tk.Button(window, text="Power Distribution", command=charts)
chart_button.place(x = 475, y =575)

# labels for the parameter entry boxes
labelBl = tk.Label(window, text='Baseline')
labelBl.grid(row = 0, column = 1, pady = 1)
labelObj = tk.Label(window, text='Objective')
labelObj.grid(row = 0, column = 2, pady = 1)

label1 = tk.Label(window, text='Weight (lb):')
label1.grid(row = 1, column = 0, padx = (20, 1), pady = 1)
label2 = tk.Label(window, text='Cruise Speed (mph):')
label2.grid(row = 2, column = 0, padx = (20, 1), pady = 1)
label3 = tk.Label(window, text='Max Speed (mph):')
label3.grid(row = 3, column = 0, padx = (20, 1), pady = 1)
label4 = tk.Label(window, text='Endurance 10k ft (hr):')
label4.grid(row = 4, column = 0, padx = (20, 1), pady = 1)
label5 = tk.Label(window, text='Endurance 15k ft (hr):')
label5.grid(row = 5, column = 0, padx = (20, 1), pady = 1)
label6 = tk.Label(window, text='Altitude Ceiling (ft):')
label6.grid(row = 6, column = 0, padx = (20, 1), pady = 1)
label7 = tk.Label(window, text='Takeoff Weight (lb):')
label7.grid(row = 7, column = 0, padx = (20, 1), pady = 1)
label8 = tk.Label(window, text='Max Temp. (C):')
label8.grid(row = 8, column = 0, padx = (20, 1), pady = 1)
label9 = tk.Label(window, text='Min Temp (C):')
label9.grid(row = 9, column = 0, padx = (20, 1), pady = 1)
label10 = tk.Label(window, text='Reserve Time (min):')
label10.grid(row = 10, column = 0, padx = (20, 1), pady = 1)
label11 = tk.Label(window, text='Engine Power (hp):')
label11.grid(row = 11, column = 0, padx = (20, 1), pady = 1)
label12 = tk.Label(window, text='Power Generation (W):')
label12.grid(row = 12, column = 0, padx = (20, 1), pady = 1)
label13 = tk.Label(window, text='Air Density (kg/m^3):')
label13.grid(row = 13, column = 0, padx = (20, 1), pady = 1)
label14 = tk.Label(window, text='Climb Speed (ft/s):')
label14.grid(row = 14, column = 0, padx = (20, 1), pady = 1)
label15 = tk.Label(window, text='Wingspan (in):')
label15.grid(row = 15, column = 0, padx = (20, 1), pady = 1)
label16 = tk.Label(window, text='Root Chord (in):')
label16.grid(row = 16, column = 0, padx = (20, 1), pady = 1)
label17 = tk.Label(window, text='Taper Chord (in):')
label17.grid(row = 17, column = 0, padx = (20, 1), pady = 1)
label18 = tk.Label(window, text='Hover Time (hr):')
label18.grid(row = 18, column = 0, padx = (20, 1), pady = 1)
label19 = tk.Label(window, text='Climb Time (hr):')
label19.grid(row = 19, column = 0, padx = (20, 1), pady = 1)
label20 = tk.Label(window, text='Cruise Time (hr):')
label20.grid(row = 20, column = 0, padx = (20, 1), pady = 1)
label21 = tk.Label(window, text='Descent Time (hr):')
label21.grid(row = 21, column = 0, padx = (20, 1), pady = 1)
label22 = tk.Label(window, text='Reserve (hr):')
label22.grid(row = 22, column = 0, padx = (20, 1), pady = 1)

label23 = tk.Label(window, text='Baseline')
label23.grid(row = 5, column = 5, pady = 1)
label24 = tk.Label(window, text='Objective')
label24.grid(row = 5, column = 6, pady = 1)
label25 = tk.Label(window, text='Baseline')
label25.grid(row = 14, column = 5, pady = 1)
label26 = tk.Label(window, text='Objective')
label26.grid(row = 14, column = 6, pady = 1)

label27 = tk.Label(window, text='Disk Loading (kg/m^2):')
label27.grid(row = 6, column = 4, padx = (100, 0), pady = 1)
label28 = tk.Label(window, text='Figure of Merit:')
label28.grid(row = 7, column = 4, padx = (100, 0), pady = 1)
label29 = tk.Label(window, text='Oswald Factor:')
label29.grid(row = 8, column = 4, padx = (100, 0), pady = 1)
label30 = tk.Label(window, text='Disk Loading (kg/m^2):')
label30.grid(row = 15, column = 4, padx = (100, 0), pady = 1)
label31 = tk.Label(window, text='Figure of Merit:')
label31.grid(row = 16, column = 4, padx = (100, 0), pady = 1)
label32 = tk.Label(window, text='Oswald Factor:')
label32.grid(row = 17, column = 4, padx = (100, 0), pady = 1)
label33 = tk.Label(window, text='Propulsive Efficiency:')
label33.grid(row = 18, column = 4, padx = (100, 0), pady = 1)
label34 = tk.Label(window, text='Wetted Surface Area:')
label34.grid(row = 19, column = 4, padx = (100, 0), pady = 1)
label35 = tk.Label(window, text='Skin Friction Coefficient:')
label35.grid(row = 20, column = 4, padx = (100, 0), pady = 1)

# the entry boxes for the "baseline" parameters on the initial window
par1bl = tk.Entry(window, width = 5)
par1bl.grid(row = 1, column = 1, padx = (0, 5), pady = 1)
par2bl = tk.Entry(window, width = 5)
par2bl.grid(row = 2, column = 1, padx = (0, 5), pady = 1)
par3bl = tk.Entry(window, width = 5)
par3bl.grid(row = 3, column = 1, padx = (0, 5), pady = 1)
par4bl = tk.Entry(window, width = 5)
par4bl.grid(row = 4, column = 1, padx = (0, 5), pady = 1)
par5bl = tk.Entry(window, width = 5)
par5bl.grid(row = 5, column = 1, padx = (0, 5), pady = 1)
par6bl = tk.Entry(window, width = 5)
par6bl.grid(row = 6, column = 1, padx = (0, 5), pady = 1)
par7bl = tk.Entry(window, width = 5)
par7bl.grid(row = 7, column = 1, padx = (0, 5), pady = 1)
par8bl = tk.Entry(window, width = 5)
par8bl.grid(row = 8, column = 1, padx = (0, 5), pady = 1)
par9bl = tk.Entry(window, width = 5)
par9bl.grid(row = 9, column = 1, padx = (0, 5), pady = 1)
par10bl = tk.Entry(window, width = 5)
par10bl.grid(row = 10, column = 1, padx = (0, 5), pady = 1)
par11bl = tk.Entry(window, width = 5)
par11bl.grid(row = 11, column = 1, padx = (0, 5), pady = 1)
par12bl = tk.Entry(window, width = 5)
par12bl.grid(row = 12, column = 1, padx = (0,5), pady = 1)
par13bl = tk.Entry(window, width = 5)
par13bl.grid(row = 13, column = 1, padx = (0, 5), pady = 1)
par14bl = tk.Entry(window, width = 5)
par14bl.grid(row = 14, column = 1, padx = (0, 5), pady = 1)
par15bl = tk.Entry(window, width = 5)
par15bl.grid(row = 15, column = 1, padx = (0, 5), pady = 1)
par16bl = tk.Entry(window, width = 5)
par16bl.grid(row = 16, column = 1, padx = (0, 5), pady = 1)
par17bl = tk.Entry(window, width = 5)
par17bl.grid(row = 17, column = 1, padx = (0, 5), pady = 1)
par18bl = tk.Entry(window, width = 5)
par18bl.grid(row = 18, column = 1, padx = (0, 5), pady = 1)
par19bl = tk.Entry(window, width = 5)
par19bl.grid(row = 19, column = 1, padx = (0, 5), pady = 1)
par20bl = tk.Entry(window, width = 5)
par20bl.grid(row = 20, column = 1, padx = (0, 5), pady = 1)
par21bl = tk.Entry(window, width = 5)
par21bl.grid(row = 21, column = 1, padx = (0, 5), pady = 1)
par22bl = tk.Entry(window, width = 5)
par22bl.grid(row = 22, column = 1, padx = (0, 5), pady = 1)

par23bl = tk.Entry(window, width = 5)
par23bl.grid(row = 6, column = 5, padx = (0, 5), pady = 1)
par24bl = tk.Entry(window, width = 5)
par24bl.grid(row = 7, column = 5, padx = (0, 5), pady = 1)
par25bl = tk.Entry(window, width = 5)
par25bl.grid(row = 8, column = 5, padx = (0, 5), pady = 1)
par26bl = tk.Entry(window, width = 5)
par26bl.grid(row = 15, column = 5, padx = (0, 5), pady = 1)
par27bl = tk.Entry(window, width = 5)
par27bl.grid(row = 16, column = 5, padx = (0, 5), pady = 1)
par28bl = tk.Entry(window, width = 5)
par28bl.grid(row = 17, column = 5, padx = (0, 5), pady = 1)
par29bl = tk.Entry(window, width = 5)
par29bl.grid(row = 18, column = 5, padx = (0, 5), pady = 1)
par30bl = tk.Entry(window, width = 5)
par30bl.grid(row = 19, column = 5, padx = (0, 5), pady = 1)
par31bl = tk.Entry(window, width = 5)
par31bl.grid(row = 20, column = 5, padx = (0, 5), pady = 1)

# the entry boxes for the "objective" parameters on the initial window
par1obj = tk.Entry(window, width = 5)
par1obj.grid(row = 1, column = 2, padx = (0, 5), pady = 1)
par2obj = tk.Entry(window, width = 5)
par2obj.grid(row = 2, column = 2, padx = (0, 5), pady = 1)
par3obj = tk.Entry(window, width = 5)
par3obj.grid(row = 3, column = 2, padx = (0, 5), pady = 1)
par4obj = tk.Entry(window, width = 5)
par4obj.grid(row = 4, column = 2, padx = (0, 5), pady = 1)
par5obj = tk.Entry(window, width = 5)
par5obj.grid(row = 5, column = 2, padx = (0, 5), pady = 1)
par6obj = tk.Entry(window, width = 5)
par6obj.grid(row = 6, column = 2, padx = (0, 5), pady = 1)
par7obj = tk.Entry(window, width = 5)
par7obj.grid(row = 7, column = 2, padx = (0, 5), pady = 1)
par8obj = tk.Entry(window, width = 5)
par8obj.grid(row = 8, column = 2, padx = (0, 5), pady = 1)
par9obj = tk.Entry(window, width = 5)
par9obj.grid(row = 9, column = 2, padx = (0, 5), pady = 1)
par10obj = tk.Entry(window, width = 5)
par10obj.grid(row = 10, column = 2, padx = (0, 5), pady = 1)
par11obj = tk.Entry(window, width = 5)
par11obj.grid(row = 11, column = 2, padx = (0, 5), pady = 1)
par12obj = tk.Entry(window, width = 5)
par12obj.grid(row = 12, column = 2, padx = (0, 5), pady = 1)
par13obj = tk.Entry(window, width = 5)
par13obj.grid(row = 13, column = 2, padx = (0, 5), pady = 1)
par14obj = tk.Entry(window, width = 5)
par14obj.grid(row = 14, column = 2, padx = (0, 5), pady = 1)
par15obj = tk.Entry(window, width = 5)
par15obj.grid(row = 15, column = 2, padx = (0, 5), pady = 1)
par16obj = tk.Entry(window, width = 5)
par16obj.grid(row = 16, column = 2, padx = (0, 5), pady = 1)
par17obj = tk.Entry(window, width = 5)
par17obj.grid(row = 17, column = 2, padx = (0, 5), pady = 1)
par18obj = tk.Entry(window, width = 5)
par18obj.grid(row = 18, column = 2, padx = (0, 5), pady = 1)
par19obj = tk.Entry(window, width = 5)
par19obj.grid(row = 19, column = 2, padx = (0, 5), pady = 1)
par20obj = tk.Entry(window, width = 5)
par20obj.grid(row = 20, column = 2, padx = (0, 5), pady = 1)
par21obj = tk.Entry(window, width = 5)
par21obj.grid(row = 21, column = 2, padx = (0, 5), pady = 1)
par22obj = tk.Entry(window, width = 5)
par22obj.grid(row = 22, column = 2, padx = (0, 5), pady = 1)

par23obj = tk.Entry(window, width = 5)
par23obj.grid(row = 6, column = 6, pady = 1)
par24obj = tk.Entry(window, width = 5)
par24obj.grid(row = 7, column = 6, pady = 1)
par25obj = tk.Entry(window, width = 5)
par25obj.grid(row = 8, column = 6, pady = 1)
par26obj = tk.Entry(window, width = 5)
par26obj.grid(row = 15, column = 6, pady = 1)
par27obj = tk.Entry(window, width = 5)
par27obj.grid(row = 16, column = 6, pady = 1)
par28obj = tk.Entry(window, width = 5)
par28obj.grid(row = 17, column = 6, pady = 1)
par29obj = tk.Entry(window, width = 5)
par29obj.grid(row = 18, column = 6, pady = 1)
par30obj = tk.Entry(window, width = 5)
par30obj.grid(row = 19, column = 6, pady = 1)
par31obj = tk.Entry(window, width = 5)
par31obj.grid(row = 20, column = 6, pady = 1)

# Output labels and entry boxes
wingless_Bl_Entry = tk.Label(window, text='Baseline')
wingless_Bl_Entry.grid(row = 0, column = 9, pady = 1)
wingless_Obj_Entry = tk.Label(window, text='Objective')
wingless_Obj_Entry.grid(row = 0, column = 10, pady = 1)
winged_Bl_Entry = tk.Label(window, text='Baseline')
winged_Bl_Entry.grid(row = 14, column = 9, pady = 1)
winged_Obj_Entry = tk.Label(window, text='Objective')
winged_Obj_Entry.grid(row = 14, column = 10, pady = 1)

winglessResultbl_Entry1 = tk.Label(window, text='Hover Energy (Wh):')
winglessResultbl_Entry1.grid(row = 1, column = 8, padx = (50, 0), pady = 1)
winglessResultbl_Entry2 = tk.Label(window, text='Climb Energy (Wh):')
winglessResultbl_Entry2.grid(row = 2, column = 8, padx = (50, 0), pady = 1)
winglessResultbl_Entry3 = tk.Label(window, text='Cruise Energy (Wh):')
winglessResultbl_Entry3.grid(row = 3, column = 8, padx = (50, 0), pady = 1)
winglessResultbl_Entry4 = tk.Label(window, text='Descend Energy (Wh):')
winglessResultbl_Entry4.grid(row = 4, column = 8, padx = (50, 0), pady = 1)
winglessResultbl_Entry5 = tk.Label(window, text='Reserve Energy (Wh):')
winglessResultbl_Entry5.grid(row = 5, column = 8, padx = (50, 0), pady = 1)
winglessResultbl_Entry6 = tk.Label(window, text='Base Energy (Wh):')
winglessResultbl_Entry6.grid(row = 6, column = 8, padx = (50, 0), pady = 1)
winglessResultbl_Entry7 = tk.Label(window, text='Required Energy Density (Wh/kg):')
winglessResultbl_Entry7.grid(row = 7, column = 8, padx = (50, 0), pady = 1)
winglessResultbl_Entry8 = tk.Label(window, text='Required Power Density (W/kg):')
winglessResultbl_Entry8.grid(row = 8, column = 8, padx = (50, 0), pady = 1)
wingedResultbl_Entry1 = tk.Label(window, text='Hover Energy (Wh):')
wingedResultbl_Entry1.grid(row = 15, column = 8, padx = (50, 0), pady = 1)
wingedResultbl_Entry2 = tk.Label(window, text='Climb Energy (Wh):')
wingedResultbl_Entry2.grid(row = 16, column = 8, padx = (50, 0), pady = 1)
wingedResultbl_Entry3 = tk.Label(window, text='Cruise Energy (Wh):')
wingedResultbl_Entry3.grid(row = 17, column = 8, padx = (50, 0), pady = 1)
wingedResultbl_Entry4 = tk.Label(window, text='Descend Energy (Wh):')
wingedResultbl_Entry4.grid(row = 18, column = 8, padx = (50, 0), pady = 1)
wingedResultbl_Entry5 = tk.Label(window, text='Reserve Energy (Wh):')
wingedResultbl_Entry5.grid(row = 19, column = 8, padx = (50, 0), pady = 1)
wingedResultbl_Entry6 = tk.Label(window, text='Base Energy (Wh):')
wingedResultbl_Entry6.grid(row = 20, column = 8, padx = (50, 0), pady = 1)
wingedResultbl_Entry7 = tk.Label(window, text='Required Energy Density (Wh/kg):')
wingedResultbl_Entry7.grid(row = 21, column = 8, padx = (50, 0), pady = 1)
wingedResultbl_Entry8 = tk.Label(window, text='Required Power Density (W/kg):')
wingedResultbl_Entry8.grid(row = 22, column = 8, padx = (50, 0), pady = 1)

# Result Labels
winglessResultbl_label1 = tk.Label(window, text='')
winglessResultbl_label2 = tk.Label(window, text='')
winglessResultbl_label3 = tk.Label(window, text='')
winglessResultbl_label4 = tk.Label(window, text='')
winglessResultbl_label5 = tk.Label(window, text='')
winglessResultbl_label6 = tk.Label(window, text='')
winglessResultbl_label7 = tk.Label(window, text='')
winglessResultbl_label8 = tk.Label(window, text='')
winglessResultObj_label1 = tk.Label(window, text='')
winglessResultObj_label2 = tk.Label(window, text='')
winglessResultObj_label3 = tk.Label(window, text='')
winglessResultObj_label4 = tk.Label(window, text='')
winglessResultObj_label5 = tk.Label(window, text='')
winglessResultObj_label6 = tk.Label(window, text='')
winglessResultObj_label7 = tk.Label(window, text='')
winglessResultObj_label8 = tk.Label(window, text='')

wingedResultBl_label1 = tk.Label(window, text='')
wingedResultBl_label2 = tk.Label(window, text='')
wingedResultBl_label3 = tk.Label(window, text='')
wingedResultBl_label4 = tk.Label(window, text='')
wingedResultBl_label5 = tk.Label(window, text='')
wingedResultBl_label6 = tk.Label(window, text='')
wingedResultBl_label7 = tk.Label(window, text='')
wingedResultBl_label8 = tk.Label(window, text='')
wingedResultObj_label1 = tk.Label(window, text='')
wingedResultObj_label2 = tk.Label(window, text='')
wingedResultObj_label3 = tk.Label(window, text='')
wingedResultObj_label4 = tk.Label(window, text='')
wingedResultObj_label5 = tk.Label(window, text='')
wingedResultObj_label6 = tk.Label(window, text='')
wingedResultObj_label7 = tk.Label(window, text='')
wingedResultObj_label8 = tk.Label(window, text='')

def printwingless():
   E_base, P_clb, P_cru, P_hov, P_des, E_dens, E_hov, P_dens, E_res, E_cru, E_clb, E_des, E_total, E_clb = wingless()
   
   # print results for objective/baseline
   winglessResultbl_label1.config(text='{0:.1f}'.format(E_hov[0]))
   winglessResultbl_label1.grid(row = 1, column = 9)
   winglessResultbl_label2.config(text='{0:.1f}'.format(E_clb[0]))
   winglessResultbl_label2.grid(row = 2, column = 9)
   winglessResultbl_label3.config(text='{0:.1f}'.format(E_cru[0]))
   winglessResultbl_label3.grid(row = 3, column = 9)
   winglessResultbl_label4.config(text='{0:.1f}'.format(E_des[0]))
   winglessResultbl_label4.grid(row = 4, column = 9)
   winglessResultbl_label5.config(text='{0:.1f}'.format(E_res[0]))
   winglessResultbl_label5.grid(row = 5, column = 9)
   winglessResultbl_label6.config(text='{0:.1f}'.format(E_base[0]))
   winglessResultbl_label6.grid(row = 6, column = 9)
   winglessResultbl_label7.config(text='{0:.1f}'.format(E_dens[0]))
   winglessResultbl_label7.grid(row = 7, column = 9)
   winglessResultbl_label8.config(text='{0:.1f}'.format(P_dens[0]))
   winglessResultbl_label8.grid(row = 8, column = 9)

   winglessResultObj_label1.config(text='{0:.1f}'.format(E_hov[1]))
   winglessResultObj_label1.grid(row = 1, column = 10)
   winglessResultObj_label2.config(text='{0:.1f}'.format(E_clb[1]))
   winglessResultObj_label2.grid(row = 2, column = 10)
   winglessResultObj_label3.config(text='{0:.1f}'.format(E_cru[1]))
   winglessResultObj_label3.grid(row = 3, column = 10)
   winglessResultObj_label4.config(text='{0:.1f}'.format(E_des[1]))
   winglessResultObj_label4.grid(row = 4, column = 10)
   winglessResultObj_label5.config(text='{0:.1f}'.format(E_res[1]))
   winglessResultObj_label5.grid(row = 5, column = 10)
   winglessResultObj_label6.config(text='{0:.1f}'.format(E_base[1]))
   winglessResultObj_label6.grid(row = 6, column = 10)
   winglessResultObj_label7.config(text='{0:.1f}'.format(E_dens[1]))
   winglessResultObj_label7.grid(row = 7, column = 10)
   winglessResultObj_label8.config(text='{0:.1f}'.format(P_dens[1]))
   winglessResultObj_label8.grid(row = 8, column = 10)

   # pie charts for wingless
   fig2 = plt.figure(figsize=(1.55, .85), dpi=150)
   base_wingless = [E_hov[0], E_clb[0], E_cru[0], E_des[0], E_res[0], E_base[0]]
   wingless_labels = ["Energy to hover", "Energy to climb", "Energy to cruise", "Energy to descend", "Reserve Energy", "Base Electrical"]

   plt.pie(base_wingless, 
      startangle=0, 
      radius=1.2, 
      #explode=(0.0, 0.3, 0.2, 0.1, 0.0, 0.6), 
      autopct='%1.2f%%', pctdistance=1.3, 
      textprops={'size': 5.5}, 
      counterclock = False)
   plt.legend(wingless_labels, loc ="lower left", bbox_to_anchor=(-.7, -.15), prop={'size': 3.55})
   pie1 = FigureCanvasTkAgg(fig2, window)
   pie1.get_tk_widget().place(x=975 , y=20)
   pie1Label = tk.Label(window, text='Wingless: Baseline')
   pie1Label.place(x=975 , y=0)
   
   
   fig3 = plt.figure(figsize=(1.55, .85), dpi=150)
   base_wingless = [E_hov[1], E_clb[1], E_cru[1], E_des[1], E_res[1], E_base[1]]
   plt.pie(base_wingless, 
      startangle=0, 
      radius=1.2, 
      #explode=(0.0, 0.3, 0.2, 0.1, 0.0, 0.6), 
      autopct='%1.2f%%', pctdistance=1.25, 
      textprops={'size': 5.5}, 
      counterclock = False)
   plt.legend(wingless_labels, loc ="lower left", bbox_to_anchor=(-.7, -.15), prop={'size': 3.55})
   pie2 = FigureCanvasTkAgg(fig3, window)
   pie2.get_tk_widget().place(x=975 , y=200)

   pie2Label = tk.Label(window, text='Wingless: Objective')
   pie2Label.place(x=975 , y=180)



   
def printpoweredlift():
   w_P_hov, w_P_cru, w_P_clb, w_P_des, w_E_hov, w_E_clb, w_E_cru, w_E_des, w_E_res, w_E_base, w_E_dens, w_P_dens = winged()
   wingedResultBl_label1.config(text='{0:.1f}'.format(w_E_hov[0]))
   wingedResultBl_label1.grid(row = 15, column = 9)
   wingedResultBl_label2.config(text='{0:.1f}'.format(w_E_clb[0]))
   wingedResultBl_label2.grid(row = 16, column = 9)
   wingedResultBl_label3.config(text='{0:.1f}'.format(w_E_cru[0]))
   wingedResultBl_label3.grid(row = 17, column = 9)
   wingedResultBl_label4.config(text='{0:.1f}'.format(w_E_des[0]))
   wingedResultBl_label4.grid(row = 18, column = 9)
   wingedResultBl_label5.config(text='{0:.1f}'.format(w_E_res[0]))
   wingedResultBl_label5.grid(row = 19, column = 9)
   wingedResultBl_label6.config(text='{0:.1f}'.format(w_E_base[0]))
   wingedResultBl_label6.grid(row = 20, column = 9)
   wingedResultBl_label7.config(text='{0:.1f}'.format(w_E_dens[0]))
   wingedResultBl_label7.grid(row = 21, column = 9)
   wingedResultBl_label8.config(text='{0:.1f}'.format(w_P_dens[0]))
   wingedResultBl_label8.grid(row = 22, column = 9)

   wingedResultObj_label1.config(text='{0:.1f}'.format(w_E_hov[1]))
   wingedResultObj_label1.grid(row = 15, column = 10)
   wingedResultObj_label2.config(text='{0:.1f}'.format(w_E_clb[1]))
   wingedResultObj_label2.grid(row = 16, column = 10)
   wingedResultObj_label3.config(text='{0:.1f}'.format(w_E_cru[1]))
   wingedResultObj_label3.grid(row = 17, column = 10)
   wingedResultObj_label4.config(text='{0:.1f}'.format(w_E_des[1]))
   wingedResultObj_label4.grid(row = 18, column = 10)
   wingedResultObj_label5.config(text='{0:.1f}'.format(w_E_res[1]))
   wingedResultObj_label5.grid(row = 19, column = 10)
   wingedResultObj_label6.config(text='{0:.1f}'.format(w_E_base[1]))
   wingedResultObj_label6.grid(row = 20, column = 10)
   wingedResultObj_label7.config(text='{0:.1f}'.format(w_E_dens[1]))
   wingedResultObj_label7.grid(row = 21, column = 10)
   wingedResultObj_label8.config(text='{0:.1f}'.format(w_P_dens[1]))
   wingedResultObj_label8.grid(row = 22, column = 10)

   # pie charts for winged
   fig4 = plt.figure(figsize=(1.55, .85), dpi=150)
   base_powered = [w_E_hov[0], w_E_clb[0], w_E_cru[0], w_E_des[0], w_E_res[0], w_E_base[0]]
   powered_labels = ["Energy to hover", "Energy to climb", "Energy to cruise", "Energy to descend", "Reserve Energy", "Base Electrical"]
   plt.pie(base_powered, 
      startangle=0, 
      radius=1.2, 
      #explode=(0.0, 0.3, 0.2, 0.1, 0.0, 0.6), 
      autopct='%1.2f%%', pctdistance=1.3, 
      textprops={'size': 5.5}, 
      counterclock = False)
   plt.legend(powered_labels, loc ="lower left", bbox_to_anchor=(-.7, -.15), prop={'size': 3.55})
   pie3 = FigureCanvasTkAgg(fig4, window)
   pie3.get_tk_widget().place(x=975 , y=340)

   pie3Label = tk.Label(window, text='Winged: Baseline')
   pie3Label.place(x=975 , y=330)

   fig5 = plt.figure(figsize=(1.55, .85), dpi=150)
   base_powered = [w_E_hov[1], w_E_clb[1], w_E_cru[1], w_E_des[1], w_E_res[1], w_E_base[1]]
   plt.pie(base_powered, 
      startangle=0, 
      radius=1.2, 
      #explode=(0.0, 0.3, 0.2, 0.1, 0.0, 0.6), 
      autopct='%1.2f%%', pctdistance=1.3, 
      textprops={'size': 5.5}, 
      counterclock = False)
   plt.legend(powered_labels, loc ="lower left", bbox_to_anchor=(-.7, -.15), prop={'size': 3.55})
   pie4 = FigureCanvasTkAgg(fig5, window)
   pie4.get_tk_widget().place(x=975 , y=510)

   pie3Label = tk.Label(window, text='Winged: Objective')
   pie3Label.place(x=975 , y=500)

# Button For Run Wingless
wingless_button = tk.Button(window, text="Run Wingless Flight", command=printwingless)
wingless_button.grid(row = 5, column = 4, padx = (100, 0))

# Button For Run Wingled
winged_button = tk.Button(window, text = "Run Powered Lift", command=printpoweredlift)
winged_button.grid(row = 14, column = 4, padx = (100, 0))

def on_closing():
   sys.exit(0)
   
window.protocol("WM_DELETE_WINDOW", on_closing)

window.mainloop()
