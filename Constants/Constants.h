#pragma once
#include "../Cache/Cache.h"
#include "../FileMap/FileMap.h"

class Constants{
 public:
  Cache* cache;
  float fifoBandwidth;
  float cacheBandwidth;
  FileMap* files;
  int numRequests;
  float poissonMean;
  int totalTime;

  Constants();
  Constants(Cache* cache, float fifoBandwidth, float cacheBandwidth, FileMap* files, int numRequests, float poissonMean, int totalTime);
};