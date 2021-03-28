#pragma once
#include <stdio.h>
#include <time.h>
#include <map>

using namespace std;

class RemoteServer {
    public:
		int currSize, propagationTime;
		map<int, File*> fileMap;

        RemoteServer(int propagationTime);
		int getFile(int fileId);
		void insertFile(int fileId, int value);
		~RemoteServer();
};