OUTDIR=bin
INC=-Iinclude/
all: src/SLICSupervoxelsMex.cpp src/SLIC.cpp include/SLIC.h
	mex src/SLICSupervoxelsMex.cpp src/SLIC.cpp ${INC} -outdir ${OUTDIR} COPTIMFLAGS='-O3' 

clean:
	rm -rf  ${OUTDIR}/*.mex*

.PHONY: clean
