// payout_engine.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUF_SZ 1024

int usage (char * program )
{
	printf( "usage: %s [file | STDIN]\n", program );
	printf( "calculate payout\n" );
	printf( "   file   input file to read\n" );
	printf( "   STDIN  piped input\n" );
	return 0;
}

/* parse_handle - parses file handle for all input, line by line, in the
 * expected format (CSV)
 * @param fp - handle to read from
 */
int parse_handle ( FILE * fp )
{
	char buf[LINE_BUF_SZ];
	long lSize;
	int num_read;

	printf( "parse_handle\n" );

	// see if there is anything to read
	if ( fp != stdin ) {
		// obtain file size:
		fseek (fp , 0 , SEEK_END);
		lSize = ftell (fp);
		rewind (fp);

		if ( lSize < 0 ) {
			printf( "nothing to read\n");
			return 0;
		}
	}

	while ( !feof(fp) ) {
//		fgets(buf, sizeof buf, fp);
		num_read = fscanf( fp, "%s", buf );

		if ( feof(fp) ) break;

		/* correctly read all values */
		if ( num_read == 1 ) {
			printf( "read: %s\n", buf );
			// TODO: work
		} else if ( num_read < 1 ) {
			printf( "missing value, read %d\n", num_read );
		}
	}
	printf( "parse_handle complete\n" );

	return 0;
}


/* main
 *
 */
int main ( int argc, char **argv )
{

	FILE * fp;

	if ( argc == 2 ) {
		if ( !strcmp( argv[1], "-") )
			fp = stdin;
		else if ( !strcmp( argv[1], "help") ||
			  !strcmp( argv[1], "-h")   ||
			  !strcmp( argv[1], "--help") ) {
			return usage( argv[0] );
		}
		else {
			fp = fopen(argv[1], "r" );
			if ( !fp ) {
				printf( "E: could not open %s\n", argv[1] );
				usage( argv[0] );
				return 1;
			}
		}
	} else {
		// assume STDIN
		fp = stdin;
	}

	if ( parse_handle(fp) ) {
		printf( "E: parse failed\n");
	}

	if ( fp != stdin ) fclose( fp );
	return 0;
}
