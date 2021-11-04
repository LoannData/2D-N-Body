#include <iostream> //For console output/input
#include <fstream>  //Allows to read/write files 
#include <math.h>   //Basic mathematic functions 
#include <vector>   //For dynamic arrays 
#include <string>   //Operations on strings 
#include <tuple>
#include <cmath>
#include <sstream>
using namespace std;

// CLASS : BODY 2 DIMENSIONS ---------------------------------------------------
class body2d 
{
    public : 

    body2d(){};
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
    void action_potential(body2d objet, double eps); 
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


double body2d::read_mass() 
{
    return mass;
}

double body2d::read_x()
{
    return rx;
}

double body2d::read_y()
{
    return ry;
}

double body2d::read_vx()
{
    return vx;
}

double body2d::read_vy()
{
    return vy;
}

double body2d::read_ax()
{
    return ax;
}

double body2d::read_ay()
{
    return ay;
}

void body2d::edit_mass(double m)
{
    mass = m;
}

void body2d::edit_position(double xnew, double ynew)
{
    rx = xnew;
    ry = ynew;
}

void body2d::edit_velocity(double vxnew, double vynew)
{
    vx = vxnew;
    vy = vynew;
}

void body2d::edit_acceleration(double axnew, double aynew)
{
    ax = axnew;
    ay = aynew;
}

void body2d::action_potential(body2d objet, double eps)
{
        //double eps = 1e-2; // Softening factor
        double distance = sqrt(pow(rx - objet.read_x(),2) + pow(ry - objet.read_y(),2)) + eps; 
        double G = 1; 
        ax +=  G*objet.read_mass()*(objet.read_x()-rx)/pow(distance,2.);
        ay +=  G*objet.read_mass()*(objet.read_y()-ry)/pow(distance,2.);

}

void body2d::reset_potential()
{ 
    ax = 0;
    ay = 0;
}

void body2d::euler(double dt)
{
    vx = vx + dt*ax;
    vy = vy + dt*ay;
    rx = rx + dt*vx + 0.5*pow(dt,2)*ax;
    ry = ry + dt*vy + 0.5*pow(dt,2)*ay; 
}

void body2d::verlet_2step(int step, double dt, double ax0, double ay0)
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
// END CLASS : BODY 2 DIMENSIONS ---------------------------------

// CLASS : BODY 3 DIMENSIONS -----------------------------------
class body3d 
{
    public : 

    body3d(){};
    double read_mass(); 
    double read_x();
    double read_y();
    double read_z();
    double read_vx();
    double read_vy();
    double read_vz();
    double read_ax();
    double read_ay();
    double read_az();
    void edit_mass(double m); 
    void edit_position(double xnew, double ynew, double znew);
    void edit_velocity(double vxnew, double vynew, double vznew); 
    void edit_acceleration(double axnew, double aynew, double aznew);
    void action_potential(body3d objet, double eps); 
    void reset_potential();
    void euler(double dt);
    void verlet_2step(int step, double dt, double ax0, double ay0, double az0);

    private : 

    double mass;
    double rx;
    double ry;
    double rz;
    double vx;
    double vy;
    double vz;
    double ax;
    double ay;
    double az;
};


double body3d::read_mass() 
{
    return mass;
}

double body3d::read_x()
{
    return rx;
}

double body3d::read_y()
{
    return ry;
}

double body3d::read_z()
{
    return rz;
}

double body3d::read_vx()
{
    return vx;
}

double body3d::read_vy()
{
    return vy;
}

double body3d::read_vz()
{
    return vz;
}

double body3d::read_ax()
{
    return ax;
}

double body3d::read_ay()
{
    return ay;
}

double body3d::read_az()
{
    return az;
}

void body3d::edit_mass(double m)
{
    mass = m;
}

void body3d::edit_position(double xnew, double ynew, double znew)
{
    rx = xnew;
    ry = ynew;
    rz = znew;
}

void body3d::edit_velocity(double vxnew, double vynew, double vznew)
{
    vx = vxnew;
    vy = vynew;
    vz = vznew;
}

void body3d::edit_acceleration(double axnew, double aynew, double aznew)
{
    ax = axnew;
    ay = aynew;
    az = aznew; 
}

void body3d::action_potential(body3d objet, double eps)
{
        //double eps = 1e-2; // Softening factor
        double distance = sqrt(pow(rx - objet.read_x(),2) + pow(ry - objet.read_y(),2) + pow(rz - objet.read_z(),2)) + eps; 
        double G = 1; 
        ax +=  G*objet.read_mass()*(objet.read_x()-rx)/pow(distance,2.);
        ay +=  G*objet.read_mass()*(objet.read_y()-ry)/pow(distance,2.);
        az +=  G*objet.read_mass()*(objet.read_z()-rz)/pow(distance,2.);

}

void body3d::reset_potential()
{ 
    ax = 0;
    ay = 0;
    az = 0;
}

void body3d::euler(double dt)
{
    vx = vx + dt*ax;
    vy = vy + dt*ay;
    vz = vz + dt*az;
    rx = rx + dt*vx + 0.5*pow(dt,2)*ax;
    ry = ry + dt*vy + 0.5*pow(dt,2)*ay; 
    rz = rz + dt*vz + 0.5*pow(dt,2)*az;
}

void body3d::verlet_2step(int step, double dt, double ax0, double ay0, double az0)
{
    if (step == 1)
    {
        rx = rx + vx*dt + 0.5*pow(dt, 2.)*ax;
        ry = ry + vy*dt + 0.5*pow(dt, 2.)*ay;
        rz = rz + vz*dt + 0.5*pow(dt, 2.)*az;
    }

    if (step ==2)
    {
        vx = vx + 0.5*dt*(ax0 + ax);
        vy = vy + 0.5*dt*(ay0 + ay); 
        vz = vz + 0.5*dt*(az0 + az); 
    }
}
// END CLASS : BODY 3 DIMENSIONS ------------------------------------