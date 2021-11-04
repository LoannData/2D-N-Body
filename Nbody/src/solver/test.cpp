#include <iostream> //For console output/input
#include <fstream>  //Allows to read/write files 
#include <math.h>   //Basic mathematic functions 
#include <vector>   //For dynamic arrays 
#include <string>   //Operations on strings 
#include <tuple>
#include <cmath>
#include <sstream>
using namespace std;

class body 
{
    public : 

    body(){};
    double read_mass(); 
    double read_x();
    double read_y();
    double read_vx();
    double read_vy();
    double read_ax();
    double read_ay();
    void edit_mass(double m); 
    void edit_position(double xnew, double ynew);
    void edit_velocity(double vxnew, double vynew); 
    void edit_acceleration(double axnew, double aynew);
    void action_potential(body objet); 
    void reset_potential();
    void euler(double dt);
    void verlet_2step(int step, double dt, double ax0, double ay0);

    private : 

    double mass;
    double rx;
    double ry;
    double vx;
    double vy;
    double ax;
    double ay;
};


double body::read_mass() 
{
    return mass;
}

double body::read_x()
{
    return rx;
}

double body::read_y()
{
    return ry;
}

double body::read_vx()
{
    return vx;
}

double body::read_vy()
{
    return vy;
}

double body::read_ax()
{
    return ax;
}

double body::read_ay()
{
    return ay;
}

void body::edit_mass(double m)
{
    mass = m;
}

void body::edit_position(double xnew, double ynew)
{
    rx = xnew;
    ry = ynew;
}

void body::edit_velocity(double vxnew, double vynew)
{
    vx = vxnew;
    vy = vynew;
}

void body::edit_acceleration(double axnew, double aynew)
{
    ax = axnew;
    ay = aynew;
}

void body::action_potential(body objet)
{
        double eps = 1e-2; // Softening factor
        double distance = sqrt(pow(rx - objet.read_x(),2) + pow(ry - objet.read_y(),2)) + eps; 
        double G = 1; 
        ax +=  G*objet.read_mass()*(objet.read_x()-rx)/pow(distance,2.);
        ay +=  G*objet.read_mass()*(objet.read_y()-ry)/pow(distance,2.);

}

void body::reset_potential()
{ 
    ax = 0;
    ay = 0;
}

void body::euler(double dt)
{
    vx = vx + dt*ax;
    vy = vy + dt*ay;
    rx = rx + dt*vx + 0.5*pow(dt,2)*ax;
    ry = ry + dt*vy + 0.5*pow(dt,2)*ay; 
}

void body::verlet_2step(int step, double dt, double ax0, double ay0)
{
    if (step == 1)
    {
        rx = rx + vx*dt + 0.5*pow(dt, 2.)*ax;
        ry = ry + vy*dt + 0.5*pow(dt, 2.)*ay;
    }

    if (step ==2)
    {
        vx = vx + 0.5*dt*(ax0 + ax);
        vy = vy + 0.5*dt*(ay0 + ay); 
    }
}


int main()
{
    int N = 200; 
    vector<body> objet;
    int id[N];
    double rx[N], ry[N], vx[N], vy[N];



    ifstream distrib_file;
    std::string distrib_file_name = "../../dist/";
    std::string ext = ".dat";
    std::string distribution = "uniform_circle";

    distrib_file_name.append(distribution);
    distrib_file_name.append(ext);

    distrib_file.open(distrib_file_name);
    int j=0;
    while (!distrib_file.eof())
    {
        distrib_file >> id[j];
        distrib_file >> rx[j];
        distrib_file >> ry[j];
        distrib_file >> vx[j];
        distrib_file >> vy[j];
        j++;
    }

    for (int ii=0; ii<N; ii++)
    {
        double m = 1.0;
        body obj1; 
        obj1.edit_mass(m);
        obj1.edit_position(rx[ii], ry[ii]);
        obj1.edit_velocity(vx[ii], vy[ii]);
        obj1.edit_acceleration(0, 0);
        objet.push_back(obj1);
    }

    ofstream body_output[N]; 
    std::string name[N];
    for (int ii=0; ii<N; ii++)
    {
        name[ii] = "../../out/body_";
        std::ostringstream number;
        number << ii;
        name[ii].append(number.str());
        std::string ext=".dat";
        name[ii].append(ext);
        body_output[ii].open(name[ii]);
    }





    double Tini = 0; 
    double dt = 1e-3; 
    double Tfin = 3.;

    double t = 0; 
    while(t < Tfin)
    {
        cout<<" Avancement : "<<t/Tfin*100.<<" %"<<endl;
        for (int ii=0; ii<N; ii++)
        {
            objet[ii].reset_potential();
            for (int jj=0; jj<N; jj++)
            {
                if (jj != ii) {objet[ii].action_potential(objet[jj]);}
            }  
            objet[ii].verlet_2step(1, dt, 0., 0.);
        }
        for (int ii=0; ii<N; ii++)
        {   
            double ax0 = objet[ii].read_ax();
            double ay0 = objet[ii].read_ay();
            objet[ii].reset_potential();
            for (int jj=0; jj<N; jj++)
            {
                if (jj != ii) {objet[ii].action_potential(objet[jj]);}
            } 
            objet[ii].verlet_2step(2, dt, ax0, ay0);
        }


        //for (int ii=0; ii<N; ii++)
        //{
        //    objet[ii].euler(dt);
        //}
        //cout<<"Position = [t = "<<t/Tfin<<"] ("<<objet[0].read_ax()<<" ,"<<objet[0].read_ay()<<")"<<endl;

        for (int ii=0; ii<N; ii++)
        {
            body_output[ii]<<t<<"\t"<<objet[ii].read_x()<<"\t"<<objet[ii].read_y();
            body_output[ii]<<"\t"<<objet[ii].read_vx()<<"\t"<<objet[ii].read_vy();
            body_output[ii]<<"\t"<<objet[ii].read_ax()<<"\t"<<objet[ii].read_ay()<<endl;
        }
        t += dt;
    }
    for (int ii=0; ii<N; ii++)
    {
        body_output[ii].close();
    }
}
