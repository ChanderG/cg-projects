/*
 * Contains data structures and associated functions used in the projects.
 */
#ifndef DS_H
#define DS_H

#include<stdlib.h>

/* Point structure
 * Holds x,y,z coordinates of a point in 3D.
 */
typedef struct {
	int x;
	int y;
	int z;
} Point;

/* 2d Point structure
 * Holds x,y coordinates of a point in 2D.
 */
typedef struct {
	int x;
	int y;
} Point2D;

/*
 * convert 2d point to 3d
 * Input -- a point2d
 * Output -- corr Point
 */
Point get3dPointFrom2d(Point2D p);

/*
 * Convert 3d point to 2d.
 * Input -- a Point
 * Output -- corr Point2D
 */
Point2D get2dPointFrom3d(Point p);

/*
 * Convert array of Point2D to array of Points
 * Input -- array of Point2D
 *          size of said array
 * Output -- array of Points of same size
 */
Point* convert2dPointArrayTo3d(Point2D* pts2, size_t len);

/*
 * Convert array of Points to array of Point2Ds
 * Input -- array of Point
 *          size of said array
 * Output -- array of Point2Ds of same size
 */
Point2D* convert3dPointArrayTo2d(Point* pts3, size_t len);

/*
 * Return a new list of Point2D, by appending extra to main.
 * Length of new list is len_main + len_extra
 */
Point2D* append2DPointList(Point2D* main, size_t len_main, Point2D* extra, size_t len_extra);

/*
 * Wrapper on append2DPointList that additionally cleans up input array.
 */
Point2D* append2DPointListWithCleanup(Point2D* main, size_t len_main, Point2D* extra, size_t len_extra);

#endif
