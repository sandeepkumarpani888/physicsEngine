#include <bits/stdc++.h>
#include "movement.hpp"

class Particle
{

private:
	Movement move;
	int mass;
	int radius;

public:
	Particle(){
		move=Movement();
		mass=100;
		radius=20;
	};

	Particle(Movement _move,int _mass,int _radius){
		this->move=_move;
		this->mass=_mass;
		this->radis=_radius;
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

	int getRadius(){
		return this->radius;
	}
};