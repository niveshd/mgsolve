#include <iostream>
#include <cstdlib>
#include "./include/grid.h"
#include <assert.h>
#include "./include/vsolve.h"
#include "./include/gauss_seidel.h"
#define pi 3.14159265358979323846
#include <ctime>
#include <fstream>

//Git test version

int main(int argc, char *argv[]){

//check if the # of arguments is 2. otherwise give error
    assert (argc <= 3);

//Note values of no of levels and no of v cycles
    int l = atoi(argv[1]);
    int n = atoi(argv[2]);
    //int flag = 0; // flag to ensure that if the program is run, a new solution.txt file is created.
    assert (l > 0 && n > 0);

    std::cout << "No of levels " << l << ". No of V cycles " << n << std::endl;

//Construct u(#of levels), F needs to be given
    grid u(l); grid b(l); grid r(l);
    double d;
    for (unsigned long int i = 1; i != u.size() - 1; ++i){
	d = sin(pi*i*u.step_size())*sinh(pi);
        u.set(i,u.size()-1,d);
    }

//Start time of Vcycle
std::clock_t start,end;
start = clock();

//variables to store residual and convergence rate every vcycle
double norm = 1, pre_norm = 1;

//Vcycle
for (int i = 0; i != n; ++i){
    vsolve(u,b);
    norm = norm_residual(u,b);

    std::cout << "V cycle # " << i << std::endl;

    if (i != 0)
        std::cout << "Convergence rate q: " <<  norm/pre_norm << std::endl;

    std::cout << "Residual Norm: "<< norm << std::endl;

    pre_norm = norm;
}

end = clock();
double time_taken = double(end - start)/CLOCKS_PER_SEC;
std::cout << "Time taken is " << time_taken << std::endl;

//writing to file

/* if (std::ifstream("solution.txt"))
{
	if(remove("solution.txt"))
	{std::cout << std::endl << "Deleting the previous solution.txt" << std::endl;}
}



std::ofstream file1("step_size_vs_time.txt", std::ios::app);
file1 << "\n" << u.step_size() << "\t" << time_taken;
std::ofstream file2("step_size_vs_error.txt", std::ios::app);
file2 << "\n" << u.step_size() << "\t" << u.error();
std::cout << "error is "<< u.error() << std::endl;

file1.close();
file2.close(); */

//print output;
u.print();

//Time taken vs Different grid sizes for a fixed number of cycles (10)
//L2 Norm of error vs grid size (Make sure solution converges/no. of cycles)
//Read file to operate mgsolve
}
