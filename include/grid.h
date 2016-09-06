#ifndef GRID
#define GRID
#include <vector>
#include <math.h>
#include <iostream>
#include <assert.h>


struct grid{

//default constructor
    grid() = default;

//constructor. intialize (2^L + 1) x (2^L+ 1) to 0. n_nodes is no. of nodes 2^L + 1
    grid(long unsigned int i):n_lev(i){}

//getter function a.get(i, j) //a is a grid object
    double get(const unsigned long int&,const unsigned long int&);

//setter function a.set(i, j, u). at grid pt (i,j) u is set
    void set(const unsigned long int&, const unsigned long int&, const double&);

//print function. a.print();
    void print();

//Restrict grid. make a smaller grid 1/2 the size. b = a.restrict();
    grid restrict();

//Interpolation grid. b = a.intpol();
    grid intpol();

//get step size. g.size();
    unsigned long int size();

//get step size. g.step_size();
    double step_size();

//subtraction
    grid operator-(grid &rhs);

//Addition
    grid operator+(grid &rhs);

//level getter
    long unsigned int lev();

//error calculation
    double error();


private:
//grid variables.
long unsigned int n_lev = 1;
double h = 1/pow(2,n_lev); //step size
long unsigned int n_nodes = (pow(2,n_lev) + 1);
std::vector<std::vector<double>> data{n_nodes,std::vector<double>(n_nodes)}; // initialized as 0;

};

#endif
