#include <iostream> //For console output/input
#include <fstream>  //Allows to read/write files 
#include <math.h>   //Basic mathematic functions 
#include <vector>   //For dynamic arrays 
#include <string>   //Operations on strings 
#include <tuple>
#include <cmath>
#include <sstream>
using namespace std;

class Point 
{
    public : 

    double get_x();
    double get_y();
    void set_x(double xp);
    void set_y(double yp);

    void get_information();

    private : 

    double x;
    double y;
};

double Point::get_x(){return x;}
double Point::get_y(){return y;}
void Point::set_x(double xp){x = xp;}
void Point::set_y(double yp){y = yp;}


class Rectangle
{
    public : 
    
    double get_x();
    double get_y();
    double get_w();
    double get_h();

    void set_x(double xc);
    void set_y(double yc);
    void set_w(double wc);
    void set_h(double hc);

    bool contain(Point pt);

    void get_information();

    private : 

    double x; 
    double y; 
    double w;
    double h;
};

double Rectangle::get_x() {return x;}
double Rectangle::get_y() {return y;}
double Rectangle::get_w() {return w;}
double Rectangle::get_h() {return h;}

void Rectangle::set_x(double xc) {x = xc;}
void Rectangle::set_y(double yc) {y = yc;}
void Rectangle::set_w(double wc) {w = wc;}
void Rectangle::set_h(double hc) {h = hc;}


class QuadTree 
{
    public : 

    Rectangle get_boundary(); 
    int get_capacity();
    void set_boundary(double xc, double yc, double wc, double hc);
    void set_rectangle(Rectangle rect);
    void set_capacity(int capacity); 

    void insert(Point pt);
    void subdivide();
    void set_divided();
    bool is_divided();

    void get_information(); 

    QuadTree getNW();
    QuadTree getNE();
    QuadTree getSW();
    QuadTree getSE();
    void setNW();
    void setNE();
    void setSW();
    void setSE();
    QuadTree* NW=NULL;
    QuadTree* NE=NULL;
    QuadTree* SW=NULL;
    QuadTree* SE=NULL;

    private : 

    Rectangle boundary;
    //int n; // Capacity
    //n = 1;
    vector<Point> p;
    bool divided = false;
    //4 children
    //vector<QuadTree> child;
    //QuadTree northwest;
    //QuadTree* child[4];

};

QuadTree QuadTree::getNW(){return *NW;}
QuadTree QuadTree::getNE(){return *NE;}
QuadTree QuadTree::getSW(){return *SW;}
QuadTree QuadTree::getSE(){return *SE;}

void QuadTree::setNW(){NW=NULL;}
void QuadTree::setNE(){NE=NULL;}
void QuadTree::setSW(){SW=NULL;}
void QuadTree::setSE(){SE=NULL;}

class CQuadTree 
{
    public : 

    Rectangle get_boundary(); 
    int get_capacity();
    void set_boundary(double xc, double yc, double wc, double hc);
    void set_rectangle(Rectangle rect);
    void set_capacity(int capacity); 

    void insert(Point pt);
    void subdivide();
    void set_divided();
    bool is_divided();

    void get_information(); 
    
    QuadTree NW;
    QuadTree NE;
    QuadTree SW;
    QuadTree SE;

    private : 

    Rectangle boundary;
    //int n; // Capacity
    //n = 1;
    vector<Point> p;
    bool divided = false;


};

bool QuadTree::is_divided()
{
    return divided;
}

bool CQuadTree::is_divided()
{
    return divided;
}

bool Rectangle::contain(Point pt)
{
    return (pt.get_x() > get_x() - get_w() 
    and     pt.get_x() < get_x() + get_w()
    and     pt.get_y() > get_y() - get_h()
    and     pt.get_y() < get_y() + get_h());
}

Rectangle QuadTree::get_boundary() {return boundary;}
Rectangle CQuadTree::get_boundary() {return boundary;}
void QuadTree::set_boundary(double xc, double yc, double wc, double hc)
{
    boundary.set_x(xc); 
    boundary.set_y(yc);
    boundary.set_w(wc);
    boundary.set_h(hc);
}

void CQuadTree::set_boundary(double xc, double yc, double wc, double hc)
{
    boundary.set_x(xc); 
    boundary.set_y(yc);
    boundary.set_w(wc);
    boundary.set_h(hc);
}
//int QuadTree::get_capacity() {return n;}
//void QuadTree::set_capacity(int capacity) {n = capacity;}
void QuadTree::set_divided() {divided = true;}
void CQuadTree::set_divided() {divided = true;}
void QuadTree::set_rectangle(Rectangle rect) {boundary = rect;}
void CQuadTree::set_rectangle(Rectangle rect) {boundary = rect;}
void QuadTree::subdivide()
{
    double xc = boundary.get_x(); 
    double yc = boundary.get_y();
    double wc = boundary.get_w(); 
    double hc = boundary.get_h();
    Rectangle nw;
    nw.set_x(xc-wc/2.);
    nw.set_y(yc+hc/2.);
    nw.set_w(wc/2.);
    nw.set_h(hc/2.);
    Rectangle ne;
    ne.set_x(xc+wc/2.);
    ne.set_y(yc+hc/2.);
    ne.set_w(wc/2.);
    ne.set_h(hc/2.);
    Rectangle sw;
    sw.set_x(xc-wc/2.);
    sw.set_y(yc-hc/2.);
    sw.set_w(wc/2.);
    sw.set_h(hc/2.);
    Rectangle se; 
    se.set_x(xc-wc/2.);
    se.set_y(yc+hc/2.);
    se.set_w(wc/2.);
    se.set_h(hc/2.);

    

    //cout<<"Bonour "<<endl;

    QuadTree oNW, oNE, oSW, oSE; 
    //cout<<"Bonour "<<endl;
    
    //NW->createNW(); 
    //oNW.divided = false; 
    oNW.set_rectangle(nw); 
    //oNW.get_information();
    //NE->createNE(); 
    //oNE.divided = false; 
    oNE.set_rectangle(ne); 
    //oNE.get_information();
    //SW->createSW(); 
    //oSW.divided = false; 
    oSW.set_rectangle(sw); 
    //oSW.get_information();
    //SE->createSE(); 
    //oSE.divided = false; 
    oSE.set_rectangle(se); 
    //oSE.get_information();

    NW = &oNW;
    NE = &oNE; 
    SW = &oSW;
    SE = &oSE;

    //delete &oNW, &oNE, &oSW, &oSE;

    //NW.get_information();

    NW->get_information();

    //divided = true;
    
}

/*
void QuadTree::insert(Point pt)
{
    

    if (! get_boundary().contain(pt) ) {cout<<"Hello 1"<<endl; return; }


    if (p.size() < 1) 
    {
        cout<<"Hello 2"<<endl; 
        p.push_back(pt); // Insert element at the end

        //delete *child;
    }
    else 
    {

        if (!divided)
        {
            
            QuadTree::subdivide();
        //    QuadTree::set_divided();
            
        }

        
    }
        //cout<<"Yo ! "<<endl;
        //pt.get_information();
        //QuadTree NW, NE, SW, SE;
        //NW = *child[0]; 
        //NE = *child[1]; 
        //SW = *child[2]; 
        //SE = *child[3];
        cout<<"Hello 3"<<endl;
        NW->insert(pt);
        NE->insert(pt);
        SW->insert(pt);
        cout<<"Hello 4"<<endl;
        SE->insert(pt);
        cout<<"Hello 4"<<endl;
        //child.push_back(NW);
        //child.push_back(NE); 
        //child.push_back(SW); 
        //child.push_back(SE);

        divided = true;
        //child[0]->insert(pt);
        //child[1]->insert(pt);
        //child[2]->insert(pt);
        //child[3]->insert(pt);
}
*/

void Point::get_information()
{
    cout<<"Point : x = "<<get_x()<<"; y = "<<get_y()<<endl;
}

void Rectangle::get_information()
{
    cout<<"Rectangle : Center Position = ("<<get_x()<<", "<<get_y()<<"), Width = "<<get_w()<<", Height = "<<get_h()<<endl;
}

void QuadTree::get_information()
{
    cout<<"QuadTree : Capacity = "<<" 1"<<", Divided (0:False, 1:True) = "<<divided<<endl;
    boundary.get_information(); 
    
    if (divided) {
    QuadTree oNW, oNE, oSW, oSE;
    cout<<" Northwest : "<<endl;
    oNW = getNW();
    oNW.get_information();
    //delete &oNW;
    //setNW();
    cout<<" Northeast : "<<endl;
    oNE = getNE();
    oNE.get_information();
    //setNE();
    cout<<" Southwest : "<<endl;
    oSW = getSW();
    //SW->get_information();
    //setSW();
    cout<<" Southeast : "<<endl;
    oSE = getSE();
    //SE->get_information();
    //setSE();
    

    }

    //NW->get_information();
    //oNW->get_information();
    /*
    cout<<"Points_in : "<<endl; 
    int siz = p.size();
    for (int ii=0; ii<siz; ii++)
    {
        p[ii].get_information();
    }
    */

    
}

/*
int main()
{
    QuadTree tree, northeast;
    tree.set_boundary(0., 0., 10., 10.);
    //tree.set_capacity(1);

    int N = 10; // Number of points to test 
    vector<Point> pt;
    //pt.resize(N);

    double LO = 0.;
    double HI = 10.;

    for (int ii=0; ii<N; ii++)
    {
        double xrand = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        double yrand = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        Point pt_temp; 
        pt_temp.set_x(xrand); 
        pt_temp.set_y(yrand);
        pt.push_back(pt_temp);

        cout<<"Point :  x = "<<xrand<<" ; y = "<<yrand<<endl;
    }
    

    tree.insert(pt[0]);
    //tree.get_information();
    //tree.insert(pt[5]);
    
    //for (int ii=0; ii<N; ii++)
    //{
    //   tree.insert(pt[ii]);
    //}

    //tree.get_information();

    //northeast.get_information();
    

    

    //cout<<tree.is_divided()<<endl;

}
*/



int main()
{
    QuadTree tree; 
    tree.set_boundary(0., 0., 10., 10.);
    tree.get_information();
    cout<<"-------------------"<<endl;
    tree.subdivide();
    tree.set_divided();
    //tree.NW->subdivide();
    //tree.NW->set_divided();
    //tree.NW->NW->subdivide();
    //tree.NW->NW->set_divided();
    cout<<"-------------------"<<endl;
    tree.get_information();
    //cout<<"-------------------"<<endl;
    //tree.NE->get_information();
}
