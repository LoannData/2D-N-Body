#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Mon Feb 19 17:46:07 2018

@author: Loann Brahimi
"""

import numpy as np
import matplotlib.pyplot as plt 
import freader as fr

dim = int(fr.search("../parameters/structure.txt","dimension"))
N   = int(fr.search("../parameters/main_parameters.txt", "num_bodies")) 
body_position_distribution = fr.search("../parameters/main_parameters.txt", "body_position_distribution")	
body_velocity_distribution = fr.search("../parameters/main_parameters.txt", "body_velocity_distribution")	
myfile_title = "../dist/"


#N = 50

#myfile_title = "../dist/"
ext = ".dat"
myfile_title += body_position_distribution
myfile_title += ext

myfile = open(myfile_title, "w")

rx = np.zeros(N)
ry = np.zeros(N)
rz = np.zeros(N)
vx = np.zeros(N)
vy = np.zeros(N)
vz = np.zeros(N)
for ii in range(N) : 
    if (body_position_distribution == "uniform_rectangle") : 
        rx[ii] = np.random.uniform(low=-1.0, high=1.0)
        ry[ii] = np.random.uniform(low=-1.0, high=1.0)
        rz[ii] = np.random.uniform(low=-1.0, high=1.0)
        
    if (body_velocity_distribution == "uniform_rectangle") : 
        vx[ii] = np.random.uniform(low=-1.0, high=1.0)
        vy[ii] = np.random.uniform(low=-1.0, high=1.0)
        vz[ii] = np.random.uniform(low=-1.0, high=1.0)




plt.figure()
plt.plot(rx, ry, '.')

plt.figure()
plt.plot(vx, vy, '.')



for ii in range(N) : 
    myfile.write(str(ii)+"\t"+str(rx[ii])+"\t"+str(ry[ii])+"\t"+str(rz[ii])+"\t"+str(vx[ii])+"\t"+str(vy[ii])+"\t"+str(vz[ii])+"\n")

myfile.close()
    
