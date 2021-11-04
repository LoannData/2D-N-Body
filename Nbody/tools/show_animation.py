#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Sun Feb 18 13:39:23 2018

@author: Loann Brahimi
"""
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import freader as f 
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.colors import cnames

main_parameters = "../parameters/main_parameters.txt" 
visualization   = "../parameters/visualisation.txt"
structure       = "../parameters/structure.txt"

dimension = int(f.search(structure,"dimension"))
num_bodies = int(f.search(main_parameters,"num_bodies"))
visualize = f.search(visualization, "visualize")
background_color = f.search(visualization, "background_color")
plot_axis	= f.search(visualization, "plot_axis")
body_point_style	= f.search(visualization, "body_point_style")
body_line	= f.search(visualization, "body_line")
body_line_style = f.search(visualization, "body_line_style")	
moving_camera = f.search(visualization, "moving_camera")
cam_pos_altitude	= float(f.search(visualization, "cam_pos_altitude"))
cam_pos_azimuth = float(f.search(visualization, "cam_pos_azimuth")) 
time_step_per_frame = int(f.search(visualization, "time_step_per_frame"))
xc = float(f.search(visualization, "xc"))
yc = float(f.search(visualization, "yc"))
zc = float(f.search(visualization, "zc"))
xw = float(f.search(visualization, "xw"))
yw = float(f.search(visualization, "yw"))
zw = float(f.search(visualization, "zw"))
frame_interval = int(f.search(visualization, "frame_interval"))
save_animation = f.search(visualization, "save_animation")
altitude_rotation_velocity = 0.
azimuth_rotation_velocity = 0.
if (moving_camera == "on") : 
    altitude_rotation_velocity = float(f.search(visualization, "altitude_rotation_velocity"))
    azimuth_rotation_velocity  = float(f.search(visualization, "azimuth_rotation_velocity"))
if (save_animation == "on") : 
    fps = int(f.search(visualization, "fps"))
    



if (dimension == 3) : 

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
    del data,  data_file_position_x, data_file_position_y, data_file_position_z
    trajectory = []
    for ii in range(Np) : 
        subtraj = [[],[],[]]
        for jj in range(len(time)) : 
            subtraj[0].append(position_x[jj][ii])
            subtraj[1].append(position_y[jj][ii])
            subtraj[2].append(position_z[jj][ii])
        trajectory.append(subtraj)
        
    x_t = np.empty((Np, len(time) , 3))
    for ii in range(len(time)) : 
        for jj in range(Np) : 
            x_t[jj][ii][0] = position_x[ii][jj]
            x_t[jj][ii][1] = position_y[ii][jj]
            x_t[jj][ii][2] = position_z[ii][jj]
        
    # Set up figure & 3D axis for animation
    fig = plt.figure(facecolor=background_color)
    ax = fig.add_axes([0, 0, 1, 1], projection='3d')
    ax.axis(plot_axis)
#    ax.style.use('dark_background')
    # choose a different color for each trajectory
    colors = plt.cm.jet(np.linspace(0, 1, Np))
    # set up trajectory lines
    lines = sum([ax.plot([], [], [], body_line_style, c=c) for c in colors], [])
    # set up points
    #pts = sum([ax.plot([], [], [], '.', c=c) for c in colors], [])
    pts = sum([ax.plot([], [], [], '.', c="black") for c in colors], [])
    # set up lines which create the stick figures
    stick_lines = sum([ax.plot([], [], [], '-', c=c) for c in colors], [])
    # prepare the axes limits
    ax.set_xlim(xc - xw/2., xc + xw/2.)
    ax.set_ylim(yc - yw/2., yc + yw/2.) # note usage of z coordinate
    ax.set_zlim(zc - zw/2., zc + zw/2.) # note usage of y coordinate
    # set point-of-view: specified by (altitude degrees, azimuth degrees)
    ax.view_init(cam_pos_altitude, cam_pos_azimuth)
    # initialization function: plot the background of each frame
    def init():
        for line, pt, stick_line in zip(lines, pts, stick_lines):
            # trajectory lines
            if (body_line == "on") : 
                line.set_data([], [])
                line.set_3d_properties([])
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
        i = (time_step_per_frame * i) % x_t.shape[1]
        for line, pt, stick_line, xi in zip(lines, pts, stick_lines, x_t):
            x, z, y = xi[:i].T # note ordering of points to line up with true exogenous registration (x,z,y)
            # trajectory lines
            if (body_line == "on") : 
                line.set_data(x, y)
                line.set_3d_properties(z)
            # points
            pt.set_data(x[-1:], y[-1:])
            pt.set_3d_properties(z[-1:])
            # stick lines
            ##stick_line.set_data(x,z)
            ##stick_line.set_3d_properties(y)
        ax.view_init(cam_pos_altitude + i*altitude_rotation_velocity, cam_pos_azimuth + i*azimuth_rotation_velocity)
        fig.canvas.draw()
        return pts  + lines + stick_lines
    
    # instantiate the animator.
    anim = animation.FuncAnimation(fig, animate, init_func=init, frames=int(len(time)/time_step_per_frame+1), interval=1, blit=False)
    # Save as mp4. This requires mplayer or ffmpeg to be installed
    if (save_animation == "on"): 
        anim.save('lorentz_attractor.mp4', fps=fps, extra_args=['-vcodec', 'libx264'])
    plt.show()       
        
        
        