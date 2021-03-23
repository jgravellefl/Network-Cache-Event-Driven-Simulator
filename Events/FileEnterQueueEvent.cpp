#include <stdio.h>
#include <time.h>
#include "FileEnterQueueEvent.h"

FileEnterQueueEvent::FileEnterQueueEvent() : Event(){}
FileEnterQueueEvent::FileEnterQueueEvent(time_t origTime, time_t execTime, int fileId) : Event(origTime, execTime, fileId){}

Event* FileEnterQueueEvent::process(){
	Event newEvents[2];

	Event myEvent = Event();
 Event *p = newEvents;
	return p;
}