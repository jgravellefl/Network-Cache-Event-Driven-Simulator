#pragma once

#include "../Cache/Cache.h"
#include "Event.h"
#include "FileArriveEvent.h"

class FileLeaveQueueEvent: public Event
{
	private:

	public:
	 FileLeaveQueueEvent();
		FileLeaveQueueEvent(float origTime, float nextTime, int fileId, Constants* constants);
		void process(Event** returnEvents);
		~FileLeaveQueueEvent(){};
};