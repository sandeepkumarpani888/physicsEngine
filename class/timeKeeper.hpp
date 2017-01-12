#ifndef TIMEKEEPER_H_
#define TIMEKEEPER_H_

#include <bits/stdc++.h>

class TimeKeeper
{
private:
	int currentTimeMilli;
	int delta;
	bool startedBefore;
public:
	TimeKeeper(){
		currentTimeMilli=0;
		delta=1;
		startedBefore=false;
	};

	int getCurrentTime(){
		return this->currentTimeMilli;
	}

	void incrementTime(){
		this->currentTimeMilli+=this->delta;
	}

	void startTime(){
		if(!this->startedBefore){
			this->startedBefore=true;
			this->currentTimeMilli=0;
		}
	}
};

#endif