#include<stdio.h>
#include<stdlib.h>

/* Point structure
 * Holds x,y,z coordinates of a point in 3D.
 */
typedef struct {
	int x;
	int y;
	int z;
} Point;

/* draw3DLine
 * INPUT:
 * ========
 * s -- starting Point 
 * e -- ending Point 
 * len -- caller store for length of return list
 *
 * OUTPUT:
 * ========
 * array of Point's, length stored in len
 */
Point *draw3DLine(Point s, Point e, size_t *len){
	Point *pts;
	int nos = 10;  //TODO: Calculate based on largest delta.
	pts = malloc(nos*sizeof(Point));
	// For now: simply store start and end points
	pts[0] = s;
	pts[1] = e;
	*len = 2;  // TODO: change to value calculated from actual number of points
	return pts;
}

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
	Point s;
	Point e;

	s.x = atoi(argv[1]);
	s.y = atoi(argv[2]);
	s.z = atoi(argv[3]);
	e.x = atoi(argv[4]);
	e.y = atoi(argv[5]);
	e.z = atoi(argv[6]);

	printf("Input: \nS -- (%d, %d, %d) E -- (%d, %d, %d)\n\n", s.x, s.y, s.z, e.x, e.y, e.z);
	// input extraction done

	// get points on the 3d segment and print results
	size_t len;
	Point *pts = draw3DLine(s, e, &len);

	// check for error in function result
	if (pts == NULL){
		// report error
		printf("ERROR. Found no points on line. Try again.\n");
		return;
    }

	printf("Points on the 3d DSS: \n");
	for(size_t i = 0; i < len; i++){
		printf("(%d, %d, %d)\n", pts[i].x, pts[i].y, pts[i].z);
	}
	printf("\n");

	printf("WIP");
	printf("\n");
}
