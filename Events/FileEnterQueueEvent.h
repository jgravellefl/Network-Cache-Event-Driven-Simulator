#pragma once

#include "Event.h"
#include "../Cache/Cache.h"
#include "FileLeaveQueueEvent.h"

class FileEnterQueueEvent: public Event
{

	public:
	 FileEnterQueueEvent();
		FileEnterQueueEvent(float origTime, float nextTime, int fileId, Constants* constants);
		Event* process();
};