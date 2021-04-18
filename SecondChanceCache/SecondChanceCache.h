#pragma once
#include <stdio.h>
#include <time.h>
#include <map>
#include <deque>
#include "../LRUCache/LRUCache.h"
#include "../Cache/Cache.h"

using namespace std;

class SecondChanceFile {
    public:
        int fileId, value, rBit;

    //Create file with id and value
        SecondChanceFile(int fileId, int value);
};

class SecondChanceCache : public Cache {
    public:
		int capacity, currSize;
        deque<int> fileDeque;
		map<int, SecondChanceFile*> fileMap;

		SecondChanceCache(int capacity);
		int getFile(int fileId);
		void insertFile(int fileId, int value);
		~SecondChanceCache();
};