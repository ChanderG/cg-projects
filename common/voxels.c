/*
 * Functions dealing with creation and drawing of voxels.
 */

#include"voxels.h"

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
 * INPUT:
 * ========
 * pts -- array of Points
 * len --length of points array
 *
 * OUTPUT:
 * ========
 * Creates a .obj file named "output.obj" 
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
void createVoxelImage2D(Point2D* pts, size_t len){
  // create a list of 3d points taken from the 2d points
  Point* pts3d = convert2dPointArrayTo3d(pts, len);

  // simply call the 3d analog function
  createVoxelImage(pts3d, len);
}
