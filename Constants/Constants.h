#pragma once
#include "../Cache/Cache.h"
#include "../RemoteServer/RemoteServer.h"
#include <queue>
#include "../FileSelection/FileSelection.h"

class Constants{
 public:
  Cache* cache;
  float fifoBandwidth;
  float cacheBandwidth;
  RemoteServer* remoteServer;
  FileSelector* fileSelector;
  int numRequests;
  float poissonMean;
  float totalTime;
  int cacheMisses;

  Constants();
  Constants(Cache* LRUcache, float fifoBandwidth, float cacheBandwidth, RemoteServer* remoteServer, FileSelector* fileSelector, int numRequests, float poissonMean, float totalTime, int cacheMisses);
};