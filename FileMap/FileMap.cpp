#include "FileMap.h"

FileMap::FileMap(int numFiles, float* fileSizes, float* filePopularities){
 this->numFiles = numFiles;
 this->fileSizes = fileSizes;
 this->filePopularities = filePopularities;
}
FileMap::FileMap(){};