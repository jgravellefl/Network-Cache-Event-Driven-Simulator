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
    int currValue = fileMap[fileId]->value;
    return currValue;
}

void FIFOCache::insertFile(int fileId, int value) {
    if (this->fileMap.find(fileId) != this->fileMap.end()) {
        this->fileMap[fileId]->value = value;
        return;
    }

    //If the current size reached capacity, remove the first in file
    if (this->currSize == this->capacity) {
        this->fileMap.erase(this->fileDeque.front());
        this->fileDeque.pop_front();
        this->currSize--;
    }

    File *file = new File(fileId, value);
    this->fileMap[fileId] = file;
    this->fileDeque.push_back(fileId);
    this->currSize++;
}

FIFOCache::~FIFOCache() {
    map<int, File*>::iterator iter;
    for (iter = this->fileMap.begin(); iter != this->fileMap.end(); iter++)  {
        delete iter->second;
    }
}