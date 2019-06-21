/*
 ============================================================================
 Name        : TMlikeprogram.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	const char * input = argv[1]+1;
	char * work[] = {
			"$         "
	};
	printf("input: '%s', work[0]: '%s' \n", input, work[0]);
	++work[0];


	state_copy:
	while ( *input == 'a' ) {
		*work[0] = *input;
		++work[0];
		++input;
	}
	if (*input != 'b')
		goto reject;

	state_rew:
	while ( *work[0] != '$' ) {
		--work[0];
	}
	++work[0];

	state_comp:
	while ( *work[0] == 'a' && *input == 'b') {
		++input;
		++work[0];
	}

	if (*work[0] == 'a' )
		goto reject;
	if (*input == 'b' )
		goto reject;

	accept:
	puts("accept.\n");
	printf("input: '%s', work[0]: '%s' \n", input, work[0]);
	return EXIT_SUCCESS;

	reject:
	puts("reject.\n");
	printf("input: '%s', work[0]: '%s' \n", input, work[0]);
	return EXIT_FAILURE;
}
