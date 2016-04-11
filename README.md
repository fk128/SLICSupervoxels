

## About

Matlab Mex file for generating 3D SLIC supervoxels.

Supervoxel code adapted from the C++ implementation found [here](http://ivrl.epfl.ch/supplementary_material/RK_SLICSuperpixels/index.html).

## Expected input

3D grayscale images uint32.

## Additional parameters

A spacing parameter has been added to allow having a different spacing in the x,y and z directions. See example3D.m for an example of applying the code on a 3D image.

## How to compile

- In the terminal: If `mex` is defined in your command line environment, you can execute `make` from the command line.
- In matlab: run `compile.m`.

## References

Radhakrishna Achanta, Appu Shaji, Kevin Smith, Aurelien Lucchi, Pascal Fua, and Sabine Süsstrunk, SLIC Superpixels Compared to State-of-the-art Superpixel Methods, IEEE Transactions on Pattern Analysis and Machine Intelligence, vol. 34, num. 11, p. 2274 - 2282, May 2012.

Radhakrishna Achanta, Appu Shaji, Kevin Smith, Aurelien Lucchi, Pascal Fua, and Sabine Süsstrunk, SLIC Superpixels, EPFL Technical Report no. 149300, June 2010.


