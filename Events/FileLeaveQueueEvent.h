#pragma once

#include "../Cache/Cache.h"
#include "Event.h"
#include "FileArriveEvent.h"

class FileLeaveQueueEvent: public Event
{
	private:

	public:
	 FileLeaveQueueEvent();
		FileLeaveQueueEvent(float initTime, float nextTime, int fileId, Constants* constants);
		int process(Event** returnEvents);
		~FileLeaveQueueEvent(){};
};