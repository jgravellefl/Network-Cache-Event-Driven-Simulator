#include "FileArriveEvent.h"

FileArriveEvent::FileArriveEvent() : Event(){}
FileArriveEvent::FileArriveEvent(float origTime, float execTime, int fileId, Constants* constants) : Event(origTime, execTime, fileId, constants){}

void FileArriveEvent::process(Event** returnEvents){
 this->constants->totalTime += this->execTime - this->origTime;
}