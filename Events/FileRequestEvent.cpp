#include <stdio.h>
#include <time.h>
#include "FileRequestEvent.h"

FileRequestEvent::FileRequestEvent() : Event(){}
FileRequestEvent::FileRequestEvent(time_t origTime, time_t execTime, int fileId) : Event(origTime, execTime, fileId){}

Event* FileRequestEvent::process(){
	Event newEvents[2];

	Event myEvent = Event();
 Event *p = newEvents;
	return p;
}