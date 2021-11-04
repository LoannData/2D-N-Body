#include <iostream> //For console output/input
#include <fstream>  //Allows to read/write files 
#include <math.h>   //Basic mathematic functions 
#include <vector>   //For dynamic arrays 
#include <string>   //Operations on strings 
#include <tuple>
#include <cmath>
#include <sstream>
#include "./class/class_body.h"
#include "./class/freader.h"
using namespace std;



int main()
{
    // Simulation parameter files ----------------------------------------
    std::string structure  ;
    std::string main_param ;
    std::string opt_solve  ;
    std::string output     ; 
    std::string dir_param  = "../parameters/"; 
    std::string structure_  = "structure.txt";
    std::string main_param_ = "main_parameters.txt";
    std::string opt_solve_  = "opt_solve.txt";
    std::string output_    = "outputs.txt"; 
    structure.append(dir_param);
    main_param.append(dir_param);
    opt_solve.append(dir_param);
    output.append(dir_param); 
    structure.append(structure_);
    main_param.append(main_param_);
    opt_solve.append(opt_solve_);
    output.append(output_); 

    //from string to int : std::stoi(string) = int 
    int dim; // Dimension of our simulation
    std::string dimension = search(structure, "dimension");
    dim = stoi(dimension);


    int N;
    std::string Number = search(main_param, "num_bodies");
    N = std::stoi(Number);
    vector<body2d> objet2;
    vector<body3d> objet3;
    int id[N];

    float m; 
    std::string mass = search(main_param, "normalized_mass");
    m = std::stof(mass);

    double rx[N], ry[N], rz[N];
    double vx[N], vy[N], vz[N];


    std::string body_position_distribution = search(main_param, "body_position_distribution");
    std::string body_velocity_distribution = search(main_param, "body_velocity_distribution");
    ifstream distrib_file;
    std::string distrib_file_name = "../dist/";
    std::string ext = ".dat";
    distrib_file_name.append(body_position_distribution);
    distrib_file_name.append(ext);
    distrib_file.open(distrib_file_name);
    int j=0;
    while (!distrib_file.eof())
    {
        distrib_file >> id[j];
        distrib_file >> rx[j];
        if (dim > 1){distrib_file >> ry[j];}
        if (dim > 2){distrib_file >> rz[j];}
        distrib_file >> vx[j];
        if (dim > 1){distrib_file >> vy[j];}
        if (dim > 2){distrib_file >> vz[j];}
        j++;
    }

    for (int ii=0; ii<N; ii++)
    {
        body2d obj2;
        if (dim == 2)
        {
            obj2.edit_mass(m);
            obj2.edit_position(rx[ii], ry[ii]);
            obj2.edit_velocity(vx[ii], vy[ii]);
            obj2.edit_acceleration(0, 0);
            objet2.push_back(obj2);
        }

        body3d obj3;
        if (dim == 3)
        {
            obj3.edit_mass(m);
            obj3.edit_position(rx[ii], ry[ii], rz[ii]);
            obj3.edit_velocity(vx[ii], vy[ii], vz[ii]);
            obj3.edit_acceleration(0, 0, 0);
            objet3.push_back(obj3);
        }
    }

    ofstream position_x, position_y, position_z;
    ofstream velocity_x, velocity_y, velocity_z;
    ofstream acceleration_x, acceleration_y, acceleration_z;
    std::string name, name_pos, name_vel, name_acc, name1, name2, name3;
    std::string name_axe_x, name_axe_y, name_axe_z;
    std::string name1x, name1y, name1z, name2x, name2y, name2z, name3x, name3y, name3z;

    name1x = "";
    name2x = "";
    name3x = ""; 
    if (dim > 1)
    {
        name1y = "";
        name2y = "";
        name3y = ""; 
    }
    if (dim > 2)
    {
        name1z = "";
        name2z = "";
        name3z = "";
    }
    name = "../out/body_";
    name_pos = "positions";
    name_vel = "velocities";
    name_acc = "accelerations";
    name_axe_x = "_x";
    if (dim > 1) {name_axe_y = "_y";}
    if (dim > 2) {name_axe_z = "_z";}

    name1x.append(name);
    name1x.append(name_pos);
    name1x.append(name_axe_x);
    name1x.append(ext);

    name2x.append(name);
    name2x.append(name_vel);
    name2x.append(name_axe_x);
    name2x.append(ext);

    name3x.append(name);
    name3x.append(name_acc);
    name3x.append(name_axe_x);
    name3x.append(ext);

    if (dim > 1)
    {
        name1y.append(name);
        name1y.append(name_pos);
        name1y.append(name_axe_y);
        name1y.append(ext);

        name2y.append(name);
        name2y.append(name_vel);
        name2y.append(name_axe_y);
        name2y.append(ext);

        name3y.append(name);
        name3y.append(name_acc);
        name3y.append(name_axe_y);
        name3y.append(ext);
    }

    if (dim > 2)
    {
        name1z.append(name);
        name1z.append(name_pos);
        name1z.append(name_axe_z);
        name1z.append(ext);

        name2z.append(name);
        name2z.append(name_vel);
        name2z.append(name_axe_z);
        name2z.append(ext);

        name3z.append(name);
        name3z.append(name_acc);
        name3z.append(name_axe_z);
        name3z.append(ext);
    }





    position_x.open(name1x);
    velocity_x.open(name2x);
    acceleration_x.open(name3x);
    if (dim > 1)
    {
    position_y.open(name1y);
    velocity_y.open(name2y);
    acceleration_y.open(name3y);
    }
    if (dim > 2)
    {
    position_z.open(name1z);
    velocity_z.open(name2z);
    acceleration_z.open(name3z);    
    }

    std::string time_initial = search(main_param, "time_initial");
    std::string time_final   = search(main_param, "time_final");
    std::string delta_time   = search(main_param, "step_min");
    double Tini = std::stof(time_initial); 
    double dt = std::stof(delta_time); 
    double Tfin = std::stof(time_final); 

    double t = Tini; 
    int Nout, out_index;
    std::string number_output = search(output, "number_outputs");
    Nout = std::stoi(number_output);
    double toutput[Nout];
    for (int ii=0; ii<Nout; ii++)
    {
        toutput[ii] = (Tfin - Tini)/Nout*ii ;
    };

    out_index = 0; 
    double eps; 
    std::string epsilon = search(main_param,"softening");
    eps = stof(epsilon);
    
    while(t < Tfin)
    {
        //cout<<"dt = "<<t<<endl;
        for (int ii=0; ii<N; ii++)
        {
            if (dim == 2){objet2[ii].reset_potential();}
            if (dim == 3){objet3[ii].reset_potential();}
            for (int jj=0; jj<N; jj++)
            {
                if (dim == 2){if (jj != ii) {objet2[ii].action_potential(objet2[jj], eps);}}
                if (dim == 3){if (jj != ii) {objet3[ii].action_potential(objet3[jj], eps);}}
            }  
            if (dim == 2){objet2[ii].verlet_2step(1, dt, 0., 0.);}
            if (dim == 3){objet3[ii].verlet_2step(1, dt, 0., 0., 0.);}
        }
        for (int ii=0; ii<N; ii++)
        {   
            if (dim == 2)
            {
            double ax0 = objet2[ii].read_ax();
            double ay0 = objet2[ii].read_ay();
            objet2[ii].reset_potential();
            for (int jj=0; jj<N; jj++)
            {
                if (jj != ii) {objet2[ii].action_potential(objet2[jj], eps);}
            } 
            objet2[ii].verlet_2step(2, dt, ax0, ay0);
            }

            if (dim == 3)
            {
            double ax0 = objet3[ii].read_ax();
            double ay0 = objet3[ii].read_ay();
            double az0 = objet3[ii].read_az();
            objet3[ii].reset_potential();
            for (int jj=0; jj<N; jj++)
            {
                if (jj != ii) {objet3[ii].action_potential(objet3[jj], eps);}
            }
            objet3[ii].verlet_2step(2, dt, ax0, ay0, az0);
            }
        }

        //cout<<"t = "<<t<<" dt = "<<dt<<" toutput = "<<toutput[out_index]<<" out_index = "<<out_index<<endl;
        if (t-dt < toutput[out_index] and t+dt > toutput[out_index])
        {
            cout<<" Avancement : "<<t/Tfin*100.<<" %"<<endl;
            out_index = out_index +1;
            position_x<<t<<"\t";
            if (dim > 1) {position_y<<t<<"\t";}
            if (dim > 2) {position_z<<t<<"\t";}
            velocity_x<<t<<"\t";
            if (dim > 1) {velocity_y<<t<<"\t";}
            if (dim > 2) {velocity_z<<t<<"\t";}
            acceleration_x<<t<<"\t";
            if (dim > 1) {acceleration_y<<t<<"\t";}
            if (dim > 2) {acceleration_z<<t<<"\t";}
            for (int ii=0; ii<N; ii++)
            {
                if (dim == 2)
                {
                position_x<<objet2[ii].read_x()<<"\t";
                position_y<<objet2[ii].read_y()<<"\t";
                velocity_x<<objet2[ii].read_vx()<<"\t";
                velocity_y<<objet2[ii].read_vy()<<"\t";
                acceleration_x<<objet2[ii].read_ax()<<"\t";
                acceleration_y<<objet2[ii].read_ay()<<"\t";
                }
                if (dim == 3)
                {
                position_x<<objet3[ii].read_x()<<"\t";
                position_y<<objet3[ii].read_y()<<"\t";
                position_z<<objet3[ii].read_z()<<"\t";
                velocity_x<<objet3[ii].read_vx()<<"\t";
                velocity_y<<objet3[ii].read_vy()<<"\t";
                velocity_z<<objet3[ii].read_vz()<<"\t";
                acceleration_x<<objet3[ii].read_ax()<<"\t";
                acceleration_y<<objet3[ii].read_ay()<<"\t";
                acceleration_z<<objet3[ii].read_az()<<"\t";
                }
            }
            position_x<<"\n";
            if (dim > 1){position_y<<"\n";}
            if (dim > 2){position_z<<"\n";}
            velocity_x<<"\n";
            if (dim > 1){velocity_y<<"\n";}
            if (dim > 2){velocity_z<<"\n";}
            acceleration_x<<"\n";
            if (dim > 1){acceleration_y<<"\n";}
            if (dim > 2){acceleration_z<<"\n";}
        }
        t += dt;     // Time update
    }
    position_x.close();
    if (dim > 1){position_y.close();}
    if (dim > 2){position_z.close();}
    velocity_x.close();
    if (dim > 1){velocity_y.close();}
    if (dim > 2){velocity_z.close();}
    acceleration_x.close();
    if (dim > 1){acceleration_y.close();}
    if (dim > 2){acceleration_z.close();}
}