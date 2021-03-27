#include "FileLeaveQueueEvent.h"

FileLeaveQueueEvent::FileLeaveQueueEvent() : Event(){}
FileLeaveQueueEvent::FileLeaveQueueEvent(float origTime, float execTime, int fileId, Constants* constants) : Event(origTime, execTime, fileId, constants){}

Event* FileLeaveQueueEvent::process(){
	//this->constants->cache->insertFile() this file
	Event myEvents[2];
	myEvents[0] = FileArriveEvent(this->origTime, this->execTime + 10, this->fileId ,this->constants);
	myEvents[1] = myEvents[1];
	Event* p = myEvents;
	return p;
}