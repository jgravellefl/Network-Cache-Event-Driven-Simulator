#include <stdio.h>
#include <time.h>
#include <iostream>
#include <map>
#include <sys/time.h>
#include "RemoteServer.h"
#include <random>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>

RemoteServer::RemoteServer(int propagationTime) {
    this->propagationTime = propagationTime;
    this->currSize = 0;
    this->fileMap = map<int, File*>();
}

RemoteServer::RemoteServer(int propagationTime, int size, double paretoShape, double paretoScale, int cacheSize) {
    this->propagationTime = propagationTime;
    this->currSize = size;
    this->fileMap = map<int, File*>();
    this->waitingMap = map<const int, vector<float> >();
    this->paretoScale = paretoScale;
    this->paretoShape = paretoShape;
    this->populateServer(cacheSize);
}

int RemoteServer::getFile(int fileId) {
    if (this->fileMap.find(fileId) == this->fileMap.end()) {
        return -1;
    }
    int currfileSize = fileMap[fileId]->fileSize;
    return currfileSize;
}

void RemoteServer::insertFile(int fileId, int fileSize) {
    if (this->fileMap.find(fileId) != this->fileMap.end()) {
        this->fileMap[fileId]->fileSize = fileSize;
        return;
    }

    File *file = new File(fileId, fileSize);
    this->fileMap[fileId] = file;
    this->currSize++;
}

void RemoteServer::populateServer(int cacheSize) {

    const gsl_rng_type * T;
    gsl_rng_env_setup();
    T = gsl_rng_default;
    struct timeval tv; // Seed generation based on time
    gettimeofday(&tv,0);
    unsigned long mySeed = tv.tv_sec + tv.tv_usec;
    const gsl_rng * r = gsl_rng_alloc (T);
    gsl_rng_set(r, mySeed);

    for (int i = 1; i < this->currSize + 1; i++){
        double randomSample = gsl_ran_pareto(r, this->paretoShape, this->paretoScale);
        while (randomSample > cacheSize){
            randomSample = gsl_ran_pareto(r, this->paretoShape, this->paretoScale);
        }
        File *file = new File(i, int(randomSample));
        this->fileMap[i] = file;
    }
}

RemoteServer::~RemoteServer() {
    map<int, File*>::iterator iter;
    for (iter = this->fileMap.begin(); iter != this->fileMap.end(); iter++)  {
        delete iter->second;
    }
}