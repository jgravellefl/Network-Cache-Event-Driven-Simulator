#pragma once

#include <stdio.h>
#include <time.h>
#include "Event.h"

class FileLeaveQueueEvent: public Event
{
	private:
		time_t origTime;
		time_t execTime;
		int fileId;
	public:
	 FileLeaveQueueEvent();
		FileLeaveQueueEvent(time_t origTime, time_t nextTime, int fileId);
		Event* process();
};