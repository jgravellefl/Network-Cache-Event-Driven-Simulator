#include "FileArriveEvent.h"

FileArriveEvent::FileArriveEvent() : Event(){}
FileArriveEvent::FileArriveEvent(float initTime, float execTime, int fileId, Constants* constants) : Event(initTime, execTime, fileId, constants){}

int FileArriveEvent::process(Event** returnEvents){
 this->constants->totalTime = this->constants->totalTime + this->execTime - this->initTime;
 //cout << "file " << this->fileId << " arrived at time: " << this->execTime << endl;
 return 0;
}