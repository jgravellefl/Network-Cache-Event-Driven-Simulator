#pragma once

#include <stdio.h>
#include <time.h>
#include "Event.h"
#include "../Cache/Cache.h"
#include "../Constants/Constants.h"
#include "FileRequestEvent.h"
#include "FileEnterQueueEvent.h"
#include "FileArriveEvent.h"

class FileRequestEvent: public Event
{
	private:

	public:
	 FileRequestEvent();
		FileRequestEvent(float origTime, float nextTime, int fileId, Constants* constants);
		Event* process();
};