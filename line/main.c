/*
 * 3d Digital Line Segment.
 */

#include"main.h"

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
 * 
 */
Point *draw3DLine(Point s, Point e, size_t *len){

	int x,y,z;
	x = s.x;
	y = s.y;
	z = s.z;	

	int dx, dy, dz;
	dx = e.x - s.x;
	dy = e.y - s.y;
	dz = e.z - s.z;

	/* Ternary flag to handle swaps to handle different ranges of slopes.
	 * 0 -- no swap
	 * 1 -- x,y swapped
	 * 2 -- x,z swapped
	 */
	int swap_flag = 0;
	int temp;
	if((abs(dx) >= abs(dy)) && (abs(dx) >= abs(dz))){
	    swap_flag = 0;
	}
	else if((abs(dy) >= abs(dx)) && (abs(dy) >= abs(dz))){
		swap_flag = 1;
		// SWAP here all occurences of x and y
		temp = x;
		x = y;
		y = temp;

		temp = dx;
		dx = dy;
		dy = temp;

		temp = e.x;
		e.x = e.y;
		e.y = temp;
	}
	else{
		swap_flag = 2;
		// SWAP here all occurences of x and z
		temp = x;
		x = z;
		z = temp;

		temp = dx;
		dx = dz;
		dz = temp;

		temp = e.x;
		e.x = e.z;
		e.z = temp;
	}

	Point *pts;
	int nos = abs(dx) + 1;  //TODO: Calculate based on largest delta.
	pts = malloc(nos*sizeof(Point));
	int count = 0;

	//Decision functions
	int fxy = 2*abs(dy) - abs(dx);
	int fxz = 2*abs(dz) - abs(dx);

	do {
	    // Actual selection of point
		// Selects point reached in prev loop -- first point the first time
		// Reverse swap before point selection
		if (swap_flag == 0){
			pts[count] = (Point){ .x = x, .y = y, .z = z};
		}
		else if (swap_flag == 1){
			pts[count] = (Point){ .x = y, .y = x, .z = z};
		}
		else if (swap_flag == 2){
			pts[count] = (Point){ .x = z, .y = y, .z = x};
		}
		else{
			printf("ERROR: Unknown swap. Contact the programmer.\n");
			exit(0);
		}
		count++;

		// reached the end
		if (abs(x) == abs(e.x)) break;

		if (dx >= 0) x++;
		else x--;

		if (fxy > 0){
			if(dy >= 0) y++;
			else y--;
			fxy += 2*(abs(dy) - abs(dx));
		}
		else{
			fxy += 2*abs(dy);
		}

		if(fxz > 0){
			if(dz >= 0) z++;
			else z--;
			fxz += 2*(abs(dz) - abs(dx));
		}
		else{
			fxz += 2*abs(dz);
		}

	}while(1);

	*len = count;  
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

	createVoxelImage(pts, len);

	printf("Check output file.");
	printf("\n");
}
