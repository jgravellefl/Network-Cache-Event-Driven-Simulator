#include "Constants.h"

Constants::Constants(Cache* cache, float fifoBandwidth, float queueBandwidth, FileMap* files, int numRequests){
 this->cache = cache
 this->fifoBandwidth = fifoBandwidth;
 this->queueBandwidth = cacheBandwidth;
 this->files = files;
 this->numRequests = numRequests;
}