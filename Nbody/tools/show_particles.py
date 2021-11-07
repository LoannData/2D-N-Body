#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Sun Feb 18 13:39:23 2018

@author: Loann Brahimi
"""
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation


data_file_position_x = open("../out/body_positions_x.dat","r").readlines()
data_file_position_y = open("../out/body_positions_y.dat","r").readlines()
data_file_position_z = open("../out/body_positions_z.dat","r").readlines()
len_file = len(data_file_position_x)

data = [np.empty(len_file), [], [], []]

for lines in range(len_file) : 
    data_file_position_x[lines] = data_file_position_x[lines].split("\t")
    data_file_position_y[lines] = data_file_position_y[lines].split("\t")
    data_file_position_z[lines] = data_file_position_z[lines].split("\t")
    
for lines in range(len_file) :
    for col in range(len(data_file_position_x[lines])-1) : 
        data_file_position_x[lines][col] = float(data_file_position_x[lines][col])
        data_file_position_y[lines][col] = float(data_file_position_y[lines][col])
        data_file_position_z[lines][col] = float(data_file_position_z[lines][col])
    del data_file_position_x[lines][0]
    del data_file_position_y[lines][0]
    del data_file_position_z[lines][0]
    del data_file_position_x[lines][len(data_file_position_x[lines])-1]
    del data_file_position_y[lines][len(data_file_position_y[lines])-1]
    del data_file_position_z[lines][len(data_file_position_z[lines])-1]
    data[0][lines] = float(data_file_position_x[lines][0])
    data[1].append(data_file_position_x[lines])
    data[2].append(data_file_position_y[lines])
    data[3].append(data_file_position_z[lines])

time       = data[0]
position_x = data[1]
position_y = data[2]  
position_z = data[3]  

Np         = len(position_x[0])
#position_z = np.zeros((10000, Np))
  
del data,  data_file_position_x, data_file_position_y, data_file_position_z

trajectory = []
for ii in range(Np) : 
    subtraj = [[],[],[]]
    for jj in range(len(time)) : 
        subtraj[0].append(position_x[jj][ii])
        subtraj[1].append(position_y[jj][ii])
        subtraj[2].append(position_z[jj][ii])
    trajectory.append(subtraj)



"""
Full animation of a walking event (note: a lot of missing data) 
"""
import numpy as np
import pandas as pd
import matplotlib
matplotlib.use('TkAgg') # Need to use in order to run on mac
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.colors import cnames
from matplotlib import animation


#===STICK-LINES========================================================================================
#xx = [x_t[1,:,0],x_t[2,:,0]]
#yy = [x_t[1,:,1],x_t[2,:,1]]
#zz = [x_t[1,:,2],x_t[2,:,2]] 
#======================================================================================================

x_t = np.empty((Np, len(time) , 3))
for ii in range(len(time)) : 
    for jj in range(Np) : 
        x_t[jj][ii][0] = position_x[ii][jj]
        x_t[jj][ii][1] = position_y[ii][jj]
        x_t[jj][ii][2] = position_z[ii][jj]

# Set up figure & 3D axis for animation
fig = plt.figure()
ax = fig.add_axes([0, 0, 1, 1], projection='3d')
ax.axis('off')

# choose a different color for each trajectory
colors = plt.cm.jet(np.linspace(0, 1, Np))
# set up trajectory lines
lines = sum([ax.plot([], [], [], '-', c=c) for c in colors], [])
# set up points
#pts = sum([ax.plot([], [], [], '.', c=c) for c in colors], [])
pts = sum([ax.plot([], [], [], '.', c="black") for c in colors], [])
# set up lines which create the stick figures
stick_lines = sum([ax.plot([], [], [], '-', c=c) for c in colors], [])

# prepare the axes limits
ax.set_xlim(-2, 2)
ax.set_ylim(-2, 2) # note usage of z coordinate
ax.set_zlim(-2, 2) # note usage of y coordinate

# set point-of-view: specified by (altitude degrees, azimuth degrees)
ax.view_init(30, 45)

# initialization function: plot the background of each frame
def init():
    for line, pt, stick_line in zip(lines, pts, stick_lines):
        # trajectory lines
        #line.set_data([], [])
        #line.set_3d_properties([])
        # points
        pt.set_data([], [])
        pt.set_3d_properties([])
        # stick lines
        ##stick_line.set_data([], [])
        ##stick_line.set_3d_properties([])
    return pts + lines + stick_lines

# animation function.  This will be called sequentially with the frame number
def animate(i):
    # we'll step two time-steps per frame.  This leads to nice results.
    i = (100 * i) % x_t.shape[1]

    for line, pt, stick_line, xi in zip(lines, pts, stick_lines, x_t):
        x, z, y = xi[:i].T # note ordering of points to line up with true exogenous registration (x,z,y)
        # trajectory lines
        #line.set_data(x,y)
        #line.set_3d_properties(z)
        # points
        pt.set_data(x[-1:], y[-1:])
        pt.set_3d_properties(z[-1:])
        # stick lines
        ##stick_line.set_data(x,z)
        ##stick_line.set_3d_properties(y)
    ax.view_init(30, 30)
#    ax.view_init(30, 30)    
    fig.canvas.draw()
    return pts  + lines + stick_lines

# instantiate the animator.
anim = animation.FuncAnimation(fig, animate, init_func=init, frames=1000, interval=1, blit=False)

# Save as mp4. This requires mplayer or ffmpeg to be installed
anim.save('lorentz_attractor.mp4', fps=15, extra_args=['-vcodec', 'libx264'])

plt.show()