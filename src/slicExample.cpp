#include <string>
#include "SLIC.h"
#include <iostream>


void DoSupervoxelVideoSegmentation();

int main()
{
	
	DoSupervoxelVideoSegmentation();
	return 0;
}



//===========================================================================
///	DoSupervoxelVideoSegmentation
///
/// Supervoxel segmentation demo
//===========================================================================
void DoSupervoxelVideoSegmentation()
{
    const int width	= 7;
    const int height = 7;
    const int depth = 7;
    const int sz = (width*height);

	const std::string filename = "yourfilename.jpg";
	const std::string savepath = "yourpathname";

    int supervoxelsize = 8;//size in pixels (2x2x2)
    double compactness = 10.0;
    int numlabels = 0;
    int** klabels = new int*[depth];
    unsigned int** ubuff = new unsigned int *[depth];
    for(int i=0; i < depth; i++)
    {
            ubuff[i] = new unsigned int[sz];
            klabels[i] = new int[sz];

            for (int k=0; k < sz; k++)
                    ubuff[i][k] = (unsigned int)rand();//normally this would be 2d slice pixel data
    }
    SLIC slic;
    slic.DoSupervoxelSegmentation( ubuff, width, height, depth, klabels, numlabels, supervoxelsize, compactness );

	//slic.SaveSupervoxelLabels(klabels, width, height, depth, filename, savepath);

	for(int i=0; i < depth; i++)
	{
		for (int k=0; k < sz; k++) {
			std::cout << klabels[i][k] << std::endl;
 	}
	}


	for(int i=0; i < depth; i++)
	{
		delete [] klabels[i];
		delete [] ubuff[i];
	}
	delete [] klabels; delete [] ubuff;
}
