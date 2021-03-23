#include <stdio.h>
#include <time.h>
#include "FileLeaveQueueEvent.h"

FileLeaveQueueEvent::FileLeaveQueueEvent() : Event(){}
FileLeaveQueueEvent::FileLeaveQueueEvent(time_t origTime, time_t execTime, int fileId) : Event(origTime, execTime, fileId){}

Event* FileLeaveQueueEvent::process(){
	Event newEvents[2];

	Event myEvent = Event();
 Event *p = newEvents;
	return p;
}