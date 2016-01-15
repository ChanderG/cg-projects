#include<stdio.h>

/* requires input as 
 * Sx, Sy, Sx
 * Ex, Ey, Ez
 * All 6 HAVE to be integers.
 * Any other number of args triggers a help message and exits.
 */
void main(int argc, char* argv[]){
	printf("No of args: %d\n", argc - 1);	
	if (argc != 7){
		// show help message and exit.
		printf("Invalid number of args.\n\n");
		printf("Need to give 6 integers, representing: \n\t S -- x, y, z\n\t E -- x, y, z\n");
		return;
	}

	// parse out, store and print the coordinates
	int sx, sy, sz;
	int ex, ey, ez;

	sx = atoi(argv[1]);
	sy = atoi(argv[2]);
	sz = atoi(argv[3]);
	ex = atoi(argv[4]);
	ey = atoi(argv[5]);
	ez = atoi(argv[6]);

	printf("Input: \nS -- (%d, %d, %d) E -- (%d, %d, %d)\n", sx, sy, sz, ex, ey, ez);

	printf("WIP");
	printf("\n");
}
