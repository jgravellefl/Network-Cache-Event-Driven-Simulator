#include "FileEnterQueueEvent.h"

FileEnterQueueEvent::FileEnterQueueEvent() : Event(){}
FileEnterQueueEvent::FileEnterQueueEvent(float origTime, float execTime, int fileId, Constants* constants) : Event(origTime, execTime, fileId, constants){}

Event* FileEnterQueueEvent::process(){

	Event myEvents[2]; 
	myEvents[0] = FileLeaveQueueEvent(this->origTime, this->execTime + 10, this->fileId, this->constants);
 myEvents[0] = myEvents[1];
	Event* p = myEvents;
	return p;
}