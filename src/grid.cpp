#include "../include/grid.h"
#include <iomanip>
#include <math.h>
#define pi1 3.14159265358979323846
#include <assert.h>
#include <fstream>



double grid::get(const unsigned long int&i, const unsigned long int&j ){
//ensure i, j are within bounds
    assert (i < n_nodes && j < n_nodes);
    return data[i][j];

}

void grid::set(const unsigned long int& i, const unsigned long int& j, const double& u){
//ensure i, j are within bounds
    assert (i < n_nodes && j < n_nodes);
    data[i][j] = u;

}

void grid::print(){
std::ofstream file1("solution.txt",std::ios::app);

    for (unsigned long int j = 0; j != n_nodes; ++j){
        for (unsigned long int i = 0; i != n_nodes; ++i){
            file1 << "\n" << i*h << "\t" << j*h << "\t" << data[i][j];
        }

    }
file1.close();

}

grid grid::restrict(){
    assert(n_lev > 1);
    grid g(n_lev -1);

//loop through grid inner points only. Dont touch boundary.
    for (unsigned long int i = 1; i != g.n_nodes - 1; ++i){
        for (unsigned long int j = 1; j != g.n_nodes - 1; ++j){
            double u;

    //update the grid value. Weighted Restriction
            u = 1.0/4*(this->get(2*i,2*j));

            u += 1.0/8*((this->get(2*i+1,2*j))  + (this->get(2*i - 1,2*j))  +  (this->get(2*i,2*j+1)) +   (this->get(2*i,2*j-1)));

            u += 1.0/16*((this->get(2*i+1,2*j+1))  + (this->get(2*i-1,2*j-1))  +  (this->get(2*i-1,2*j+1)) +   (this->get(2*i+1,2*j-1)));
            g.set(i,j,u);
        }
    }

    return g;

}


grid grid::intpol(){
    grid g(n_lev+1);

//4 LOOPS through grid inner points. No boundary!
    //loop - points sharing no grid (weights = 1)
        for (unsigned long int i = 1; i <= g.n_nodes-1; i = i+2){
            for (unsigned long int j = 1; j <= g.n_nodes-1; j = j+2){
                double u;
                u = 1.0/4*((this->get((i-1)/2, (j-1)/2))  + (this->get((i+1)/2, (j-1)/2))  +  (this->get((i-1)/2, (j+1)/2)) +   (this->get((i+1)/2, (j+1)/2)));
                g.set(i,j,u);
            }
        }

    //loop - points sharing horizontal grid (weights = 0.5)
        for (unsigned long int i = 1; i <= g.n_nodes-1; i = i+2){
                for (unsigned long int j = 2; j <= g.n_nodes-1; j = j+2){
                    double u;
                    u = 1.0/2*((this->get((i-1)/2, (j)/2))  + (this->get((i+1)/2, (j)/2)));
                    g.set(i,j,u);
                }
            }

    //loop - points sharing vertical grid
        for (unsigned long int i = 2; i <= g.n_nodes-1; i = i+2){
                for (unsigned long int j = 1; j <= g.n_nodes-1; j = j+2){
                    double u;
                    u = 1.0/2*((this->get((i)/2, (j-1)/2))  + (this->get((i)/2, (j+1)/2)));
                    g.set(i,j,u);
                }
            }

    //loop - shared points
        for (unsigned long int i = 2; i <= g.n_nodes-1; i = i+2){
                for (unsigned long int j = 2; j <= g.n_nodes-1; j = j+2){
                    double u;
                    u = 1.0*((this->get((i)/2, (j)/2)));
                    g.set(i,j,u);
                }
            }

    return g;
}


unsigned long int grid::size(){
    return n_nodes;
}

double grid::step_size(){
    return h;
}

grid grid::operator-(grid &rhs){
    grid res(n_lev);
    for (unsigned long int i = 0; i != n_nodes; ++i){
                for (unsigned long int j = 0; j != n_nodes; ++j){
                    res.set(i,j, data[i][j]-rhs.get(i,j));
                }
            }
    return res;
}

grid grid::operator+(grid &rhs){
    grid res(n_lev);
    for (unsigned long int i = 0; i != n_nodes; ++i){
                for (unsigned long int j = 0; j != n_nodes; ++j){
                    res.set(i,j, (data[i][j])+rhs.get(i,j));
                }
            }
    return res;
}

long unsigned int grid::lev(){
    return n_lev;
}

double grid::error(){
    double err = 0, temp;
        for (unsigned long int i = 1; i < n_nodes-1; ++i)
            {
                for (unsigned long int j=1; j < n_nodes-1; ++j)
                {
                    temp = data[i][j] - sin(i*pi1*h)*sinh(j*pi1*h);
                    err += temp*temp;
                }
            }
    err = err/((n_nodes-2)*(n_nodes-2));
    err = sqrt(err);
    return err;
}
