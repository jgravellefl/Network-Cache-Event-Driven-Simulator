#include "FileLeaveQueueEvent.h"

FileLeaveQueueEvent::FileLeaveQueueEvent() : Event(){}
FileLeaveQueueEvent::FileLeaveQueueEvent(float execTime, int fileId, Constants* constants) : Event(execTime, fileId, constants){}

int FileLeaveQueueEvent::process(Event** returnEvents){
	//this->constants->cache->insertFile() this file
	cout << "file leave queue event" << endl;
	 cout << "\tfile: " << this->fileId << endl;
	 cout << "\tExecTime: " << this->execTime << endl; 

	int fileId = this->constants->remoteServer->fifoQueue.front();
	cout << "\tfileID gotten: " << fileId << endl;
	this->constants->remoteServer->fifoQueue.pop();
	this->constants->cache->insertFile(fileId, this->constants->remoteServer->getFile(fileId));
	cout << "hello" << endl;
	//error here I think/
	this-constants->remoteServer->queuePop.erase(this->fileId);
	cout << "yello" << endl;
	returnEvents[0] = new FileArriveEvent(this->execTime + this->constants->remoteServer->getFile(this->fileId)/this->constants->cacheBandwidth, this->fileId, this->constants);
	cout << "queue emtpy status; " << this->constants->remoteServer->fifoQueue.empty() << endl;
	cout << "queue value: " << endl;
	cout << "\tsize: " << this->constants->remoteServer->fifoQueue.size() << endl;
	cout << "\t top: " << this->constants->remoteServer->fifoQueue.front() << endl;
	cout << "\t remote server valid? propagation time: " << this->constants->remoteServer->propagationTime << endl;;
	if (!this->constants->remoteServer->fifoQueue.empty()){
		fileId = this->constants->remoteServer->fifoQueue.front();
		cout << fileId << endl;
		returnEvents[1] = new FileLeaveQueueEvent(this->execTime + this->constants->remoteServer->getFile(fileId)/this->constants->fifoBandwidth, fileId, this->constants);
		return 2;
	}
	return 1;
}
