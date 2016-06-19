#include "fmtout.h"

/**
 * A version of fprintf which tacks my program name on
 * the front to make sure we always know that the output
 * is coming from this code!!!
 */
void ffprintf( int op, char *pre, FILE *fp, const char *fmt, ... )
{
        va_list ap;
        va_start( ap, fmt );
	fprintf( fp, "%-12s: ", pre );
        vfprintf( fp, fmt, ap );
	fprintf( fp, "\n" );
        va_end( ap );
}

