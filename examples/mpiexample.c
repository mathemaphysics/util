#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include "mpifmtout.h"

int main( int argc, char **argv )
{
	/* MPI variables */
	int rank,size,res,mst=0;
	char name[64];
	MPI_Status stat;
	t_mpi_msg msg;

	/* Initialize MPI */
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Get_processor_name( name, &res );

        /* Create a communicator containing only the slave processes */
        MPI_Comm gr;
        mpiservercom( rank, size, mst, &gr );

        /* Test mpiprintserver() */
        if( rank == mst )
                mpiprintserver( rank, size, mst, stderr );
        else
        {
                msg.op = T_INFO, strcpy( msg.pre, "PREFIX" ), strcpy( msg.name, name ), msg.rank = rank, strcpy( msg.msg, "Just saying hi!" );
                mpiprint( rank, size, mst, &msg );
                MPI_Barrier( gr );
        }
        if( rank == 1 ) /* Tell the print server to end */
        {
                msg.op = T_EXIT;
                mpiprint( rank, size, mst, &msg );
        }

        /* Temporary stop point */
        MPI_Finalize();
        return 0;
}

// vim: tabstop=4:softtabstop=4:shiftwidth=4:expandtab:smarttab
