#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
	
	// calculate vertices and faces here
	int vertex_line_length = 25;
	char* vertex_line_repn = "v %f %f %f \n";

	char *v1 = malloc(vertex_line_length*sizeof(char));
	sprintf(v1, vertex_line_repn, center.x - 0.5, center.y - 0.5, center.z + 0.5);

	char *v2 = malloc(vertex_line_length*sizeof(char));
	sprintf(v2, vertex_line_repn, center.x + 0.5, center.y - 0.5, center.z + 0.5);

	char *v3 = malloc(vertex_line_length*sizeof(char));
	sprintf(v3, vertex_line_repn, center.x + 0.5, center.y + 0.5, center.z + 0.5);

	char *v4 = malloc(vertex_line_length*sizeof(char));
	sprintf(v4, vertex_line_repn, center.x - 0.5, center.y + 0.5, center.z + 0.5);

	char *v7 = malloc(vertex_line_length*sizeof(char));
	sprintf(v7, vertex_line_repn, center.x - 0.5, center.y - 0.5, center.z - 0.5);

	char *v6 = malloc(vertex_line_length*sizeof(char));
	sprintf(v6, vertex_line_repn, center.x + 0.5, center.y - 0.5, center.z - 0.5);

	char *v5 = malloc(vertex_line_length*sizeof(char));
	sprintf(v5, vertex_line_repn, center.x + 0.5, center.y + 0.5, center.z - 0.5);

	char *v8 = malloc(vertex_line_length*sizeof(char));
	sprintf(v8, vertex_line_repn, center.x - 0.5, center.y + 0.5, center.z - 0.5);
	
	strcat(repn, v1);
	strcat(repn, v2);
	strcat(repn, v3);
	strcat(repn, v4);
	strcat(repn, v5);
	strcat(repn, v6);
	strcat(repn, v7);
	strcat(repn, v8);

	// dealing with faces
	int face_line_length = 20;
	char *f1, *f2, *f3, *f4, *f5, *f6; 
	f1 = malloc(face_line_length*sizeof(char));
	f2 = malloc(face_line_length*sizeof(char));
	f3 = malloc(face_line_length*sizeof(char));
	f4 = malloc(face_line_length*sizeof(char));
	f5 = malloc(face_line_length*sizeof(char));
	f6 = malloc(face_line_length*sizeof(char));

    // TODO: use #defines to make all this less verbose
	int _1 = 1 + *offset;
	int _2 = 2 + *offset;
	int _3 = 3 + *offset;
	int _4 = 4 + *offset;
	int _5 = 5 + *offset;
	int _6 = 6 + *offset;
	int _7 = 7 + *offset;
	int _8 = 8 + *offset;
	
	char *face_line_repn = "f %d %d %d %d\n";
	sprintf(f1, face_line_repn, _1, _2, _3, _4);
	sprintf(f2, face_line_repn, _5, _6, _7, _8);
	sprintf(f3, face_line_repn, _2, _6, _5, _3);
	sprintf(f4, face_line_repn, _8, _7, _1, _4);
	sprintf(f5, face_line_repn, _7, _6, _2, _1);
	sprintf(f6, face_line_repn, _3, _5, _8, _4);

	strcat(repn, f1);
	strcat(repn, f2);
	strcat(repn, f3);
	strcat(repn, f4);
	strcat(repn, f5);
	strcat(repn, f6);

	*offset += 8;
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
		fputs("#\n", fp);
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
