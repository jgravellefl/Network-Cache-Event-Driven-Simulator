#pragma once

#include <stdio.h>
#include <time.h>
#include "Event.h"

class FileRequestEvent: public Event
{
	private:
		time_t origTime;
		time_t execTime;
		int fileId;
	public:
	 FileRequestEvent();
		FileRequestEvent(time_t origTime, time_t nextTime, int fileId);
		Event* process();
};