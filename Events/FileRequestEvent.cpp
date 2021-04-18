#include "FileRequestEvent.h"
#include <iostream>

FileRequestEvent::FileRequestEvent() : Event(){}
FileRequestEvent::FileRequestEvent(float initTime, float execTime, int fileId, Constants* constants) : Event(initTime, execTime, fileId, constants){
  std::random_device rd;
		mt19937 gen(rd());
  		this->generator =  gen;
		poisson_distribution<int> distribution(this->constants->poissonMean);
		this->poissonDist = distribution;
}

int FileRequestEvent::process(Event** returnEvents){ 
	//cout << "requesting file: " << this->fileId << " at time " << this->execTime << endl;
	//cout << "current files in cache: " << endl;
	/*for (int i = 0; i < this->constants->remoteServer->currSize; i++){
		if (this->constants->cache->getFile(i) != -1){
			cout << "\t " << i << endl;
		}
	}*/
	if (this->constants->numRequests > 1){
	 	int sampleTime = this->poissonDist(this->generator) + this->execTime;
		returnEvents[0] = new FileRequestEvent(sampleTime, sampleTime, this->constants->fileSelector->getFile(), this->constants);
		if (this->constants->cache->getFile(this->fileId) != -1){
			returnEvents[1] = new FileArriveEvent(this->initTime, this->execTime + (this->constants->remoteServer->getFile(this->fileId)/this->constants->cacheBandwidth),this->fileId ,this->constants);
		}
		else{
			if (this->constants->remoteServer->queuePop.count(this->fileId) == 0){
				returnEvents[1] = new FileEnterQueueEvent(this->initTime, this->execTime + this->constants->remoteServer->propagationTime, this->fileId, this->constants);
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
		if (this->constants->cache->getFile(this->fileId) != -1){
			returnEvents[0] = new FileArriveEvent(this->initTime, this->execTime + (this->constants->remoteServer->getFile(this->fileId)/this->constants->cacheBandwidth),this->fileId ,this->constants);
		}
		else{
			if (this->constants->remoteServer->queuePop.count(this->fileId) == 0){
				returnEvents[0] = new FileEnterQueueEvent(this->initTime, this->execTime + this->constants->remoteServer->propagationTime, this->fileId, this->constants);
				this->constants->remoteServer->queuePop.insert(this->fileId);
			}
			else{
				return 0;
			}
		}
		return 1;
	}
}