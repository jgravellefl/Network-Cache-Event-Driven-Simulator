#pragma once

#include "Event.h"
#include "../Cache/Cache.h"

class FileArriveEvent: public Event
{
	private:

	public:
	 FileArriveEvent();
		FileArriveEvent(float nextTime, int fileId, Constants* constants);
		int process(Event** returnEvents);
		~FileArriveEvent();
};