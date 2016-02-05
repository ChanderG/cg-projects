/*
 * Functions etc pertaining to 3d triangle creation.
 */

#include "triangle3d.h"

/*
 * Helpers
 */

/*
 * Return minimum of 3 numbers.
 */
int min3(int a, int b, int c){
  int m = a;
  if (b < m)
    m = b;
  if (c < m)
    m = c;
  return m;
}

/*
 * Return maximum of 3 numbers.
 */
int max3(int a, int b, int c){
  int m = a;
  if (b > m)
    m = b;
  if (c > m)
    m = c;
  return m;
}

/*
 * Calculate plane equation along axis X.
 */
int planeCalcX(int A, int B, int C, int D, Point p, int pred){
  int val = 2*(A*pred + B*p.y + C*p.z + D);
  return (-1*abs(A) < val) && (val < abs(A));
}

/*
 * Calculate plane equation along axis Y.
 */
int planeCalcY(int A, int B, int C, int D, Point p, int pred){
  int val = 2*(A*p.x + B*pred + C*p.z + D);
  return (-1*abs(B) < val) && (val < abs(B));
}

/*
 * Calculate plane equation along axis Z.
 */
int planeCalcZ(int A, int B, int C, int D, Point p, int pred){
  int val = 2*(A*p.x + B*p.y + C*pred + D);
  return (-1*abs(C) < val) && (val < abs(C));
}

/*
 * Create 3d triangle -- get points in/on a 3d triangle.
 * Input -- the 3 corners of a triangle 
 *          a length variable
 * Ouput -- returns an array of points
 *          populates len variable with length of said array
 */
Point* getTriangle3dPoints(Point a, Point b, Point c, size_t* len){

  logm("getTriangle3dPoints", "a (%d, %d, %d) b (%d, %d, %d) c (%d, %d, %d)", a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);
  
  // first calculate coefficients of plane
  int A, B, C, D;

  A = ((b.y - a.y)*(c.z - a.z) - (b.z - a.z)*(c.y - a.y));
  B = ((b.z - a.z)*(c.x - a.x) - (c.z - a.z)*(b.x - a.x));
  C = ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x));

  // substituting a into equation to obtain D as well
  D = 0 - A*a.x - B*a.y - C*a.z;

  logm("getTriangle3dPoints", "Plane params: A = %d, B = %d, C = %d, D = %d", A, B, C, D);

  if ((A == 0) && (B == 0) && (C == 0)){
	// in case all three points line on a straight line
    // brute force: simply connect all three points
	
	// output variables
	Point* pts;

	// edge variables
	Point *ab, *ac, *bc;
	size_t len_ab, len_ac, len_bc;

	ab = getLine3dPoints(a, b, &len_ab);
	ac = getLine3dPoints(a, c, &len_ac);
	bc = getLine3dPoints(b, c, &len_bc);

	pts = append3DPointList(ab, len_ab, ac, len_ac);
	pts = append3DPointList(pts, len_ab + len_ac, bc, len_bc);

	*len = len_ab + len_ac + len_bc;
	return pts;
  }

  Point2D p, q, r;
  axis_marker axis;

  if ((abs(A) >= abs(B)) && (abs(A) >= abs(C))){
	// A is largest of coefficients
    axis = X;	
    logm("getTriangle3dPoints", "Chosen X as axis.");
  }
  else if ((abs(B) >= abs(A)) && (abs(B) >= abs(C))){
	// B is largest of coefficients
    axis = Y;	
    logm("getTriangle3dPoints", "Chosen Y as axis.");
  }
  else{
	// C is largest of coefficients
    axis = Z;	
    logm("getTriangle3dPoints", "Chosen Z as axis.");
  }

  p = get2dPointFrom3dWithMapping(a, axis);
  q = get2dPointFrom3dWithMapping(b, axis);
  r = get2dPointFrom3dWithMapping(c, axis);
  logm("getTriangle3dPoints", "p (%d, %d), q(%d, %d), r(%d, %d)", p.x, p.y, q.x, q.y, r.x, r.y);

  // now draw triangle in 2d
  size_t len_t2d;
  Point2D* t2d_2d = getTriangle2dPoints(p, q, r, &len_t2d);
  // we now have all points in 2d
  
  // do a raw conversion to 3d
  Point* t = convert2dPointArrayTo3dWithMapping(t2d_2d, len_t2d, axis);

  /*
   * Pure int technique
   * History relying on brute-force:
   * Use history. If fails, resort to brute-force between end points.
   */
  int prev_other;  //prev found value of the other coordinate.
  int max_other, min_other; // range of other 

  // set up range and initital prediction of the 3rd coordinate
  if( axis == X ){
    min_other = min3(a.x, b.x, c.x) - 1;
    max_other = max3(a.x, b.x, c.x) + 1;
    prev_other = min_other;
  }
  if( axis == Y ){
    min_other = min3(a.y, b.y, c.y) - 1;
    max_other = max3(a.y, b.y, c.y) + 1;
    prev_other = min_other;
  }
  if( axis == Z ){
    min_other = min3(a.z, b.z, c.z) - 1;
    max_other = max3(a.z, b.z, c.z) + 1;
    prev_other = min_other;
  }

  // boolean if point is done or not
  int point_done = 0;
  // history-brute for all points
  for(int i=0; i< len_t2d; i++){
    point_done = 0;
	// were other axis -- X
	if (axis == X){
	  // try out delta from prev
      for (int j = -1; j!= 2;j++){
		if (planeCalcX(A, B, C, D, t[i], prev_other + j) == 1){
		  // if this works out
		  prev_other = prev_other + j;
		  t[i].x = prev_other;
		  point_done = 1;
		  logm("getTriangle3dPoints", "Point %d/%d handled by history.", i, len_t2d);
		  break;
		}
	  }
	
	  // check if history worked out
	  if (point_done == 1)
		continue;

	  // history failed.
	  // Brute force.
      for (int j = min_other; j!= max_other + 1;j++){
		if (planeCalcX(A, B, C, D, t[i],j) == 1){
		  // if this works out
		  prev_other = j;
		  t[i].x = prev_other;
		  point_done = 1;
		  logm("getTriangle3dPoints", "Point %d/%d handled by brute-force.", i, len_t2d);
		  break;
		}
	  }
	}

	// were other axis -- Y
	if (axis == Y){
	  // try out delta from prev
      for (int j = -1; j!= 2;j++){
		if (planeCalcY(A, B, C, D, t[i], prev_other + j) == 1){
		  // if this works out
		  prev_other = prev_other + j;
		  t[i].y = prev_other;
		  point_done = 1;
		  logm("getTriangle3dPoints", "Point %d/%d handled by history.", i, len_t2d);
		  break;
		}
	  }

	  // check if history worked out
	  if (point_done == 1)
		continue;

	  // history failed.
	  // Brute force.
      for (int j = min_other; j!= max_other + 1;j++){
		if (planeCalcY(A, B, C, D, t[i],j) == 1){
		  // if this works out
		  prev_other = j;
		  t[i].y = prev_other;
		  point_done = 1;
		  logm("getTriangle3dPoints", "Point %d/%d handled by brute-force.", i, len_t2d);
		  break;
		}
	  }
	}

	// were other axis -- Z
	if (axis == Z){
	  // try out delta from prev
      for (int j = -1; j!= 2;j++){
		if (planeCalcZ(A, B, C, D, t[i], prev_other + j) == 1){
		  // if this works out
		  prev_other = prev_other + j;
		  t[i].z = prev_other;
		  point_done = 1;
		  logm("getTriangle3dPoints", "Point %d/%d handled by history.", i, len_t2d);
		  break;
		}
	  }

	  // check if history worked out
	  if (point_done == 1)
		continue;

	  // history failed.
	  // Brute force.
      for (int j = min_other; j!= max_other + 1;j++){
		if (planeCalcZ(A, B, C, D, t[i],j) == 1){
		  // if this works out
		  prev_other = j;
		  t[i].z = prev_other;
		  point_done = 1;
		  logm("getTriangle3dPoints", "Point %d/%d handled by brute-force.", i, len_t2d);
		  break;
		}
	  }
	}

  }
  /*
   * End of history-brute technique.
   */

  /*
   * Floating point technique.
  float l, u, temp;
  // loop over the points and add the missing coordinate
  for(int i=0; i< len_t2d; i++){
	if (axis == X){
	  // fill in other 2 variables
	  l = 1.0*(-1*abs(A) -2*B*t[i].y -2*C*t[i].z -2*D)/(2*A);
	  u = 1.0*(abs(A) - 2*B*t[i].y - 2*C*t[i].z - 2*D)/(2*A);

	  // ensure larger and lower
	  if (l > u){
		temp = l;
		l = u;
		u = temp;
	  }

	  logm("getTriangle3dPoints", "i: %d, l=%0.2f u=%0.2f", i, l, u);

	  // set to floor of u; if the this is negeative, subtract 1 from it 
	  t[i].x = (int)((u < 0)?u-1:u);
	  logm("getTriangle3dPoints", "Choose -- %d", t[i].x);
	}
	if (axis == Y){
	  l = 1.0*(-1*abs(B) - 2*A*t[i].x - 2*C*t[i].z - 2*D)/(2*B);
	  u = 1.0*(abs(B) - 2*A*t[i].x - 2*C*t[i].z - 2*D)/(2*B);

	  // ensure larger and lower
	  if (l > u){
		temp = l;
		l = u;
		u = temp;
	  }

	  logm("getTriangle3dPoints", "i: %d, l=%0.2f u=%0.2f", i, l, u);

	  // set to floor of u; if the this is negeative, subtract 1 from it 
	  t[i].y = (int)((u < 0)?u-1:u);
	  logm("getTriangle3dPoints", "Choose -- %d", t[i].y);
	}
	if (axis == Z){
	  l = 1.0*(-1*abs(C) - 2*A*t[i].x - 2*B*t[i].y - 2*D)/(2*C);
	  u = 1.0*(abs(C) - 2*A*t[i].x - 2*B*t[i].y - 2*D)/(2*C);

	  // ensure larger and lower
	  if (l > u){
		temp = l;
		l = u;
		u = temp;
	  }

	  logm("getTriangle3dPoints", "i: %d, l=%0.2f u=%0.2f", i, l, u);

	  // set to floor of u; if the this is negeative, subtract 1 from it 
	  t[i].z = (int)((u < 0)?u-1:u);
	  logm("getTriangle3dPoints", "Choose -- %d", t[i].z);
	}
  }
  */

  logm("getTriangle3dPoints", "Completed points calculation. No. of points: %d", len_t2d);

  *len = len_t2d;
  return t;
}

/*
 * Draw a 3d Triangle.
 * Input -- the 3 corners of a triangle 
 * Output -- creates the output.obj file required.
 */
void draw3dTriangle(Point a, Point b, Point c){

  // create the triangle -- ie get the points on the 3d triangle
  size_t len;
  Point *pts = getTriangle3dPoints(a, b, c, &len);

  // draw the 3d points
  createVoxelImage(pts, len);
}

