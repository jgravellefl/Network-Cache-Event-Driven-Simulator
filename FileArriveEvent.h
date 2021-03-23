#pragma once

#include <stdio.h>
#include <time.h>
#include "Event.h"

class FileArriveEvent: public Event
{
	private:
		time_t origTime;
		time_t execTime;
		int fileId;
	public:
	 FileArriveEvent();
		FileArriveEvent(time_t origTime, time_t nextTime, int fileId);
		Event* process();
};