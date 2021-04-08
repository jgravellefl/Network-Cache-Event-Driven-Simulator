#pragma once

#include "../Constants/Constants.h"
#include <iostream>

class Event
{
	private:
		
	public:
		float execTime;
	 	int fileId;
		Constants* constants;
		Event(float nextTime, int fileId, Constants* constants);
		virtual int process(Event** currentEvent){cout << "running event" << endl; return 0;};
		Event();
		~Event(){};
};
//bool operator<(const Event& lhs, const Event& rhs); 

struct LessThanByTime
{
  bool operator()(const Event* lhs, const Event* rhs) const
  {
    return lhs->execTime > rhs->execTime;
  }
};