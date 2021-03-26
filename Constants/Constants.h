#pragma once
#include "../Cache/Cache.h"
#include "../FileMap/FileMap.h"

class Constants{
 public:
  Cache* cache;
  float fifoBandwidth;
  float queueBandwidth;
  FileMap* files;
  int numRequests;

  Constants();
  Constants(Cache* cache, float fifoBandwidth, float queueBandwidth, FileMap* files, int numRequests);
};