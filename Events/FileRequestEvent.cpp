#include "FileRequestEvent.h"

FileRequestEvent::FileRequestEvent() : Event(){}
FileRequestEvent::FileRequestEvent(float origTime, float execTime, int fileId, Constants* constants) : Event(origTime, execTime, fileId, constants){}

Event* FileRequestEvent::process(){
	Event newEvents[2];
	
	if (this->constants->cache->getFile(this->fileId) == -1){
		newEvents[0] = FileEnterQueueEvent(this->origTime, this->execTime + 10,this->fileId, this->constants);
	}
	else{
		newEvents[0] = FileArriveEvent(this->origTime, this->execTime + 10, this->fileId, this->constants);
	}
	if (this->constants->numRequests > 0){
		newEvents[1] = FileRequestEvent(this->execTime + 10, this->execTime + 10, this->fileId, this->constants);
	}
	Event *p = newEvents;
	return p;
}