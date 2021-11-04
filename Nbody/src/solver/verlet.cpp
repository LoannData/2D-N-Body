#include <iostream> //For console output/input
#include <fstream>  //Allows to read/write files 
#include <math.h>   //Basic mathematic functions 
#include <vector>   //For dynamic arrays 
#include <string>   //Operations on strings 
#include <tuple>
#include <cmath>
using namespace std;

vector< vector<double> > verlet1pas_2D(int N, double dt, vector<double> X0, vector<double> Y0, vector<double> VX0, vector<double> VY0, vector<double> AX0, vector<double> AY0);

int main()
{
    int N = 50;
    double tini = 1e-3;
    double dt = 1e-6;
    vector<double> X0(N), Y0(N), VX0(N), VY0(N), AX0(N), AY0(N); 
    for (int ii=0; ii<N; ii++)
    {
        X0[ii] = pow(ii,-1);
        Y0[ii] = pow(ii, 1);
        VX0[ii] = ii + 1;
        VY0[ii] = ii - 1;
        AX0[ii] = pow(ii, 2.); 
        AY0[ii] = pow(ii, -2.); 
    }
    vector< vector<double> > M(4, vector<double>(N));
    M = verlet1pas_2D(N, dt, X0, Y0, VX0, VY0, AX0, AY0);

    cout<<M[0][0]<<endl;
    


}



vector< vector<double> > verlet1pas_2D(int N, double dt, vector<double> X0, vector<double> Y0, vector<double> VX0, vector<double> VY0, vector<double> AX0, vector<double> AY0)
{
    vector< vector<double> > M(4, vector<double>(N));
    for (int ii=0; ii<N; ii++)
    {
        M[0][ii] = X0[ii] + dt*VX0[ii] + 0.5*pow(dt, 2.)*AX0[ii];
        M[1][ii] = Y0[ii] + dt*VY0[ii] + 0.5*pow(dt, 2.)*AY0[ii];
        M[2][ii] = VX0[ii] + 0.5*dt*AX0[ii];
        M[3][ii] = VY0[ii] + 0.5*dt*AY0[ii];
    }
    return M;
}