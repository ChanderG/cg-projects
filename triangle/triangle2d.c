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
