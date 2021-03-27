#pragma once

#include <random>
#include "Event.h"
#include "../Cache/Cache.h"
#include "../Constants/Constants.h"
#include "FileRequestEvent.h"
//#include "FileEnterQueueEvent.h"
//#include "FileArriveEvent.h"

class FileRequestEvent: public Event
{
	private:

	public:
	 FileRequestEvent();
		FileRequestEvent(float origTime, float nextTime, int fileId, Constants* constants);
		void process(Event** returnEvents);
		~FileRequestEvent(){};
};