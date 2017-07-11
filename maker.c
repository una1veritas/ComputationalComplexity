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

	/* Read only mem (input), A*/

	/* reset ... clear registers and rewind PC */
	printf("#reset action\n");
	printf("reset _ * 	stb.0 _ R 0 N\n");
	for(i = 0; i < 10; i++)
		printf("reset %d * 	reset %d L 0 N\n", i, i);

	/* fetch instruction */

	printf("#halt\n");
	printf("stb.0 _ * 	halt.0 _ N 0 N\n");
	printf("stb.1 _ * 	halt.0 _ N 0 N\n");
	printf("halt.0 * * 	halt.0 * N * N\n");

	printf("#load immediate\n");
	printf("stb.0 l * 	ldi.0 l R 0 N\n");
	printf("stb.1 l * 	ldi.0 l R 0 N\n");
	for(i = 0; i < 10; i++)
		printf("ldi.0 %d * 	stb.0 %d R %d N\n", i, i, i);

	printf("#add immediate with carry\n");
	printf("stb.0 a * 	adc.0 a R * N\n");
	for(a = 0; a < 10; a++)
		for(i = 0; i < 10; i++)
			printf("adc.0 %d %d 	stb.%d %d R %d N\n", i, i, a, (i+a > 9), (i+a)%10);

	return EXIT_SUCCESS;
}
