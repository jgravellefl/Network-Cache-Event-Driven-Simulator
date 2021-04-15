#pragma once

#include <random>
#include "Event.h"
#include "../LRUCache/LRUCache.h"
#include <iostream>
#include "../Constants/Constants.h"
#include "FileRequestEvent.h"
#include "FileEnterQueueEvent.h"
#include "FileArriveEvent.h"

class FileRequestEvent: public Event
{
	private:

	public:
		//default_random_engine generator;
  poisson_distribution<int> poissonDist;
		mt19937 generator;
	 FileRequestEvent();
		FileRequestEvent(float nextTime, int fileId, Constants* constants);
		int process(Event** returnEvents);
		~FileRequestEvent(){};
};