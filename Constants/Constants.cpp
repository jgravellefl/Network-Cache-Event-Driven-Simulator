#include "Constants.h"

Constants::Constants(Cache* cache, float fifoBandwidth, float cacheBandwidth, FileMap* files, int numRequests, float poissonMean, int totalTime){
 this->cache = cache;
 this->fifoBandwidth = fifoBandwidth;
 this->cacheBandwidth = cacheBandwidth;
 this->files = files;
 this->numRequests = numRequests;
 this->poissonMean = poissonMean;
 this->totalTime = totalTime;
}

Constants::Constants(){}