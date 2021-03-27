#pragma once

#include "Event.h"
#include "../Cache/Cache.h"

class FileArriveEvent: public Event
{
	private:

	public:
	 FileArriveEvent();
		FileArriveEvent(float origTime, float nextTime, int fileId, Constants* constants);
		Event* process();
};