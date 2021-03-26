#include "FileEnterQueueEvent.h"

FileEnterQueueEvent::FileEnterQueueEvent() : Event(){}
FileEnterQueueEvent::FileEnterQueueEvent(float origTime, float execTime, int fileId, Constants* constants) : Event(origTime, execTime, fileId, constants){}

Event* FileEnterQueueEvent::process(){
	Event newEvents[2];

	newEvents[0] = FileLeaveQueueEvent(this->origTime, this->execTime + 10, this->fileId, this->constants);
 Event *p = newEvents;
	return p;
}