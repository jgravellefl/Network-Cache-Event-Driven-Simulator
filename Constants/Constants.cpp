#include "Constants.h"

Constants::Constants(Cache* cache, float fifoBandwidth, float cacheBandwidth, RemoteServer* remoteServer, FileSelector* fileSelector, int numRequests, float poissonMean, float totalTime, int cacheMisses){
 this->cache = cache;
 this->fifoBandwidth = fifoBandwidth;
 this->cacheBandwidth = cacheBandwidth;
 this->remoteServer = remoteServer;
 this->numRequests = numRequests;
 this->poissonMean = poissonMean;
 this->totalTime = totalTime;
 this->fileSelector = fileSelector;
 this->cacheMisses = cacheMisses;
}

Constants::Constants(){}