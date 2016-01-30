/*
 * Contains data structures and associated functions used in the projects.
 */

#include "ds.h"

/*
 * convert 2d point to 3d
 * Input -- a point2d
 * Output -- corr Point
 */
Point get3dPointFrom2d(Point2D p){
  // simply pad z as 0
  Point p3;
  p3.x = p.x;
  p3.y = p.y;
  p3.z = 0;
  return p3;
}

/*
 * Convert 3d point to 2d.
 * Input -- a Point
 * Output -- corr Point2D
 */
Point2D get2dPointFrom3d(Point p){
  // simply ignore z
  Point2D p2;
  p2.x = p.x;
  p2.y = p.y;
  return p2;
}

/*
 * Convert array of Point2D to array of Points
 * Input -- array of Point2D
 *          size of said array
 * Output -- array of Points of same size
 */
Point* convert2dPointArrayTo3d(Point2D* pts2, size_t len){
  Point* pts3 = malloc(len*sizeof(Point));

  for (int i=0;i < len;i++){
	pts3[i] = get3dPointFrom2d(pts2[i]);
  }

  return pts3;
}

/*
 * Convert array of Points to array of Point2Ds
 * Input -- array of Point
 *          size of said array
 * Output -- array of Point2Ds of same size
 */
Point2D* convert3dPointArrayTo2d(Point* pts3, size_t len){
  Point2D* pts2 = malloc(len*sizeof(Point2D));

  for (int i=0;i < len;i++){
	pts2[i] = get2dPointFrom3d(pts3[i]);
  }

  return pts2;
}

/*
 * Return a new list of Point2D, by appending extra to main.
 * Length of new list is len_main + len_extra
 */
Point2D* append2DPointList(Point2D* main, size_t len_main, Point2D* extra, size_t len_extra){

  // create new list
  Point2D* new_list = malloc((len_main + len_extra)*sizeof(Point2D));

  int k = 0;
  while(k < len_main + len_extra){
	if(k < len_main){
	  // add main items
	  new_list[k] = main[k];
	}
	else{
	  // add extra items
	  new_list[k] = extra[k-len_main];
	}
	k++;
  }

  return new_list;
}
