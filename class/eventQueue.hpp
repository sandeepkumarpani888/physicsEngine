#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

#include <bits/stdc++.h>
#include "particle.hpp"

class Event{
private:
	int time;
	Particle part1;
	Particle part2;
public:

	Event(int _time,Particle _part1,Particle _part2){
		this->time=_time;
		this->part1=_part1;
		this->part2=_part2;
	}

	int getTime(){
		return this->time;
	}
	
	bool operator<(const Event &other) const{
		return this->time>other.time;
	}
};

class EventQueue
{
private:
	std::priority_queue<Event> eventQueue;

public:

	EventQueue(){
		while(!eventQueue.empty()){
			eventQueue.pop();
		}
	}

	void clear(){
		while(!eventQueue.empty()){
			eventQueue.pop();
		}
	}

	void push(Event _event){
		eventQueue.push(_event);
	}


	//Tells if an event is going to occur at the present time.
	bool isEventOccur(int _time){
		if(eventQueue.empty()){
			return false;
		}
		else{
			Event mostImportantEvent=eventQueue.top();
			if(mostImportantEvent.getTime()==_time){
				return true;
			}
			else{
				return false;
			}
		}
	}
};

#endif