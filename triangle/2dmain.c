/*
 * 2d Triangle runner
 */

#include "2dmain.h"

/*
 * INPUT:
 * 3 2d points in form:
 * Ax, Ay
 * Bx, By
 * Cx, Cy
 * OUPUT:
 * Points consisting of the traingle itself. 
 * Creates a "output.obj" file that draws unit cubes around these points. 
 */
void main(int argc, char* argv[]){
	printf("2d Triangle runner:\n");
	printf("No of args: %d\n", argc - 1);	
	if (argc != 7){
		// show help message and exit.
		printf("Invalid number of args.\n\n");
		printf("Need to give 6 integers, representing: \n\t A -- x, y\n\t B -- x, y\n\t C -- x, y\n");
		return;
	}

	// parse out, store and print the coordinates
	Point2D a, b, c;

	a.x = atoi(argv[1]);
	a.y = atoi(argv[2]);
	b.x = atoi(argv[3]);
	b.y = atoi(argv[4]);
	c.x = atoi(argv[5]);
	c.y = atoi(argv[6]);

	printf("Input: \na -- (%d, %d) b -- (%d, %d) c -- (%d, %d)\n\n", a.x, a.y, b.x, b.y, c.x, c.y );

	draw2dTriangle(a, b, c);
	printf("Check output.obj file created.\n");
}
