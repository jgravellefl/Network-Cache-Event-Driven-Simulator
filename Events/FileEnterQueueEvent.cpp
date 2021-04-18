#include "FileEnterQueueEvent.h"

FileEnterQueueEvent::FileEnterQueueEvent() : Event(){}
FileEnterQueueEvent::FileEnterQueueEvent(float execTime, int fileId, Constants* constants) : Event(execTime, fileId, constants){}

int FileEnterQueueEvent::process(Event** returnEvents){
	//cout << "file " << this->fileId << " entering FIFO queue" << "at time: " <<this->execTime << endl;
	if (this->constants->remoteServer->fifoQueue.empty()){
		this->constants->remoteServer->fifoQueue.push(this->fileId);
		returnEvents[0] = new FileLeaveQueueEvent(this->execTime + (this->constants->remoteServer->getFile(this->fileId))/this->constants->fifoBandwidth, this->fileId, this->constants);
		return 1;
	}
	else{
		this->constants->remoteServer->fifoQueue.push(this->fileId);
		return 0;
	}
}