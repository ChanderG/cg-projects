/*
 * Functions dealing with creation and drawing of voxels.
 */
#ifndef VOXELS_H
#define VOXELS_H

#include"ds.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* returnVoxelCube
 * Generates obj lines for a single cube.
 * INPUT:
 * ========
 * center -- Point, center of cube
 * offset -- to share offset of vertices positioning in the output file 
 *
 * OUTPUT:
 * ========
 * char string consisting all lines corr to this cube
 */
char* returnVoxelCube(Point center, int* offset);

/* createVoxelImage
 * Creates voxel boxes around points given.
 * INPUT:
 * ========
 * pts -- array of Points
 * len --length of points array
 *
 * OUTPUT:
 * ========
 * Creates a .obj file named "output.obj" 
 */
void createVoxelImage(Point* pts, size_t len);

/* createVoxelImage2D
 * Creates voxel boxes around points given.
 * Simply a wrapper over createVoxelImage
 * INPUT:
 * ========
 * pts -- array of Point2D
 * len --length of points array
 *
 * OUTPUT:
 * ========
 * Creates a .obj file named "output.obj" 
 */
void createVoxelImage2D(Point2D* pts, size_t len);

#endif
