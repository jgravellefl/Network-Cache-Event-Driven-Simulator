#include "FileArriveEvent.h"

FileArriveEvent::FileArriveEvent() : Event(){}
FileArriveEvent::FileArriveEvent(float execTime, int fileId, Constants* constants) : Event(execTime, fileId, constants){}

int FileArriveEvent::process(Event** returnEvents){
 this->constants->totalTime = this->execTime;
 //cout << "file " << this->fileId << " arrived at time: " << this->execTime << endl;
 return 0;
}