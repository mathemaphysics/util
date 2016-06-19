#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "combinadic.h"

int main( int argc, char **argv )
{
	int i,j;
	int dim = 3;
	int ord = 4;
	int exp[3];

	for(j=0;j<10;j++)
	{
		global_polynomial_vector( j, dim, exp );
		for(i=0;i<dim;i++)
			printf( "%d ", exp[i] );
		printf( "\n" );
	}

	return 0;
}

