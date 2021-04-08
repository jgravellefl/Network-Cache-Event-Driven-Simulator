#include "Event.h"

Event::Event(float execTime, int fileId, Constants* constants){
	this->execTime = execTime;
	this->fileId = fileId;
	this->constants = constants;
}
Event::Event(){
	this->fileId = 0;
}