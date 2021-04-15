#include "FileRequestEvent.h"
#include <iostream>

FileRequestEvent::FileRequestEvent() : Event(){}
FileRequestEvent::FileRequestEvent(float execTime, int fileId, Constants* constants) : Event( execTime, fileId, constants){
  std::random_device rd;
		mt19937 gen(rd());
  		this->generator =  gen;
		poisson_distribution<int> distribution(this->constants->poissonMean);
		this->poissonDist = distribution;
}

int FileRequestEvent::process(Event** returnEvents){
	cout << "file request event" << endl;
	 cout << "\tfile: " << this->fileId << endl;
	 cout << "\tExecTime: " << this->execTime << endl; 
	if (this->constants->numRequests > 1){
	 	int sampleTime = this->poissonDist(this->generator) + this->execTime;
		returnEvents[0] = new FileRequestEvent(sampleTime, this->constants->fileSelector->getFile(), this->constants);
		if (this->constants->LRUcache->getFile(this->fileId) != -1){
			returnEvents[1] = new FileArriveEvent(this->execTime + (this->constants->remoteServer->getFile(this->fileId)/this->constants->cacheBandwidth),this->fileId ,this->constants);
		}
		else{
			if (this->constants->remoteServer->queuePop.count(this->fileId) == 0){
				returnEvents[1] = new FileEnterQueueEvent(this->execTime + this->constants->remoteServer->propagationTime, this->fileId, this->constants);
				this->constants->remoteServer->queuePop.insert(this->fileId);
			}
			else{
				this->constants->numRequests  = this->constants->numRequests -1;
				return 1;
			}
		}
		this->constants->numRequests  = this->constants->numRequests -1;
		return 2;
	}
	else {
		int sampleTime = this->poissonDist(this->generator) + this->execTime;
		if (this->constants->LRUcache->getFile(this->fileId) != -1){
			returnEvents[0] = new FileArriveEvent(this->execTime + (this->constants->remoteServer->getFile(this->fileId)/this->constants->cacheBandwidth),this->fileId ,this->constants);
		}
		else{
			if (this->constants->remoteServer->queuePop.count(this->fileId) == 0){
				returnEvents[0] = new FileEnterQueueEvent(this->execTime + this->constants->remoteServer->propagationTime, this->fileId, this->constants);
				this->constants->remoteServer->queuePop.insert(this->fileId);
			}
			else{
				return 0;
			}
		}
		return 1;
	}
}