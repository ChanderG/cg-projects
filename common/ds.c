/*
 * Contains data structures and associated functions used in the projects.
 */

#include "ds.h"

/*
 * convert 2d point to 3d
 * Wrapper on get3dPointFrom2dWithMapping
 * Input -- a point2d
 * Output -- corr Point
 */
Point get3dPointFrom2d(Point2D p){
  // simply pad z as 0
  return get3dPointFrom2dWithMapping(p, Z);
}

/*
 * Convert 3d point to 2d.
 * Wrapper on get2dPointFrom3dWithMapping
 * Input -- a Point
 * Output -- corr Point2D
 */
Point2D get2dPointFrom3d(Point p){
  // simply ignore z
  return get2dPointFrom3dWithMapping(p, Z);
}

/*
 * Convert array of Point2D to array of Points
 * Wrapper on convert2dPointArrayTo3dWithMapping with axis_marker Z
 * Input -- array of Point2D
 *          size of said array
 * Output -- array of Points of same size
 */
Point* convert2dPointArrayTo3d(Point2D* pts2, size_t len){
  // call the more general function with axis_marker Z
  return convert2dPointArrayTo3dWithMapping(pts2, len, Z);
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

/*
 * Wrapper on append2DPointList that additionally cleans up input array.
 */
Point2D* append2DPointListWithCleanup(Point2D* main, size_t len_main, Point2D* extra, size_t len_extra){
  // simply call append2DPointList
  Point2D* ret_val = append2DPointList(main, len_main, extra, len_extra);

  // clean up inputs
  free(main);
  free(extra);

  return ret_val;
}

/*
 * convert 2d point to 3d with mapping
 * Input -- a point2d, an axis to drop/take
 * Output -- corr Point
 */
Point get3dPointFrom2dWithMapping(Point2D p, axis_marker axis){
  Point p3;
  if (axis == X){
	p3.x = 0;
	p3.y = p.x;
	p3.z = p.y;
  }
  else if (axis == Y){
	p3.x = p.x;
	p3.y = 0;
	p3.z = p.y;
  }
  else if (axis == Z){
	p3.x = p.x;
	p3.y = p.y;
	p3.z = 0;
  }
  else{
	// impossible
  }

  return p3;
}

/*
 * Convert 3d point to 2d with mapping
 * Input -- a Point, an axis to drop/take
 * Output -- corr Point2D
 */
Point2D get2dPointFrom3dWithMapping(Point p, axis_marker axis){
  Point2D p2;

  if (axis == X){
	p2.x = p.y;
	p2.y = p.z;
  }
  else if (axis == Y){
	p2.x = p.x;
	p2.y = p.z;
  }
  else if (axis == Z){
	p2.x = p.x;
	p2.y = p.y;
  }
  else{
	// impossible
  }

  return p2;
}

/*
 * Convert array of Point2D to array of Points given axes of mapping
 * Input -- array of Point2D
 *          size of said array
 *          axes of mapping as an axis_marker
 * Output -- array of Points of same size
 */
Point* convert2dPointArrayTo3dWithMapping(Point2D* pts2, size_t len, axis_marker axis){
  Point* pts3 = malloc(len*sizeof(Point));

  for (int i=0;i < len;i++){
	pts3[i] = get3dPointFrom2dWithMapping(pts2[i], axis);
  }

  return pts3;
}
