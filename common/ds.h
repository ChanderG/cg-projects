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
 * Axis marker.
 * One of 0, 1, 2
 * 0 -- represents z axis
 * 1 -- represents y axis
 * 2 -- represents x axis
 */
typedef enum {Z, Y, X} axis_marker;

/*
 * convert 2d point to 3d
 * Wrapper on get3dPointFrom2dWithMapping
 * Input -- a point2d
 * Output -- corr Point
 */
Point get3dPointFrom2d(Point2D p);

/*
 * Convert 3d point to 2d.
 * Wrapper on get2dPointFrom3dWithMapping
 * Input -- a Point
 * Output -- corr Point2D
 */
Point2D get2dPointFrom3d(Point p);

/*
 * Convert array of Point2D to array of Points
 * Wrapper on convert2dPointArrayTo3dWithMapping with axis_marker Z
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
 * Return a new list of Point, by appending extra to main.
 * Length of new list is len_main + len_extra
 */
Point* append3DPointList(Point* main, size_t len_main, Point* extra, size_t len_extra);

/*
 * Wrapper on append2DPointList that additionally cleans up input array.
 */
Point2D* append2DPointListWithCleanup(Point2D* main, size_t len_main, Point2D* extra, size_t len_extra);

/*
 * convert 2d point to 3d with mapping
 * Input -- a point2d, an axis to drop/take
 * Output -- corr Point
 */
Point get3dPointFrom2dWithMapping(Point2D p, axis_marker axis);

/*
 * Convert 3d point to 2d with mapping
 * Input -- a Point, an axis to drop/take
 * Output -- corr Point2D
 */
Point2D get2dPointFrom3dWithMapping(Point p, axis_marker axis);

/*
 * Convert array of Point2D to array of Points given axes of mapping
 * Input -- array of Point2D
 *          size of said array
 *          axes of mapping as an axis_marker
 * Output -- array of Points of same size
 */
Point* convert2dPointArrayTo3dWithMapping(Point2D* pts2, size_t len, axis_marker axis);

#endif
