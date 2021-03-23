#pragma once

#include <stdio.h>
#include <time.h>

class Event
{
	private:
		time_t origTime;
		time_t execTime;
		int fileId;
	public:
		Event(time_t origTime, time_t nextTime, int fileId);
		Event* process();
		Event();
};