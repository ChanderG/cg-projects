/*
 * Functions etc pertaining to 2d triangle creation.
 */

#ifndef TRIANGLE2D_H
#define TRIANGLE2D_H

#include<stdio.h>

#include "../common/common.h"
#include "../line/line.h"

/*
 * Create 2d triangle -- get points in/on a 2d triangle.
 * Input -- the 3 corners of a triangle 
 *          a length variable
 * Ouput -- returns an array of 2D points
 *          populates len variable with length of said array
 */
Point2D* getTriangle2dPoints(Point2D a, Point2D b, Point2D c, size_t* len);

/*
 * Draw a 2d Triangle.
 * Input -- the 3 corners of a triangle 
 * Output -- creates the output.obj file required.
 */
void draw2dTriangle(Point2D a, Point2D b, Point2D c);

#endif 
