#include "FileEnterQueueEvent.h"

FileEnterQueueEvent::FileEnterQueueEvent() : Event(){}
FileEnterQueueEvent::FileEnterQueueEvent(float origTime, float execTime, int fileId, Constants* constants) : Event(origTime, execTime, fileId, constants){}

void FileEnterQueueEvent::process(Event** returnEvents){

	returnEvents[0] = new FileLeaveQueueEvent(this->origTime, this->execTime + 10, this->fileId, this->constants);
 returnEvents[1] = returnEvents[0];
}