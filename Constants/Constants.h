#pragma once
#include "../LRUCache/LRUCache.h"
#include "../RemoteServer/RemoteServer.h"
#include <queue>
#include "../FileSelection/FileSelection.h"

class Constants{
 public:
  LRUCache* LRUcache;
  float fifoBandwidth;
  float cacheBandwidth;
  RemoteServer* remoteServer;
  FileSelector* fileSelector;
  int numRequests;
  float poissonMean;
  float totalTime;

  Constants();
  Constants(LRUCache* LRUcache, float fifoBandwidth, float cacheBandwidth, RemoteServer* remoteServer, FileSelector* fileSelector, int numRequests, float poissonMean, float totalTime);
};