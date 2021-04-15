#pragma once

#include "Event.h"
#include "../LRUCache/LRUCache.h"
#include "FileLeaveQueueEvent.h"

class FileEnterQueueEvent: public Event
{

	public:
	 FileEnterQueueEvent();
		FileEnterQueueEvent(float nextTime, int fileId, Constants* constants);
	 int process(Event** returnEvents);
		~FileEnterQueueEvent(){};
};