#pragma once
#include <stdio.h>
#include <time.h>
#include <map>
#include "../Cache/Cache.h"

using namespace std;

class Range {
	public:
		int min, max;

		Range(int min, int max);
		bool withinRange(int probabilityInput);
};

class FileSelector {
    public:
		int currSize, nextMin;
		map<int, Range*> selectorMap;


        FileSelector();
		FileSelector(int numFiles, double paretoScale, double paretoShape);
		void insertFile(int fileId, int min, int max);
		int getFile(int probabilityInput);
		int getFile();
		~FileSelector();
		
};