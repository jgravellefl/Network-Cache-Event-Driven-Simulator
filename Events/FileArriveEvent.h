#pragma once

#include "Event.h"
#include "../LRUCache/LRUCache.h"

class FileArriveEvent: public Event
{
	private:

	public:
	 FileArriveEvent();
		FileArriveEvent(float initTime, float nextTime, int fileId, Constants* constants);
		int process(Event** returnEvents);
		~FileArriveEvent();
};