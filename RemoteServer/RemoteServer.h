#pragma once
#include <stdio.h>
#include <time.h>
#include <queue>
#include <set>
#include <map>
#include "../Cache/Cache.h"

using namespace std;

class RemoteServer {
    public:
		int currSize, propagationTime;
		map<int, File*> fileMap;
		double paretoShape;
		double paretoScale;
		queue<int> fifoQueue;
		std::set<int> queuePop;

        RemoteServer(int propagationTime);
		RemoteServer(int propagationTime, int size, double paretoShape, double paretoScale);
		int getFile(int fileId);
		void populateServer();
		void insertFile(int fileId, int value);
		~RemoteServer();
};