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

	std::vector<Particle> getParticles(){
		std::vector<Particle> result={this->part1,this->part2};
		return result;
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

	//HELPS IN CLEARING DEPRECATED EVENTS
	void clearRedundant(int _time){
		while(!this->eventQueue.empty()){
			Event currentEvent=this->eventQueue.top();
			if(currentEvent.getTime()<_time){
				this->eventQueue.pop();
			}
			else{
				break;
			}
		}
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

	//Returns the most recent event and removes it from the eventQueue.
	Event getEvent(){
		assert(!this->eventQueue.empty());
		Event mostImportantEvent=eventQueue.top();
		eventQueue.pop();
		return mostImportantEvent;
	}
};

#endif