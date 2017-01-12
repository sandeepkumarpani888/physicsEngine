#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <bits/stdc++.h>
#include "movement.hpp"

class Particle
{

private:
	Movement move;
	int mass;
	int radius;
	int index;
	bool isIndexSet;

public:
	Particle(){
		move=Movement();
		mass=100;
		radius=20;
		index=-1;
		isIndexSet=false;
	};

	Particle(Movement _move,int _mass,int _radius){
		this->move=_move;
		this->mass=_mass;
		this->radius=_radius;
	};

	void updatePosition(){
		Movement _move=this->move;
		std::tuple<int,int> pos=_move.getCordinates();
		std::tuple<double,double> vel=_move.getVelocity();
		std::get<0>(pos)+=(int)std::get<0>(vel);
		std::get<1>(pos)+=(int)std::get<1>(vel);
		this->move.setCordinates(pos);
	}

	void setIndex(int _index){
		if(!this->isIndexSet){
			this->isIndexSet=true;
			this->index=_index;
		}
	}

	Movement getMovementData(){
		return this->move;
	};

	int getMass(){
		return this->mass;
	}

	void setMass(int _mass){
		this->mass=_mass;
	}

	int getRadius(){
		return this->radius;
	}

	void setRadius(int _radius){
		this->radius=_radius;
	}

	void setCordinates(std::tuple<int,int> _cord){
		this->move.setCordinates(_cord);
	}

	void setVelocity(std::tuple<double,double> _vel){
		this->move.setVelocity(_vel);
	}

	std::tuple<int,int> getCordinates(){
		return this->move.getCordinates();
	}

	std::tuple<double,double> getVelocity(){
		return this->move.getVelocity();
	}

	int getIndex(){
		return this->index;
	}
};

#endif