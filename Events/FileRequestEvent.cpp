#include "FileRequestEvent.h"
#include <iostream>

FileRequestEvent::FileRequestEvent() : Event(){}
FileRequestEvent::FileRequestEvent(float origTime, float execTime, int fileId, Constants* constants) : Event(origTime, execTime, fileId, constants){}

void FileRequestEvent::process(Event** returnEvents){
	cout <<"fileRequest event" << endl;
	
	cout << "numRequests: " << this->constants->numRequests << endl;
	if (this->constants->numRequests > 0){
		default_random_engine generator;
  poisson_distribution<int> distribution(this->constants->poissonMean);
	 int sampleTime = distribution(generator) + this->execTime;
		cout << sampleTime << endl; 
		returnEvents[1] = new FileRequestEvent(sampleTime, sampleTime, this->fileId + 1, this->constants);
		returnEvents[0] = returnEvents[1];
		cout << "og fileID: " << returnEvents[0]->fileId << endl;
		this->constants->numRequests  = this->constants->numRequests -1;
	}
}