#include "FileRequestEvent.h"
#include <iostream>

FileRequestEvent::FileRequestEvent() : Event(){}
FileRequestEvent::FileRequestEvent(float origTime, float execTime, int fileId, Constants* constants) : Event(origTime, execTime, fileId, constants){
  std::random_device rd;
		mt19937 gen(rd());
  this->generator =  gen;
		poisson_distribution<int> distribution(this->constants->poissonMean);
		this->poissonDist = distribution;
}

void FileRequestEvent::process(Event** returnEvents){
	
	if (this->constants->numRequests > 0){
	 int sampleTime = this->poissonDist(this->generator) + this->execTime;
		returnEvents[1] = new FileRequestEvent(sampleTime, sampleTime, this->fileId + 1, this->constants);
		returnEvents[0] = returnEvents[1];
		this->constants->numRequests  = this->constants->numRequests -1;
	}
}