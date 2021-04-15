#pragma once
#include <stdio.h>
#include <time.h>
#include <map>
#include <deque>
#include "../LRUCache/LRUCache.h"

using namespace std;

class FIFOCache {
    public:
		int capacity, currSize;
        deque<int> fileDeque;
		map<int, File*> fileMap;

		FIFOCache(int capacity);
        int remove_last_file();
		int getFile(int fileId);
		void insertFile(int fileId, int value);
		~FIFOCache();
        FIFOCache();
};