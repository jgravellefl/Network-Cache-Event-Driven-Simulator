#include <stdio.h>
#include <time.h>
#include <iostream>
#include <map>
#include "RemoteServer.h"
#include "../Cache/Cache.h"

RemoteServer::RemoteServer(int propagationTime) {
    this->propagationTime = propagationTime;
    this->currSize = 0;
    this->fileMap = map<int, File*>();
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

    File *file = File(fileId, value);
    this->fileMap[fileId] = file;
    this->currSize++;
}

RemoteServer::~RemoteServer() {
    map<int, File*>::iterator iter;
    for (iter = this->fileMap.begin(); iter != this->fileMap.end(); iter++)  {
        delete iter->second;
    }
}