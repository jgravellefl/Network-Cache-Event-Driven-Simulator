#pragma once

#include <random>
#include "Event.h"
#include "../Cache/Cache.h"
#include <iostream>
#include "../Constants/Constants.h"
#include "FileRequestEvent.h"
//#include "FileEnterQueueEvent.h"
//#include "FileArriveEvent.h"

class FileRequestEvent: public Event
{
	private:

	public:
		//default_random_engine generator;
  poisson_distribution<int> poissonDist;
		mt19937 generator;
	 FileRequestEvent();
		FileRequestEvent(float origTime, float nextTime, int fileId, Constants* constants);
		void process(Event** returnEvents);
		~FileRequestEvent(){};
};