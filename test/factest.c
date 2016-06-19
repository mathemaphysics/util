#include <stdio.h>
#include "combinadic.h"

int main( int argc, char **argv )
{
	int i = 1,j;
	int ptr[5],qtr[5];
	rcombinadic_init( 8, 3, ptr );
	for(i=0;i<10;i++)
	{
		rcombinadic_occupancy( 8, 3, ptr, qtr );
		for(j=0;j<3;j++)
			printf( "%d ", qtr[j] );
		printf( "\n" );
		for(j=0;j<2;j++)
			printf( "%d ", ptr[j] );
		printf( "\n" );
		rcombinadic_next( 8, 3, ptr );
	}
	return 0;
}

