common/ds.o: common/common.h common/ds.h common/ds.c
	cc -std=c99 -c common/ds.c -o common/ds.o
common/voxels.o: common/common.h common/voxels.h common/voxels.c common/ds.h
	cc -std=c99 -c common/voxels.c -o common/voxels.o
common/log.o: common/log.h common/log.c
	cc -std=c99 -c common/log.c -o common/log.o
common/common.o: common/common.h common/ds.o common/voxels.o common/log.o
	ld -r common/ds.o common/voxels.o common/log.o -o common/common.o
line: common/common.o line/main.h line/main.c line/line.h line/line.c
	cc -std=c99 common/common.o line/main.c line/line.c -o line/a.out
2dt: common/common.o triangle/2dmain.h triangle/2dmain.c triangle/triangle2d.h triangle/triangle2d.c line/line.h line/line.c
	cc -std=c99 common/common.o triangle/2dmain.c triangle/triangle2d.c line/line.c -o triangle/a.out
clean:
	find . -type f -name '*.o' -delete
	find . -type f -name 'a.out' -delete
	find . -type f -name 'output.obj' -delete
	find . -type f -name 'output.log' -delete
cleanlog:
	find . -type f -name 'output.log' -delete
