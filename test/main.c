#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "symtab.h"
#include "cfgread.h"

int main( int argc, char **argv )
{
	int i,n,h;
	FILE *fp;
	char buf[5000],var[128],val[128];
	char *tok[5000];
	char *sep = "=";
	symbol_t *s;
	symtab_t ss;
	symtab_init( &ss, 100000 );
	if( argv[1] != NULL )
	{
		if( cfgread_load_symbols_f( argv[1], &ss ) < 0 )
		{
			printf( "Problem loading symbols. Exiting.\n" );
			return 0;
		}
	}
	else
	{
		printf( "Input file is null.\n" );
		return -1;
	}
	symtab_print( &ss );
	s = symtab_lookup( &ss, "quadrature_type" );
	if( s == NULL )
		printf( "Could not find variable!\n" );
	else
		printf( "Variable found! Value = %s\n", (char*)(s->data) );
	if( argv[2] != NULL )
		cfgread_save_symbols_f( argv[2], &ss );
	else
	{
		printf( "Output file is null.\n" );
		return -1;
	}
	return 0;
}

