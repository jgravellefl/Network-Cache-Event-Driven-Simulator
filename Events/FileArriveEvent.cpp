#include "FileArriveEvent.h"

FileArriveEvent::FileArriveEvent() : Event(){}
FileArriveEvent::FileArriveEvent(float execTime, int fileId, Constants* constants) : Event(execTime, fileId, constants){}

int FileArriveEvent::process(Event** returnEvents){
 cout << "file arrive event" << endl;
 cout << "\tfile: " << this->fileId << endl;
 cout << "\tExecTime: " << this->execTime << endl; 
 this->constants->totalTime = this->execTime;
 return 0;
}