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

