#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	char * p = argv[1];
	char mem[strlen(argv[1])];
	for(int i = 0; i < strlen(argv[1]); ++i)
		mem[i] = (char) 0;
	char * w = mem + 1;

	if ( *p == 'a' or *p == 'b' ) {
		*w++ = *p++;
	} else
		return -1;

	while ( *p == 'a' or *p == 'b' ) {
		*w++ = *p++;
	}
	if ( *p == '#' )
		w--;
	else
		return -1;
	while ( *w-- ) {}

	return 0;
}
