#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Thu Oct 11 12:31:27 2018

@author: lbrahimi
"""

import numpy as np
import matplotlib.pyplot as plt



data_file_position_x = open("../out/body_positions_x.dat","r").readlines()
data_file_position_y = open("../out/body_positions_y.dat","r").readlines()
len_file = len(data_file_position_x)

data = [np.empty(len_file), [], []]

for lines in range(len_file) : 
    data_file_position_x[lines] = data_file_position_x[lines].split("\t")
    data_file_position_y[lines] = data_file_position_y[lines].split("\t")
    
for lines in range(len_file) :
    for col in range(len(data_file_position_x[lines])-1) : 
        data_file_position_x[lines][col] = float(data_file_position_x[lines][col])
        data_file_position_y[lines][col] = float(data_file_position_y[lines][col])
    del data_file_position_x[lines][0]
    del data_file_position_y[lines][0]
    del data_file_position_x[lines][len(data_file_position_x[lines])-1]
    del data_file_position_y[lines][len(data_file_position_y[lines])-1]
    data[0][lines] = float(data_file_position_x[lines][0])
    data[1].append(data_file_position_x[lines])
    data[2].append(data_file_position_y[lines])

time       = data[0]
position_x = data[1]
position_y = data[2]  
Np         = len(position_x[0])
  
del data,  data_file_position_x, data_file_position_y

trajectory = []
for ii in range(Np) : 
    subtraj = [[],[]]
    for jj in range(len(time)) : 
        subtraj[0].append(position_x[jj][ii])
        subtraj[1].append(position_y[jj][ii])
    trajectory.append(subtraj)


plt.figure()
for ii in range(Np) : 
    plt.plot(trajectory[ii][0], trajectory[ii][1])
plt.xlim(-5, 5)
plt.ylim(-5, 5)
plt.show()
