#include <stdio.h>
#include <time.h>
#include <iostream>
#include <map>
#include "RemoteServer.h"
#include <random>
#include "../Cache/Cache.h"

RemoteServer::RemoteServer(int propagationTime) {
    this->propagationTime = propagationTime;
    this->currSize = 0;
    this->fileMap = map<int, File*>();
}

RemoteServer::RemoteServer(int propagationTime, int size, int sizeMean) {
    this->propagationTime = propagationTime;
    this->currSize = size;
    this->fileMap = map<int, File*>();
    this->sizeMean = sizeMean;
    this->populateServer();
}

int RemoteServer::getFile(int fileId) {
    if (this->fileMap.find(fileId) == this->fileMap.end()) {
        return -1;
    }
    int currValue = fileMap[fileId]->value;
    return currValue;
}

void RemoteServer::insertFile(int fileId, int value) {
    if (this->fileMap.find(fileId) != this->fileMap.end()) {
        this->fileMap[fileId]->value = value;
        return;
    }

    File *file = new File(fileId, value);
    this->fileMap[fileId] = file;
    this->currSize++;
}

void RemoteServer::populateServer() {

    default_random_engine generator;
    exponential_distribution<double> distribution(3.5);

    for (int i = 1; i < this->currSize + 1; i++){
        //File *file = new File(i, distribution(generator));
        //this->fileMap[i] = file;
        cout << distribution(generator) << endl;;
    }
}

RemoteServer::~RemoteServer() {
    map<int, File*>::iterator iter;
    for (iter = this->fileMap.begin(); iter != this->fileMap.end(); iter++)  {
        delete iter->second;
    }
}