#include "Event.h"

#include <stdio.h>
#include <time.h>
#include "Event.h"

Event::Event(time_t origTime, time_t execTime, int fileId){
	this->origTime = origTime;
	this->execTime = execTime;
	this->fileId = fileId;
}
Event::Event(){
	this->fileId = 0;
}