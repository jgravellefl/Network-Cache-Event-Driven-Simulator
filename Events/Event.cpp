#include "Event.h"
#include <iostream>

Event::Event(float origTime, float execTime, int fileId, Constants* constants){
	this->origTime = origTime;
	this->execTime = execTime;
	this->fileId = fileId;
	this->constants = constants;
}
Event::Event(){
	this->fileId = 0;
}
/*bool operator<(const Event& lhs, const Event& rhs)
{
  return lhs.execTime < rhs.execTime;
}*/