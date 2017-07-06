/*
 * maker.c
 *
 *  Created on. 2017/07/05
 *      Author. sin
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	unsigned int a, i;

	printf("stb.0.0 * _  stb.0.0 N 0 N\n");

	printf("stb.0.0 L 0  ldi.0.0 R 0 N\n");

	for (a = 0; a < 16; a++) {
		printf("ldi.0.0 %X 0  stb.%X.0 R 0 N\n", a, a);
	}

	for (a = 0; a < 16; a++) {
		printf("stb.%X.0 A 0  adi.%X.0 R 0 N\n", a, a);
	}

	for (a = 0; a < 16; a++) {
		for (i = 0; i < 16; i++ ) {
			printf("adi.%X.0 %X 0  stb.%X.%X R 0 N\n", a, i, (a+i)&0xf, ( (a+i)>>4&1) );
		}
	}

	for (a = 0; a < 16; a++) {
		printf("stb.%X.0 P 0  stb.%X.0 R %x R\n", a, a, a);
		printf("stb.%X.1 P 0  stb.%X.1 R %x R\n", a, a, a);
	}

	return EXIT_SUCCESS;
}
