#pragma once

#include "../Constants/Constants.h"
#include <iostream>

class Event
{
	private:
		
	public:
		float origTime;
		float execTime;
	 int fileId;
		Constants* constants;
		Event(float origTime, float nextTime, int fileId, Constants* constants);
		virtual void process(Event** currentEvent){cout << "running event" << endl;return;};
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