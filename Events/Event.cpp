#include "Event.h"

Event::Event(float origTime, float execTime, int fileId, Constants* constants){
	this->origTime = origTime;
	this->execTime = execTime;
	this->fileId = fileId;
}
Event::Event(){
	this->fileId = 0;
}