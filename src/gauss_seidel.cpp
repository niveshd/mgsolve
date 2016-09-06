#include "../include/grid.h"

void gauss_seidel(grid& residual, grid& U, grid & b)
{
	//grid output
	// grid& residual, U, b // u is the input matrix, b is right hand side of the eqn (Ax = b)
	unsigned long int numberOfNodes; // to get the value of nodes.
	unsigned long int i,j; // temperory variable for iterations
	double step_size;
	double temp;
	numberOfNodes = U.size();
	step_size = U.step_size();
// =======================Red==================================
	for (i = 1; i < numberOfNodes-1; i = i+2)
		{
		for (j=1; j< numberOfNodes-1; j = j+2)
			{
				temp = ((U.get(i-1,j) + U.get(i+1,j) + U.get(i,j+1) + U.get(i, j-1)) - (step_size * step_size * b.get(i,j)))/4.0;
				U.set(i,j,temp);
		 	}
		}

	// second iteration to cover the remaining red nodes
	for (i = 2; i < numberOfNodes-1; i = i+2)
		{
		for (j=2; j< numberOfNodes-1; j = j+2)
			{
				temp = ((U.get(i-1,j) + U.get(i+1,j) + U.get(i,j+1) + U.get(i, j-1)) - (step_size * step_size * b.get(i,j)))/4.0;
				U.set(i,j,temp);
		 	}
		}

// ==============Black method===================================
for (i = 1; i < numberOfNodes-1; i = i+2)
		{
		for (j=2; j< numberOfNodes-1; j = j+2)
			{
				temp = ((U.get(i-1,j) + U.get(i+1,j) + U.get(i,j+1) + U.get(i, j-1)) - (step_size * step_size * b.get(i,j)))/4.0;
				U.set(i,j,temp);
		 	}
		}

	// second iteration to cover the remaining red nodes
	for (i = 2; i < numberOfNodes-1; i = i+2)
		{
		for (j=1; j< numberOfNodes-1; j = j+2)
			{
				temp = ((U.get(i-1,j) + U.get(i+1,j) + U.get(i,j+1) + U.get(i, j-1)) - (step_size * step_size * b.get(i,j)))/4.0;
				U.set(i,j,temp);
		 	}
		}
//=================Residual=============================================

	for (i = 1; i < numberOfNodes-1; ++i)
	{
		for (j=1; j< numberOfNodes-1; ++j)
		{
			temp = b.get(i,j) + (1.0/(step_size*step_size))*(4*U.get(i,j) - (U.get(i-1,j) + U.get(i+1,j) + U.get(i,j+1) + U.get(i, j-1)));
			residual.set(i,j,temp);
		}
	}
//======================================================================

}
