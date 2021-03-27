#pragma once

class FileMap{
 public:
  int numFiles;
  float* fileSizes;
  float* filePopularities;
  FileMap();
  FileMap(int numFiles, float* fileSizes, float* filePopularities);
};