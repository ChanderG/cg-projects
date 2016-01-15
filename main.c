#include<stdio.h>
#include<stdlib.h>

/* Point structure
 * Holds x,y,z coordinates of a point in 3D.
 */
typedef struct {
	int x;
	int y;
	int z;
} Point;

/* draw3DLine
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
 * -----IMP-----
 * For now, ONLY works for first case lines. ie 0 <= dy <= dx; 0 <= dz <= dx.
 * -----IMP-----
 */
Point *draw3DLine(Point s, Point e, size_t *len){
	Point *pts;
	int nos = 100;  //TODO: Calculate based on largest delta.
	pts = malloc(nos*sizeof(Point));
	int count = 0;
    
	int x,y,z;
	x = s.x;
	y = s.y;
	z = s.z;	

	int dx, dy, dz;
	dx = e.x - s.x;
	dy = e.y - s.y;
	dz = e.z - s.z;

	//Decision functions
	int fxy = 2*dy - dx;
	int fxz = 2*dz - dx;

	pts[count] = (Point){ .x = x, .y = y, .z = z};
	count++;

	while(x < e.x){
		x++;
		if (fxy > 0){
			y++;
			fxy += 2*(dy - dx);
		}
		else{
			fxy += 2*dy;
		}

		if(fxz > 0){
			z++;
			fxz += 2*(dz - dx);
		}
		else{
			fxz += 2*dz;
		}

		pts[count] = (Point){ .x = x, .y = y, .z = z};
		count++;
	}

	*len = count;  
	return pts;
}

/* returnVoxelCube
 * Generates obj lines for a single cube.
 * TODO: explain params and output
 */
char* returnVoxelCube(Point center, int* offset){
	char* repn = malloc(500*sizeof(char)); //TODO: use a more appropriate number here.
	// get representation here
	sprintf(repn, "Hello"); // TODO: put correct stuff here
	// TODO: use and update offset
    return repn;
}

/* createVoxelImage
 * Creates voxel boxes around points given.
 * TODO: explain params and output
 */
void createVoxelImage(Point* pts, size_t len){
	char* filename = "output.obj";

	FILE *fp;
	fp = fopen(filename, "w");
	fprintf(fp, "# OBJ output from 3dss\n");

	int offset = 0;
	for (size_t i = 0; i < len; i++){
		//output each cube's info
		char* cube_string = returnVoxelCube(pts[i], &offset);
		fputs(cube_string, fp);
		fputs("\n", fp);
	}
	fclose(fp);
}

/* requires input as 
 * Sx, Sy, Sx
 * Ex, Ey, Ez
 * All 6 HAVE to be integers.
 * Any other number of args triggers a help message and exits.
 */
void main(int argc, char* argv[]){
	printf("No of args: %d\n", argc - 1);	
	if (argc != 7){
		// show help message and exit.
		printf("Invalid number of args.\n\n");
		printf("Need to give 6 integers, representing: \n\t S -- x, y, z\n\t E -- x, y, z\n");
		return;
	}

	// parse out, store and print the coordinates
	Point s;
	Point e;

	s.x = atoi(argv[1]);
	s.y = atoi(argv[2]);
	s.z = atoi(argv[3]);
	e.x = atoi(argv[4]);
	e.y = atoi(argv[5]);
	e.z = atoi(argv[6]);

	printf("Input: \nS -- (%d, %d, %d) E -- (%d, %d, %d)\n\n", s.x, s.y, s.z, e.x, e.y, e.z);
	// input extraction done

	// get points on the 3d segment and print results
	size_t len;
	Point *pts = draw3DLine(s, e, &len);

	// check for error in function result
	if (pts == NULL){
		// report error
		printf("ERROR. Found no points on line. Try again.\n");
		return;
    }

	printf("Points on the 3d DSS: \n");
	for(size_t i = 0; i < len; i++){
		printf("(%d, %d, %d)\n", pts[i].x, pts[i].y, pts[i].z);
	}
	printf("\n");

	createVoxelImage(pts, len);

	printf("WIP");
	printf("\n");
}
