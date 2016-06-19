#ifndef PARSE_H
#define PARSE_H

#include "utildefs.h"

#define UTIL_MAX_RANGES 512
#define UTIL_BUFFER_LEN 2048

void parse_print_white( FILE *, int );

void parse_print_back( FILE *, int );

char *parse_strip_white( char * );

int parse_read_line( FILE *, char * );

int parse_stokenize( char *, char **, char * );

int parse_ftokenize( FILE *, char *, char **, char * );

int parse_read_ranges( char *, int *** );

long parse_read_ranges_long( char *, long *** );

typedef struct snode
{
	int id;
	int len;
	char *str;
	int deg;
	int alloc;
	struct snode *child;
	char op[SNODE_OP_SIZE];
	char optype;
} snode_t;

int snode_init( snode_t *obj_in, int len_in );

int snode_alloc( snode_t *obj_in, int len_in );

int snode_free( snode_t *obj_in );

int snode_set_string( snode_t *, char * );

int snode_set_op( snode_t *, char *, char );

int snode_add_child( snode_t *, char * );

int stree_free( snode_t * );

int stree_print( snode_t *, int );

#endif

