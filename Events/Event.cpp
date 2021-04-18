#include "Event.h"

Event::Event(float initTime ,float execTime, int fileId, Constants* constants){
	this->execTime = execTime;
	this->fileId = fileId;
	this->constants = constants;
	this->initTime = initTime;
}
Event::Event(){
	this->fileId = 0;
}