#include <stdio.h>
#include <time.h>
#include <iostream>
#include "Cache.h"

Cache::Cache(int capacity) {
    this->capacity = capacity;
    this->currSize = 0;
}

Cache::Cache() {
    this->capacity = 0;
    this->currSize = 0;
}

Cache::~Cache() {
    // cout << "remove cache" << endl;
}

void Cache::insertFile(int fileId, int value) {
    cout << "parent" << endl;
}

int Cache::getFile(int fileId) {
    cout <<" parent" << endl;
    return fileId;
}