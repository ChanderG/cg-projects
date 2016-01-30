/*
 * Functions etc pertaining to 2d triangle creation.
 */

#include"triangle2d.h"

/*
 * Create 2d triangle -- get points in/on a 2d triangle.
 * Input -- the 3 corners of a triangle 
 *          a length variable
 * Ouput -- returns an array of 2D points
 *          populates len variable with length of said array
 */
Point2D* getTriangle2dPoints(Point2D a, Point2D b, Point2D c, size_t* len){
  /*
   * operating procedure:
   * We scan from bottom to top, left to right.
   * TO that end, need to create 3 different aliases p, q, r to refer to these points.
   * However, p is going to refer to bootom most point.
   * q to the left of the remaining 2, r the right one.
   */

  Point2D p, q, r, temp;
  Point2D *pq, *pr, *qr;
  size_t len_pq, len_pr, len_qr;
  // start with a dummy assignment
  p = a;
  q = b;
  r = c;

  if (q.y < p.y){
	// swap p and q 
	temp = p;
	p = q;
	q = temp;
  }
  if (r.y < p.y){
	// swap p and r
	temp = p;
	p = r;
	r = temp;
  }

  if (q.x > r.x){
	// if q is to the right of r, swap q and r
	temp = q;
	q = r;
	r = temp;
  }

  logm("getTriangle2dPoints", "p -- (%d, %d)", p.x, p.y);
  logm("getTriangle2dPoints", "q -- (%d, %d)", q.x, q.y);
  logm("getTriangle2dPoints", "r -- (%d, %d)", r.x, r.y);

  pq = getLine2dPoints(p, q, &len_pq);
  pr = getLine2dPoints(p, r, &len_pr);
  qr = getLine2dPoints(q, r, &len_qr);

  // need to create the triangle itself
  Point2D* t_pts = NULL;
  size_t len_t_pts = 0;

  // store points on current line segment
  Point2D* curr_seg;
  size_t len_curr_seg;

  // representing index of current point on the 2 lines
  int i,j;
  i = 0; j = 0;

  int k = p.y; // represents y coordinate of scan line

  // to first edge completion
  while ((k <= pq[len_pq - 1].y) && (k <= pr[len_pr - 1].y)){
	// get point on that y level
	while(pq[i].y != k) i++;
	while(pr[j].y != k) j++;
	// get points from this end to that
    curr_seg = getLine2dPoints(pq[i], pr[j], &len_curr_seg);
	// add to our triangle set
	t_pts = append2DPointListWithCleanup(t_pts, len_t_pts, curr_seg, len_curr_seg);
	len_t_pts += len_curr_seg;
	logm("getTriangle2dPoints", "finished scanning line (phase 1) y = %d", k);
	k++;
  }

  // second phase
  if (k <= pq[len_pq - 1].y){
	// will only be activated if pq is still active but pr is done
	// so, start with qr, more specifically rq
	
	// repurpose j to use for rq
	j = len_qr - 1;
	
    while(k <= pq[len_pq - 1].y){
	  // get point on that y level
	  while(pq[i].y != k) i++;
	  while(qr[j].y != k) j--;

	  curr_seg = getLine2dPoints(pq[i], qr[j], &len_curr_seg);
	  t_pts = append2DPointListWithCleanup(t_pts, len_t_pts, curr_seg, len_curr_seg);
	  len_t_pts += len_curr_seg;
	  logm("getTriangle2dPoints", "finished scanning line (phase 2) y = %d", k);
	  k++;
	}
  }

  if (k <= pr[len_pr - 1].y){
	// will be activated if pr is still active but pq is done
	// so, start with qr
	
	// repurpose j to use for rq
	i = 0;

	while(k <= pr[len_pr - 1].y){
	  // get point on that y level
	  while(qr[i].y != k) i++;
	  while(pr[j].y != k) j++;

	  curr_seg = getLine2dPoints(qr[i], pr[j], &len_curr_seg);
	  t_pts = append2DPointListWithCleanup(t_pts, len_t_pts, curr_seg, len_curr_seg);
	  len_t_pts += len_curr_seg;
	  logm("getTriangle2dPoints", "finished scanning line (phase 2) y = %d", k);
	  k++;
	}
  }

  // add borders for good measure
  // should not be required, strictly required, correct later
  // added to counter a particular corner case: where q/r lie on same y axis as p
  t_pts = append2DPointList(t_pts, len_t_pts, pq, len_pq);
  len_t_pts += len_pq;
  t_pts = append2DPointList(t_pts, len_t_pts, pr, len_pr);
  len_t_pts += len_pr;
  t_pts = append2DPointList(t_pts, len_t_pts, qr, len_qr);
  len_t_pts += len_qr;
 
  *len = len_t_pts;
  return t_pts;
}

/*
 * Draw a 2d Triangle.
 * Input -- the 3 corners of a triangle 
 * Output -- creates the output.obj file required.
 */
void draw2dTriangle(Point2D a, Point2D b, Point2D c){

  // create the triangle -- ie get the points on the 2d triangle
  size_t len;
  Point2D *pts = getTriangle2dPoints(a, b, c, &len);

  // draw the 2d points
  createVoxelImage2D(pts, len);
}
