// payout_engine.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "payout_engine.h"

#define LINE_BUF_SZ 1024

#define max_trans 100



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
	struct btc_trans trans[max_trans];
	long lSize;
	int num_read, num_trans = 0, ret;

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
		/* transaction_hash from_hash to_hash santoshi */
		if( fgets( buf, LINE_BUF_SZ, fp ) == NULL )
			printf( "E: buffer read failed\n" );

		if ( feof(fp) ) break;

		/* ignore comments */
		if( buf[0] == '#' ) {
			printf( "ignoring comment: %s\n", buf );
			continue;
		}

		num_read = sscanf( buf, "%65s%34s%34s%65s", 
			trans[num_trans].trans_hash, 
			trans[num_trans].from_addr, 
			trans[num_trans].to_addr, 
			trans[num_trans].satoshi );

		/* correctly read all values */
		if ( num_read == 4 ) {
			printf( "trans_hash: %s\nfrom_addr: %s\nto_addr: %s\nsatoshi: %s\n",
			trans[num_trans].trans_hash, 
                        trans[num_trans].from_addr, 
                        trans[num_trans].to_addr, 
                        trans[num_trans].satoshi );
			// TODO: work
		} else if ( num_read < 1 ) {
			printf( "missing value, read %d\n", num_read );
		} else {
			printf( "E: incomplete transaction, read %d values\n", num_read );
		}
		num_trans++;
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
