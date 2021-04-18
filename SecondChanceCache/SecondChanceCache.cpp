#include <stdio.h>
#include <time.h>
#include <iostream>
#include <map>
#include <deque>
#include "SecondChanceCache.h"

SecondChanceFile::SecondChanceFile(int fileId, int value){
	this->fileId = fileId;
	this->value = value;
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
    int currValue = fileMap[fileId]->value;
    fileMap[fileId]->rBit = 1;
    return currValue;
}

void SecondChanceCache::insertFile(int fileId, int value) {
    if (this->fileMap.find(fileId) != this->fileMap.end()) {
        this->fileMap[fileId]->value = value;
        return;
    }

    //If the current size reached capacity, remove the first in file
    if (this->currSize == this->capacity) {
        bool notFound = true;
        while (notFound) {
            int currFileId = this->fileDeque.front();
            if (this->fileMap[currFileId]->rBit == 1) {
                this->fileMap[currFileId]->rBit = 0;
                this->fileDeque.pop_front();
                this->fileDeque.push_back(currFileId);
            } else {
                notFound = false;
                this->fileMap.erase(currFileId);
                this->fileDeque.pop_front();
                this->currSize--;
            }
        }
    }

    SecondChanceFile *file = new SecondChanceFile(fileId, value);
    this->fileMap[fileId] = file;
    this->fileDeque.push_back(fileId);
    this->currSize++;
}

SecondChanceCache::~SecondChanceCache() {
    map<int, SecondChanceFile*>::iterator iter;
    for (iter = this->fileMap.begin(); iter != this->fileMap.end(); iter++)  {
        delete iter->second;
    }
}