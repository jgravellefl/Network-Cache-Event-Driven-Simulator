#include <stdio.h>
#include <time.h>
#include <iostream>
#include <map>
#include "FileSelection.h"
#include "../Cache/Cache.h"

Range::Range(int min, int max) {
    this->min = min;
    this->max = max;
}

bool Range::withinRange(int probabilityInput) {
    //Make sure bounds are good when creating
    if (this->min <= probabilityInput && probabilityInput <= this->max) {
        return true;
    }
    return false;
}

FileSelector::FileSelector() {
    this->currSize = 0;
    this->nextMin = 0;
    this->selectorMap = map<int, Range*>();
}

void FileSelector::insertFile(int fileId, int min, int max){
    if (this->selectorMap.find(fileId) != this->selectorMap.end()) {
        this->selectorMap[fileId]->min = min;
        this->selectorMap[fileId]->max = max;
        this->nextMin = max + 1;
        return;
    }

    Range *range = new Range(min, max);
    this->selectorMap[fileId] = range;
    this->currSize++;
    this->nextMin = max + 1;
}

int FileSelector::getFile(int probabilityInput) {
    map<int, Range*>::iterator iter;
    iter = this->selectorMap.begin();
    bool found = false;
    //Returns -1 if file not found
    int fileID = -1;
    while (!false && iter != this->selectorMap.end()) {
        if (iter->second->withinRange(probabilityInput)) {
            found = true;
            fileID = iter->first;
        }
        iter++;
    }
    return fileID;
}

FileSelector::~FileSelector() {
    map<int, Range*>::iterator iter;
    for (iter = this->selectorMap.begin(); iter != this->selectorMap.end(); iter++)  {
        delete iter->second;
    }
}