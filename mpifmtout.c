#include "fmtout.h"
#include "mpifmtout.h"

/**
 * This is a version of fprintf which is intended to be
 * used with MPI code to display the origin of a message.
 * @param op The code indicating what type of message
 * @param who Name of the process or machine
 * @param rank Index of the process
 * @param size Total number of  processes
 * @param fp Stream pointer
 * @param fmt Format specifier
 */
void mffprintf( int op, char *pre, char *who, int wide, int rank, int size, FILE *fp, const char *fmt, ... )
{
	va_list ap;
	va_start( ap, fmt );
	fprintf( fp, "[%*s] (%5d/%5d): ", wide, who, rank, size );
	fprintf( fp, "%-12s: ", pre );
	vfprintf( fp, fmt, ap );
	fprintf( fp, "\n" );
	va_end( ap );
}

void mpisetmsg( t_mpi_msg *obj, int op, char *pre, char *name, int rank, char *msg )
{
	obj->op = op;
	strncpy( obj->pre, pre, 31 );
	strncpy( obj->name, name, 1023 );
	obj->rank = rank;
	strncpy( obj->msg, msg, 4095 );
}

void mpiservercom( int rank, int size, int mst, MPI_Comm *gr )
{
	MPI_Group wg;

	/* Create communicator containing only slaves */
	MPI_Comm_group( MPI_COMM_WORLD, &wg );
	if( rank != mst )
	{
		MPI_Group gwm;
		MPI_Group_excl( wg, 1, &mst, &gwm );
		MPI_Comm_create( MPI_COMM_WORLD, gwm, gr );
	}
	else
	{
		MPI_Comm dmy;
		MPI_Comm_create( MPI_COMM_WORLD, MPI_GROUP_EMPTY, &dmy );
	}
}

/**
 * Server for receiving messages from slave processes; in charge
 * of printing things in a linear fashion, i.e. no interruptions
 * between two items
 */
int mpiprintserver( int rank, int size, int mst, FILE *fp )
{
	MPI_Status stat;
	t_mpi_msg msg;
	if( rank == mst )
	{
		for(;;)
		{
			MPI_Recv( &msg, sizeof(t_mpi_msg), MPI_CHAR, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &stat );
			if( msg.op == T_EXIT )
				break;
			mffprintf( msg.op, msg.pre, msg.name, strlen(msg.name), msg.rank, size, fp, msg.msg );
		}
	}
	else
		return -1;
	return 0;
}

/**
 * Print a message from the local process to a the master node
 */
int mpiprint( int rank, int size, int mst, t_mpi_msg *msg )
{
	MPI_Send( msg, sizeof(t_mpi_msg), MPI_CHAR, mst, 1, MPI_COMM_WORLD );
	return 0;
}

