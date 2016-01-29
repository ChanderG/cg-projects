common/common.o: common/ds.h common/voxels.h common/voxels.c
	cc -std=c99 -c common/voxels.c -o common/common.o
line: common/common.o line/main.h line/main.c
	cc -std=c99 common/common.o line/main.c -o line/a.out
clean:
	find . -type f -name '*.o' -delete
	find . -type f -name 'a.out' -delete
	find . -type f -name 'output.obj' -delete
