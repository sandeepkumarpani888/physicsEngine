#include <bits/stdc++.h>
#include "movement.hpp"

class Particle
{

private:
	Movement move;
	int mass;

public:
	Particle(){
		move=Movement();
		mass=100;
	};

	Particle(Movement _move,int _mass){
		this->move=_move;
		this->mass=_mass;
	};

	Movement getMovementData(){
		return this->move;
	};

	int getMass(){
		return this->mass;
	}

	void setMass(int _mass){
		this->mass=_mass;
	}
};