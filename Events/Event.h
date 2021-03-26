#pragma once

#include "../Cache/Cache.h"
#include "../Constants/Constants.h"

class Event
{
	private:
		
	public:
		float origTime;
		float execTime;
	 int fileId;
		Constants* constants;
		Event(float origTime, float nextTime, int fileId, Constants* constants);
		Event* process();
		Event();
};