#include <stdio.h>
#include <time.h>
#include <iostream>
#include <map>
#include <random>
#include "FileSelection.h"
#include "../Cache/Cache.h"
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>

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

FileSelector::FileSelector(int numFiles, double paretoShape, double paretoScale){
    
    this->currSize = numFiles;
    this->selectorMap = map<int, Range*>();
    const gsl_rng_type * T;
    //may cause issues to call this here and in RemoteServer, will need to monitor
    gsl_rng_env_setup();      
    T = gsl_rng_default;
    const gsl_rng * r = gsl_rng_alloc (T);
    int popArray[numFiles];
    int sum = 0;
    for (int i = 0; i < numFiles; i++){
        double randomSample = gsl_ran_pareto(r, paretoShape, paretoScale);
        popArray[i] = int(randomSample);
        sum += int(randomSample);
    }
    int tempSum = 0;
    for (int i = 0; i < numFiles; i++){
        int currSum = popArray[i];
        this->insertFile(i, tempSum, tempSum + currSum);
        tempSum += currSum + 1;
    }
    this->nextMin = tempSum;
    this->currSize = sum;
    srand (time(NULL));
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

int FileSelector::getFile() {
    int probabilityInput = rand() % (currSize - 1) + 1;
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