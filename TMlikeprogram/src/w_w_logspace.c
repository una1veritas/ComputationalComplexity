/*
 ============================================================================
 Name        : w_w_logspace.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	printf("Hello. '%s'\n",argv[1]);

	char * h = argv[1];
	unsigned int cnt;

	cnt = 0;
loop:
	h += cnt;
	if ( *h == '0' ) {
		while( *h++ != '#' ) ;
		h += cnt;
		if ( *h != '0' )
			goto reject;
	} else if (*h == '1' ) {
		while( *h++ != '#' )
		h += cnt;
		if ( *h != '1' )
			goto reject;
	} else if ( *h == '#' ) {
		h += cnt;
		if ( *h == ' ' )
			goto accept;
		goto reject;
	}
	while ( *h-- != ' ' )
	++h;
	cnt++;
	goto loop;

accept:
	printf("accepted.");
	return 0;

reject:
	printf("rejected.\n");
	printf("cnt = %d\n",cnt);
	return 1;
}
