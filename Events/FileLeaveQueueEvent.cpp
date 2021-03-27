#include "FileLeaveQueueEvent.h"

FileLeaveQueueEvent::FileLeaveQueueEvent() : Event(){}
FileLeaveQueueEvent::FileLeaveQueueEvent(float origTime, float execTime, int fileId, Constants* constants) : Event(origTime, execTime, fileId, constants){}

void FileLeaveQueueEvent::process(Event** returnEvents){
	//this->constants->cache->insertFile() this file
 returnEvents[0] = new FileArriveEvent(this->origTime, this->execTime + 10, this->fileId ,this->constants);
	returnEvents[1] = returnEvents[0];
}