#include "FileLeaveQueueEvent.h"

FileLeaveQueueEvent::FileLeaveQueueEvent() : Event(){}
FileLeaveQueueEvent::FileLeaveQueueEvent(float origTime, float execTime, int fileId, Constants* constants) : Event(origTime, execTime, fileId, constants){}

Event* FileLeaveQueueEvent::process(){
	Event newEvents[2];

	newEvents[0] = FileArriveEvent(this->origTime, this->execTime + 10, this->fileId ,this->constants);
 Event *p = newEvents;
	return p;
}