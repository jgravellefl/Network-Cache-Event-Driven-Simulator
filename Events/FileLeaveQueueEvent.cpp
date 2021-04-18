#include "FileLeaveQueueEvent.h"

FileLeaveQueueEvent::FileLeaveQueueEvent() : Event(){}
FileLeaveQueueEvent::FileLeaveQueueEvent(float execTime, int fileId, Constants* constants) : Event(execTime, fileId, constants){}

int FileLeaveQueueEvent::process(Event** returnEvents){
	//this->constants->cache->insertFile() this file
	//cout << "file " << this->fileId << "leaving fifo queue " << "at time" << this->execTime <<endl;
	int fileId = this->constants->remoteServer->fifoQueue.front();
	this->constants->remoteServer->fifoQueue.pop();
	this->constants->cache->insertFile(fileId, this->constants->remoteServer->getFile(fileId));
	//error here I think/
	this-constants->remoteServer->queuePop.erase(this->fileId);
	returnEvents[0] = new FileArriveEvent(this->execTime + this->constants->remoteServer->getFile(this->fileId)/this->constants->cacheBandwidth, this->fileId, this->constants);
	if (!this->constants->remoteServer->fifoQueue.empty()){
		fileId = this->constants->remoteServer->fifoQueue.front();
		returnEvents[1] = new FileLeaveQueueEvent(this->execTime + this->constants->remoteServer->getFile(fileId)/this->constants->fifoBandwidth, fileId, this->constants);
		return 2;
	}
	return 1;
}
