#pragma once
#include <stdio.h>
#include <time.h>
#include <map>
#include <deque>
#include "../LRUCache/LRUCache.h"
#include "../Cache/Cache.h"

using namespace std;

class FIFOCache : public Cache {
    public:
		int capacity, currSize;
        deque<int> fileDeque;
		map<int, File*> fileMap;

		FIFOCache(int capacity);
        int remove_last_file();
		int getFile(int fileId);
		void insertFile(int fileId, int fileSize);
		~FIFOCache();
        FIFOCache();
};