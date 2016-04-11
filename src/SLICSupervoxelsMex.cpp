#include <mex.h>
#include <string>
#include "SLIC.h"
#include <iostream>

// http://www.mathworks.co.uk/help/matlab/matlab_external/standalone-example.html


/* The gateway function */
/*
nlhs	Number of output (left-side) arguments, or the size of the plhs array.
plhs	Array of output arguments.
nrhs	Number of input (right-side) arguments, or the size of the prhs array.
prhs	Array of input arguments.
*/
void mexFunction(int nlhs, mxArray *plhs[],
	int nrhs, const mxArray *prhs[])
{

    int supervoxelsize[3] = {10,10,10};
    double compactness = 10.0;
    int numlabels = 0;
    int numIter = 5;
    double spacing[3] = {1,1,1};


    // get parameter values
    if (nrhs == 2) {  
    	
    	mxArray *tmp;

    	tmp = mxGetField(prhs[1], 0, "supervoxelsize");
        const mwSize* n_ds = mxGetDimensions(tmp);
    	if (tmp != NULL && n_ds[1] == 3) {
    		double* s_ptr = (double*)mxGetPr(tmp);
            supervoxelsize[0] = s_ptr[0];
            supervoxelsize[1] = s_ptr[1];
            supervoxelsize[2] = s_ptr[2];
        }
    	else {
    		mexPrintf("supervoxelsize not set correctly; setting it to default 10x10x10\n");
    	
    	}

    	tmp = mxGetField(prhs[1], 0, "compactness");
    	if (tmp != NULL) 
    		compactness = (double)mxGetScalar(tmp);
    	else {
    		mexPrintf("compactness not set correctly; setting it to default 10.0\n");
    		compactness = 10.0;
    	}
        tmp = mxGetField(prhs[1], 0, "numIter");
        if (tmp != NULL) 
            numIter = (double)mxGetScalar(tmp);
        else {
            mexPrintf("numIter not set correctly; setting it to default 5\n");
            numIter = 5;
        }
        tmp = mxGetField(prhs[1], 0, "spacing");
        const mwSize *n_d = mxGetDimensions(tmp);
        if (tmp != NULL && n_d[1] ==3) {
            double* s_ptr = (double*)mxGetPr(tmp);

            spacing[0] = s_ptr[0];
            spacing[1] = s_ptr[1];
            spacing[2] = s_ptr[2];
        }
        else {
            mexPrintf("spacing not set correctly; setting it to default 1\n");
         
        }

        // std::cout << spacing[0] << std::endl;
        // std::cout << spacing[1] << std::endl;
        // std::cout << spacing[2] << std::endl;
        // std::cout << supervoxelsize[0] << std::endl;
        // std::cout << supervoxelsize[1] << std::endl;
        // std::cout << supervoxelsize[2] << std::endl;

    }

    mwSize n_dim = mxGetNumberOfDimensions(prhs[0]);
    if ( n_dim != 3) {
    	mexPrintf("image must be 3D\n");
    	return;
    }


    size_t  height, width, depth;
    const mwSize* dims = mxGetDimensions(prhs[0]);
    width = dims[0];
    height = dims[1];
    depth = dims[2];

    // std::cout <<"width: " << width << std::endl;
    // std::cout <<"height: " << height << std::endl;
    // std::cout <<"depth: " << depth << std::endl;

    unsigned int** ubuff;
    ubuff = (unsigned int **)mxCalloc(depth, sizeof(unsigned int *));

    unsigned int* ubuff2 = (unsigned int* )mxGetData(prhs[0]);

    #pragma omp parallel for 
    for(int z = 0; z < depth; z++) {
        ubuff[z] = (unsigned int *) mxCalloc(height*width, sizeof(unsigned int));
        int i(0);
        for(int x=0; x < width; x++) {
            for(int y=0; y < height; y++) {
                ubuff[z][i] = ubuff2[y + x*height + z*width*height];
                i++;
            }
        }
    }


    int** klabels = new int*[depth]; 
    for(int i=0; i < depth; i++)
    {
    	klabels[i] = new int[width*height];
    }

    plhs[0] = mxCreateNumericMatrix(depth, width*height, mxINT32_CLASS, mxREAL);
    int * klabelsOut = (int *)mxGetData(plhs[0]);

    SLIC slic;
    slic.DoSupervoxelSegmentation( ubuff, width, height, depth, klabels, numlabels, supervoxelsize, compactness, numIter, spacing );
    mexPrintf("number of labels: %d\n",numlabels);



    // output
    for(int z=0; z < depth; z++) {
    	int i(0);
    	for(int x=0; x < width; x++) {
    		for(int y=0; y < height; y++) {
    			klabelsOut[y + x*height + z*width*height] = klabels[z][i];
    			i++;
    		}
    	}

    }


    // clean up
    for(int z = 0; z < depth; z++) {
    	mxFree(ubuff[z]);
        delete [] klabels[z];
    }
    mxFree(ubuff);
    delete klabels;
   
}