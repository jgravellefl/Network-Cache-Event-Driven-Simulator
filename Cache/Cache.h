#pragma once
#include <stdio.h>
#include <time.h>
#include <map>
#include <deque>

using namespace std;

class Cache {
    public:
		int capacity, currSize;

		Cache(int capacity);
        Cache();
        virtual void insertFile(int fileId, int value);
        virtual int getFile(int fileId);
		virtual ~Cache();
};