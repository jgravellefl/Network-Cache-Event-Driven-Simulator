#include "Constants.h"

Constants::Constants(LRUCache* LRUcache, float fifoBandwidth, float cacheBandwidth, RemoteServer* remoteServer, FileSelector* fileSelector, int numRequests, float poissonMean, float totalTime){
 this->LRUcache = LRUcache;
 this->fifoBandwidth = fifoBandwidth;
 this->cacheBandwidth = cacheBandwidth;
 this->remoteServer = remoteServer;
 this->numRequests = numRequests;
 this->poissonMean = poissonMean;
 this->totalTime = totalTime;
 this->fileSelector = fileSelector;
}

Constants::Constants(){}