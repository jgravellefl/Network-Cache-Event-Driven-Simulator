#include <stdio.h>
#include <time.h>
#include <iostream>
#include <map>
#include <deque>
#include "FIFOCache.h"

int FIFOCache::remove_last_file() {
    //Returns -1 if the queue is emptu
    if (this->fileDeque.empty()) {
        return -1;
    }

    int lastFileID = this->fileDeque.front();

    this->fileMap.erase(this->fileDeque.front());
    this->fileDeque.pop_front();

    return lastFileID;
}

FIFOCache::FIFOCache(int capacity) {
    this->capacity = capacity;
    this->currSize = 0;
    this->fileDeque = deque<int>();
    this->fileMap = map<int, File*>();
}

int FIFOCache::getFile(int fileId) {
    if (this->fileMap.find(fileId) == this->fileMap.end()) {
        return -1;
    }
    int currfileSize = fileMap[fileId]->fileSize;
    return currfileSize;
}

void FIFOCache::insertFile(int fileId, int fileSize) {
    if (this->fileMap.find(fileId) != this->fileMap.end()) {
        this->fileMap[fileId]->fileSize = fileSize;
        return;
    }

    //If the current size reached capacity, remove the first in file
    while (this->currSize + fileSize > this->capacity) {
        int tempFileSize = this->fileMap[this->fileDeque.front()]->fileSize;
        this->fileMap.erase(this->fileDeque.front());
        this->fileDeque.pop_front();
        this->currSize = this->currSize - tempFileSize;
    }

    File *file = new File(fileId, fileSize);
    this->fileMap[fileId] = file;
    this->fileDeque.push_back(fileId);
    this->currSize += fileSize;
}

FIFOCache::~FIFOCache() {
    map<int, File*>::iterator iter;
    for (iter = this->fileMap.begin(); iter != this->fileMap.end(); iter++)  {
        delete iter->second;
    }
}