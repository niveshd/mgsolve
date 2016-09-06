#include <iostream>
#include "../include/grid.h"
#include "../include/gauss_seidel.h"
#include <math.h>

void vsolve(grid &X, grid &B){
    grid R(X.lev());

    if (X.lev() == 1){
        double d = -1/4.0*(B.get(1,1))*X.step_size()*X.step_size();
        X.set(1,1,d);
    }
    else {
        for (int i = 1; i != 3; ++i){
            gauss_seidel(R, X, B);
        }


        grid x(X.lev()-1);
        grid b = R.restrict();

        vsolve(x,b);
        grid e = x.intpol();
        X = X + e;
    }
}

double norm_residual(grid &X, grid &B){
    double sum = 0;
    auto nodes = X.size();
    double temp = 0;
    for (unsigned long int i = 1; i < nodes-1; ++i)
            {
                for (unsigned long int j=1; j < nodes-1; ++j)
                {
                    temp = B.get(i,j) + (1.0/(X.step_size()*X.step_size()))*(4*X.get(i,j) - (X.get(i-1,j) + X.get(i+1,j) + X.get(i,j+1) + X.get(i, j-1)));
                    sum += temp*temp;
                }
            }
    sum = sum/((nodes-2)*(nodes-2));
    sum = sqrt(sum);
    return sum;
}
