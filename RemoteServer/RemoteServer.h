#pragma once
#include <stdio.h>
#include <time.h>
#include <queue>
#include <set>
#include <map>
#include "../LRUCache/LRUCache.h"
#include <vector>

using namespace std;

class RemoteServer {
    public:
		int currSize, propagationTime;
		map<int, File*> fileMap;
		double paretoShape;
		double paretoScale;
		queue<int> fifoQueue;
		std::map<const int, vector<float> > waitingMap;
		std::set<int> queuePop;

        RemoteServer(int propagationTime);
		RemoteServer(int propagationTime, int size, double paretoShape, double paretoScale, int cacheSize);
		int getFile(int fileId);
		void populateServer(int cacheSize);
		void insertFile(int fileId, int fileSize);
		~RemoteServer();
};