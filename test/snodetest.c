#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include "symtab.h"
#include "parse.h"

int build_tree( snode_t *base_in )
{
	/* First look for equality signs */
	int i,n;
	char *tok_out[128];
	char buf[512];
	strcpy( buf, base_in->str );
	n = parse_stokenize( buf, tok_out, "=" );
	if( n > 1 )
	{
		snode_set_op( base_in, "eq", 0 ); /* optype_in <= 0 means void, i.e. no return */
		for(i=0;i<n;i++)
			snode_add_child( base_in, parse_strip_white( tok_out[i] ) );
		for(i=0;i<n;i++)
			build_tree( base_in->child + i );
	}
	else
	{
		snode_set_op( base_in, "sum", 1 ); /* optype > 0 means returns a result */
		strcpy( buf, base_in->str );
		n = parse_stokenize( buf, tok_out, "+-" );
		if( n > 1 )
		{
			for(i=0;i<n;i++)
				snode_add_child( base_in, parse_strip_white( tok_out[i] ) );
			for(i=0;i<n;i++)
				build_tree( base_in->child + i ); /* Recursion */
		}
		else
		{
			snode_set_op( base_in, "vec", 1 );
			strcpy( buf, base_in->str );
			n = parse_stokenize( buf, tok_out, "," );
			if( n <= 1 )
				return 0;
			else
			{
				for(i=0;i<n;i++)
					snode_add_child( base_in, parse_strip_white( tok_out[i] ) );
				for(i=0;i<n;i++)
					build_tree( base_in->child + i );
			}
		}
	}
	return 0;
}

int execute_tree( snode_t *obj_in, char *ret_out, symtab_t *smt_out )
{
	
}

int main( int argc, char **argv )
{
	/* Initialize and fill a syntax tree */
	snode_t base,nodes[64];
	symtab_t smt;
	symtab_init( &smt, 128 );
	int i,n;
	char *tok[128];
	char out[512];
	char st[128] = "s1,s2 + t1,t2 - z1,z2 = v1,v2 + w1,w2 + x1,x2 + y1,y2";
	snode_init( &base, 128 );
	snode_set_string( &base, st );
	build_tree( &base );
	stree_print( &base, 0 );
	execute_tree( &base, out, &smt );
	stree_free( &base );

	return 0;
}
