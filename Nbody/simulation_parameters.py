import numpy as np 

# Structure of the simulation 
myfile0_title = "./parameters/structure.txt"
myfile0 = open(myfile0_title,"w")
dimension = 3                                                                                   # (1, 2, 3) : Dimensions accepted for the simulation 
myfile0.write("dimension"+"\t"+str(dimension)+"\n")
myfile0.close()
# ----------------------------------------------------------------

# Outputs 
myfile1_title = "./parameters/outputs.txt"
myfile1 = open(myfile1_title, "w")
output_name_prefix = "body"                                                                     # example : body_....dat 
output_name_postfix = ""                                                                        # example : body_450_heavy.dat 
output_name_ext = "dat"                                                                         # txt, dat, out ... 
output_type = "one_by_body"                                                                     # Output types  
number_outputs = 5000                                                                         # Number of time output of the simulation
myfile1.write("output_name_prefix"+"\t"+str(output_name_prefix)+"\n")
myfile1.write("output_name_postfix"+"\t"+str(output_name_postfix)+"\n")
myfile1.write("output_name_ext"+"\t"+str(output_name_ext)+"\n")
myfile1.write("output_type"+"\t"+str(output_type)+"\n")
myfile1.write("number_outputs"+"\t"+str(number_outputs)+"\n")
myfile1.close()
# ----------------------------------------------------------------

# Main parameters
myfile2_title = "./parameters/main_parameters.txt"
myfile2 = open(myfile2_title,"w")

num_bodies = 100                                                                             # (1, ...) : Number of bodies in the simulation 
body_mass_distribution = "no"                                                                   # If you want a specific mass distribution 
normalized_mass = 1                                                                             # Normalized mass value of bodies 
body_radius_distribution = "no"                                                                 # If you want a specific radius distribution 
normalized_radius = 1                                                                           # Normalized radius value of bodies 
body_position_distribution = "uniform_rectangle"                                                # Initial position distribution
body_velocity_distribution = "uniform_rectangle"                                                # Initial velocity distribution
softening = 1e-4                                                                                # Parameter allowing to avoid numerical divergences 
collisions = "no"                                                                               # Solid collisions between bodies 
viscosity = "no"                                                                                # Presence of a gas 
time_initial = 0.                                                                               # Time at which the simulation begin 
time_final = 1.0                                                                                # Time at which the simulation end 
variable_step = "no"
step_min = 1e-4                                                                                 # Example of step (min value for variable step, fixed value for fixed step)

if (step_min*number_outputs >= 1.) : print ("Error ! The time step is too high compared to the number of time outputs")


myfile2.write("num_bodies"+"\t"+str(num_bodies)+"\n")
myfile2.write("body_mass_distribution"+"\t"+str(body_mass_distribution)+"\n")
myfile2.write("normalized_mass"+"\t"+str(normalized_mass)+"\n")
myfile2.write("body_radius_distribution"+"\t"+str(body_radius_distribution)+"\n")
myfile2.write("normalized_radius"+"\t"+str(normalized_radius)+"\n")
myfile2.write("body_position_distribution"+"\t"+str(body_position_distribution)+"\n")
myfile2.write("body_velocity_distribution"+"\t"+str(body_velocity_distribution)+"\n")
myfile2.write("softening"+"\t"+str(softening)+"\n")
myfile2.write("collisions"+"\t"+str(collisions)+"\n")
myfile2.write("viscosity"+"\t"+str(viscosity)+"\n")
myfile2.write("time_initial"+"\t"+str(time_initial)+"\n")
myfile2.write("time_final"+"\t"+str(time_final)+"\n")
myfile2.write("variable_step"+"\t"+str(variable_step)+"\n")
myfile2.write("step_min"+"\t"+str(step_min)+"\n")


if (body_mass_distribution == "yes") : 
    mass_distribution = "test_distribution"                                                     # Example of mass distribution 
    myfile2.write("mass_distribution"+"\t"+str(mass_distribution)+"\n")
if (body_radius_distribution == "yes") : 
    radius_distribution = "test_distribution"                                                   # Example of radius distribution 
    myfile2.write("radius_distribution"+"\t"+str(radius_distribution)+"\n")
if (collisions == "yes") : 
    collision_consequence = "fusion"                                                            # Example of consequence of a collision between two bodies
    myfile2.write("collision_consequence"+"\t"+str(collision_consequence)+"\n") 
if (viscosity == "yes") : 
    viscosity_law = "exmaple"                                                                   # Example of law of viscosity 
    myfile2.write("viscosity_law"+"\t"+str(viscosity_law)+"\n")
if (variable_step == "yes") : 
    step_rule = "exmaple"                                                                       # Example of rule for a variable step
    myfile2.write("step_rule"+"\t"+str(step_rule)+"\n")

myfile2.close()
# ----------------------------------------------------------------

# Optimization and solving parameters 
myfile3_title = "./parameters/opt_solve.txt"
myfile3 = open(myfile3_title,"w")
barnes_hut = "no" # Barnes-hut optimization method
myfile3.write("barnes_hut"+"\t"+str(barnes_hut)+"\n")
sph = "no" # Smooth-particle-hydrodynamics grid 
myfile3.write("sph"+"\t"+str(sph)+"\n")
solver = "verlet" # Brut-force solver
myfile3.write("solver"+"\t"+str(solver)+"\n")
myfile3.close()
# ----------------------------------------------------------------

# Visualization parameters 
myfile4_title="./parameters/visualisation.txt"
myfile4 = open(myfile4_title,"w")
visualize = "on" # Do you want to launch vizualisator immediately ? 
myfile4.write("visualize"+"\t"+str(visualize)+"\n")
background_color = "black" # Color of the backgound 
myfile4.write("background_color"+"\t"+str(background_color)+"\n")
plot_axis = "off"
myfile4.write("plot_axis"+"\t"+str(plot_axis)+"\n")
body_point_style = "." #('.',',','*'...)
myfile4.write("body_point_style"+"\t"+str(body_point_style)+"\n")
body_line = "off"
myfile4.write("body_line"+"\t"+str(body_line)+"\n")
body_line_style = '-'
myfile4.write("body_line_style"+"\t"+str(body_line_style)+"\n")
moving_camera = "off" # Only for 3D visualization 
myfile4.write("moving_camera"+"\t"+str(moving_camera)+"\n")
cam_pos_altitude = 30 # Camera position altidue in degrees 
myfile4.write("cam_pos_altitude"+"\t"+str(cam_pos_altitude)+"\n")
cam_pos_azimuth  = 30 # Camera position azimuth in degrees
myfile4.write("cam_pos_azimuth"+"\t"+str(cam_pos_azimuth)+"\n")
time_step_per_frame = 40 # Number of time step by frame 
myfile4.write("time_step_per_frame"+"\t"+str(time_step_per_frame)+"\n")
if (moving_camera == "on") : 
    altitude_rotation_velocity = 0.0050
    azimuth_rotation_velocity  = 0.0050 
    myfile4.write("altitude_rotation_velocity"+"\t"+str(altitude_rotation_velocity)+"\n")
    myfile4.write("azimuth_rotation_velocity"+"\t"+str(azimuth_rotation_velocity)+"\n")
xc = 0 # X center position
xw = 2 # X width of the box ... 
yc = 0
yw = 2
zc = 0
zw = 2
myfile4.write("xc"+"\t"+str(xc)+"\n")
myfile4.write("yc"+"\t"+str(yc)+"\n")
myfile4.write("zc"+"\t"+str(zc)+"\n")
myfile4.write("xw"+"\t"+str(xw)+"\n")
myfile4.write("yw"+"\t"+str(yw)+"\n")
myfile4.write("zw"+"\t"+str(zw)+"\n")
frame_interval = 1 # Time between two frames (in ms)
myfile4.write("frame_interval"+"\t"+str(frame_interval)+"\n")
save_animation = "off" 
myfile4.write("save_animation"+"\t"+str(save_animation)+"\n")
if (save_animation == "on") : 
    fps = 25 
    myfile4.write("fps"+"\t"+str(fps)+"\n")
