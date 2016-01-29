/*
 * Functions etc pertaining to creating lines.
 */

#include"line.h"

/*
 * get point2ds lying on line between a and b 
 * Input --
 *  a, b -- Point2Ds representing endpoints
 *  len  -- size_t to store length
 * Output --
 *  array of point2ds
 *  length of said array
 */
Point2D* getLine2dPoints(Point2D a, Point2D b, size_t* len){
  // convert 2d points to 3d points, run 3d algorithm and reconvert points back

  // convert to 3d points
  Point s,e;
  s = get3dPointFrom2d(a);
  e = get3dPointFrom2d(b);

  // run 3d algorithm
  Point* pts;
  // use len itself

  pts = getLine3dPoints(s, e, len);

  // convert back to list of 2d points
  Point2D *pts2 = convert3dPointArrayTo2d(pts, *len);
  return pts2;
}  

/* getLine3dPoints
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
Point *getLine3dPoints(Point s, Point e, size_t *len){

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
