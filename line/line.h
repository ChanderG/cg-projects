/*
 * Functions etc pertaining to creating lines.
 */

#ifndef LINE_H
#define LINE_H

#include"../common/common.h"

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
