#pragma once
#include <stdio.h>
#include <time.h>
#include <map>
#include "../Cache/Cache.h"

using namespace std;

class RemoteServer {
    public:
		int currSize, propagationTime, sizeMean;
		map<int, File*> fileMap;

        RemoteServer(int propagationTime);
		RemoteServer(int propagationTime, int size, int sizeMean);
		int getFile(int fileId);
		void populateServer();
		void insertFile(int fileId, int value);
		~RemoteServer();
};