/*
 * Functions etc pertaining to 3d triangle creation.
 */

#ifndef TRIANGLE3D_H
#define TRIANGLE3D_H

#include<stdio.h>

#include "../common/common.h"
#include "../line/line.h"
#include "triangle2d.h"

/*
 * Create 3d triangle -- get points in/on a 3d triangle.
 * Input -- the 3 corners of a triangle 
 *          a length variable
 * Ouput -- returns an array of points
 *          populates len variable with length of said array
 */
Point* getTriangle3dPoints(Point a, Point b, Point c, size_t* len);

/*
 * Draw a 3d Triangle.
 * Input -- the 3 corners of a triangle 
 * Output -- creates the output.obj file required.
 */
void draw3dTriangle(Point a, Point b, Point c);

#endif 
