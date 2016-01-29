/*
 * Functions etc pertaining to 2d triangle creation.
 */

#ifndef TRIANGLE2D_H
#define TRIANGLE2D_H

#include<stdio.h>

#include "../common/common.h"

/*
 * Draw a 2d Triangle.
 * Input -- the 3 corners of a triangle 
 * Output -- creates the output.obj file required.
 */
void draw2dTriangle(Point2D a, Point2D b, Point2D c);

#endif 
