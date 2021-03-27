#include "FileArriveEvent.h"

FileArriveEvent::FileArriveEvent() : Event(){}
FileArriveEvent::FileArriveEvent(float origTime, float execTime, int fileId, Constants* constants) : Event(origTime, execTime, fileId, constants){}

Event* FileArriveEvent::process(){

	return;
}