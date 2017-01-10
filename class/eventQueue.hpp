#include <bits/stdc++.h>
#include "particle.hpp"

class event{
	int time;
	Particle part1;
	Particle part2;
public:
	bool operator<(const even &other) const{
		return this->time>other.time;
	}
}

class eventQueue
{
private:
	priority_queue<event> eventQueue;

public:

	eventQueue(){
		eventQueue.clear();
	}

	//Tells if an event is going to occur at the present time.
	bool isEventOccur(int time){
		if(eventQueue.empty()){
			this->compute();
			return false;
		}
		else{
			if(eventQueue.top().time==time){
				return true;
			}
			else{
				return false;
			}
		}
	}
};