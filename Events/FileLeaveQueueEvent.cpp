#include "FileLeaveQueueEvent.h"

FileLeaveQueueEvent::FileLeaveQueueEvent() : Event(){}
FileLeaveQueueEvent::FileLeaveQueueEvent(float initTime, float execTime, int fileId, Constants* constants) : Event(initTime, execTime, fileId, constants){}

int FileLeaveQueueEvent::process(Event** returnEvents){
	//this->constants->cache->insertFile() this file
	//cout << "file " << this->fileId << "leaving fifo queue " << "at time " << this->execTime <<endl;
	int fileId = this->constants->remoteServer->fifoQueue.front();
	this->constants->remoteServer->fifoQueue.pop();
	this->constants->cache->insertFile(fileId, this->constants->remoteServer->getFile(fileId+1));
	//error here I think/
	this-constants->remoteServer->queuePop.erase(this->fileId);
	if ( this->constants->remoteServer->waitingMap.find(this->fileId) != this->constants->remoteServer->waitingMap.end() ) {
		while (!this->constants->remoteServer->waitingMap[this->fileId].empty()){
			//cout << "\t getting " << this->fileId << " from the endMap" << endl;
			this->initTime = this->initTime - (this->execTime + this->constants->remoteServer->getFile(this->fileId + 1)/this->constants->cacheBandwidth - this->constants->remoteServer->waitingMap	[this->fileId][0]);
			//cout << "\t\t " << this->initTime << endl;
			this->constants->remoteServer->waitingMap[this->fileId].erase(this->constants->remoteServer->waitingMap[this->fileId].begin());
		}
	}
	returnEvents[0] = new FileArriveEvent(this->initTime, this->execTime + this->constants->remoteServer->getFile(this->fileId + 1)/this->constants->cacheBandwidth, this->fileId, this->constants);
	if (!this->constants->remoteServer->fifoQueue.empty()){
		fileId = this->constants->remoteServer->fifoQueue.front();
		returnEvents[1] = new FileLeaveQueueEvent(this->initTime, this->execTime + this->constants->remoteServer->getFile(fileId + 1)/this->constants->fifoBandwidth, fileId, this->constants);
		return 2;
	}
	return 1;
}
