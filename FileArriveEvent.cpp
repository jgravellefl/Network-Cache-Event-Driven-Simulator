#include <stdio.h>
#include <time.h>
#include "FileArriveEvent.h"

FileArriveEvent::FileArriveEvent() : Event(){}
FileArriveEvent::FileArriveEvent(time_t origTime, time_t execTime, int fileId) : Event(origTime, execTime, fileId){}

Event* FileArriveEvent::process(){
	Event newEvents[2];

	Event myEvent = Event();
 Event *p = newEvents;
	
	return p;
}