/*
 * Functions etc pertaining to creating lines.
 */

#ifndef LINE_H
#define LINE_H

#include"../common/common.h"

/*
 * get point2ds lying on line between a and b 
 * Input --
 *  a, b -- Point2Ds representing endpoints
 *  len  -- size_t to store length
 * Output --
 *  array of point2ds
 *  length of said array
 */
Point2D* getLine2dPoints(Point2D a, Point2D b, size_t* len);

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
Point *getLine3dPoints(Point s, Point e, size_t *len);

#endif
