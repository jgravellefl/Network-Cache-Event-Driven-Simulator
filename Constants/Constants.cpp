#include "Constants.h"

Constants::Constants(Cache* cache, float fifoBandwidth, float cacheBandwidth, FileMap* files, int numRequests, float poissonMean){
 this->cache = cache;
 this->fifoBandwidth = fifoBandwidth;
 this->cacheBandwidth = cacheBandwidth;
 this->files = files;
 this->numRequests = numRequests;
 this->poissonMean = poissonMean;
}

Constants::Constants(){}