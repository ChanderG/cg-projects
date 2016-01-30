/*
 * Functions etc pertaining to 2d triangle creation.
 */

#include"triangle2d.h"

/*
 * Create 2d triangle -- get points in/on a 2d triangle.
 * Input -- the 3 corners of a triangle 
 *          a length variable
 * Ouput -- returns an array of 2D points
 *          populates len variable with length of said array
 */
Point2D* getTriangle2dPoints(Point2D a, Point2D b, Point2D c, size_t* len){
  
  Point2D *ab, *ac, *bc;
  size_t len_ab, len_ac, len_bc;

  ab = getLine2dPoints(a, b, &len_ab);
  ac = getLine2dPoints(a, c, &len_ac);
  bc = getLine2dPoints(b, c, &len_bc);

  /*
   * operating procedure:
   * We scan from bottom to top, left to right.
   * TO that end, need to create 3 different aliases p, q, r to refer to these points.
   * However, p is going to refer to bootom most point.
   * q to the left of the remaining 2, r the right one.
   */

  Point2D p, q, r, temp;
  // start with a dummy assignment
  p = a;
  q = b;
  r = c;

  if (q.y < p.y){
	// swap p and q 
	temp = p;
	p = q;
	q = temp;
  }
  if (r.y < p.y){
	// swap p and r
	temp = p;
	p = r;
	r = temp;
  }

  if (q.x > r.x){
	// if q is to the right of r, swap q and r
	temp = q;
	q = r;
	r = temp;
  }

  logm("getTriangle2dPoints", "p -- (%d, %d)", p.x, p.y);
  logm("getTriangle2dPoints", "q -- (%d, %d)", q.x, q.y);
  logm("getTriangle2dPoints", "r -- (%d, %d)", r.x, r.y);

  // just for sample, draw the triangle border
  Point2D* borders;
  borders = append2DPointList(ab, len_ab, ac, len_ac);
  borders = append2DPointList(borders, len_ab + len_ac, bc, len_bc);

  *len = len_ab + len_ac + len_bc;
  return borders;

  /*
  // for now return the corners alone
  Point2D *pts;
  int nos = 3;
  pts = malloc(nos*sizeof(Point2D));
  pts[0] = a;
  pts[1] = b;
  pts[2] = c;
  *len = 3;
  return pts;
  */
}

/*
 * Draw a 2d Triangle.
 * Input -- the 3 corners of a triangle 
 * Output -- creates the output.obj file required.
 */
void draw2dTriangle(Point2D a, Point2D b, Point2D c){

  // create the triangle -- ie get the points on the 2d triangle
  size_t len;
  Point2D *pts = getTriangle2dPoints(a, b, c, &len);

  // draw the 2d points
  createVoxelImage2D(pts, len);
}
