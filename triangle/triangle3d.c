/*
 * Functions etc pertaining to 3d triangle creation.
 */

#include "triangle3d.h"

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
  
  // add the missing coordinate

  // for now, just add endpoints
  Point* pts = malloc(3*sizeof(Point));
  pts[0] = a;
  pts[1] = b;
  pts[2] = c;

  *len = 3;
  return pts;
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

