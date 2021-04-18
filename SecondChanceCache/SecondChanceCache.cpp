#include <stdio.h>
#include <time.h>
#include <iostream>
#include <map>
#include <deque>
#include "SecondChanceCache.h"

SecondChanceFile::SecondChanceFile(int fileId, int fileSize){
	this->fileId = fileId;
	this->fileSize = fileSize;
	this->rBit = 0;
}

SecondChanceCache::SecondChanceCache(int capacity) {
    this->capacity = capacity;
    this->currSize = 0;
    this->fileDeque = deque<int>();
    this->fileMap = map<int, SecondChanceFile*>();
}

int SecondChanceCache::getFile(int fileId) {
    if (this->fileMap.find(fileId) == this->fileMap.end()) {
        return -1;
    }
    int currfileSize = fileMap[fileId]->fileSize;
    fileMap[fileId]->rBit = 1;
    return currfileSize;
}

void SecondChanceCache::insertFile(int fileId, int fileSize) {
    if (this->fileMap.find(fileId) != this->fileMap.end()) {
        this->fileMap[fileId]->fileSize = fileSize;
        return;
    }

    //If the current size reached capacity, remove the first in file
    while (this->currSize + fileSize > this->capacity) {
        bool notFound = true;
        while (notFound) {
            int currFileId = this->fileDeque.front();
            if (this->fileMap[currFileId]->rBit == 1) {
                this->fileMap[currFileId]->rBit = 0;
                this->fileDeque.pop_front();
                this->fileDeque.push_back(currFileId);
            } else {
                notFound = false;
                int tempFileSize = this->fileMap[currFileId]->fileSize;
                this->fileMap.erase(currFileId);
                this->fileDeque.pop_front();
                this->currSize -= tempFileSize;
            }
        }
    }

    SecondChanceFile *file = new SecondChanceFile(fileId, fileSize);
    this->fileMap[fileId] = file;
    this->fileDeque.push_back(fileId);
    this->currSize += fileSize;
}

SecondChanceCache::~SecondChanceCache() {
    map<int, SecondChanceFile*>::iterator iter;
    for (iter = this->fileMap.begin(); iter != this->fileMap.end(); iter++)  {
        delete iter->second;
    }
}