#ifndef TIMEKEEPER_H_
#define TIMEKEEPER_H_

#include <bits/stdc++.h>

class TimeKeeper
{
private:
	int currentTimeMilli;
	int delta;
public:
	TimeKeeper(){
		currentTimeMilli=0;
		delta=100;
	};

	int getCurrentTime(){
		return this->currentTimeMilli;
	}

	void incrementTime(){
		this->currentTimeMilli+=this->delta;
	}
};

#endif