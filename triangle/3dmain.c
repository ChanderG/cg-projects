/*
 * 3d Triangle runner
 */

#include "3dmain.h"

/*
 * INPUT:
 * 3 3d points in form:
 * Ax, Ay, Az
 * Bx, By, Bz
 * Cx, Cy, Cz
 * OUPUT:
 * Points consisting of the traingle itself. 
 * Creates a "output.obj" file that draws unit cubes around these points. 
 */
void main(int argc, char* argv[]){
    logm("main", "Start program.");
	printf("3d Triangle runner:\n");
	printf("No of args: %d\n", argc - 1);	
	if (argc != 10){
		// show help message and exit.
		printf("Invalid number of args.\n\n");
		printf("Need to give 9 integers, representing: \n\t A -- x, y, z\n\t B -- x, y, z\n\t C -- x, y, z\n");
		return;
	}

	// parse out, store and print the coordinates
	Point a, b, c;

	a.x = atoi(argv[1]);
	a.y = atoi(argv[2]);
	a.z = atoi(argv[3]);
	b.x = atoi(argv[4]);
	b.y = atoi(argv[5]);
	b.z = atoi(argv[6]);
	c.x = atoi(argv[7]);
	c.y = atoi(argv[8]);
	c.z = atoi(argv[9]);

	printf("Input: \na -- (%d, %d, %d) b -- (%d, %d, %d) c -- (%d, %d, %d)\n\n", a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z );

	draw3dTriangle(a, b, c);
	printf("Check output.obj file created.\n");
	logm("main", "Main program ends.");
}
