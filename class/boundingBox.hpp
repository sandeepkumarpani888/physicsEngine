#include <bits/stdc++.h>
#include "particles.hpp"
#include "eventQueue.hpp"

class BoundingBox
{
private:
	vector<Particle> particlesInBox;
	eventQueue events;
public:

	//The function that starts it all.
	void startSimulation(){
		//qwe
	}

	//Returns the event object in case of collision between particle
	//and the box.
	event getCollisionEventP2B(Particle partA){
		int timeOfCollision=getTimeOfCollisionP2B(
			partA.getMovementData(),
			partA.getCordinates(),
			partA.getRadius());
		Particle partB;
		partB.setMass(-1);
		return event(timeOfCollision,partA,partB);
	}

	//Returns the event object in case of collision between the given
	//particles.
	event getCollisionEventP2P(Particle partA,Particle partB){
		int timeOfCollision=getTimeOfCollisionP2P(
			partA.getMovementData(),
			partB.getMovementData(),
			partA.getCordinates(),
			partB.getCordinates(),
			partA.getRadius(),
			partB.getRadius());
		return event(timeOfCollision,partA,partB);
	}

	//Computes all the collision events between every pair of particles.
	void compute(){
		events.clear();
		int numParticles=(int)std::particlesInBox.size();
		for(int i=0;i<numParticles;i++){
			for(int j=i+1;j<numParticles;j++){
				event collisionEvent=getCollisionEventP2P(
					particlesInBox[i],
					particlesInBox[j]);
				events.push(collisionEvent);
			}
		}

		for(int i=0;i<numParticles;i++){
			event collisionEvent=getCollisionEventP2B(
				particlesInBox[i]);
			events.push(collisionEvent);
		}
	}

	boundingBox(){
		particlesInBox.clear();
	};

	//Function which will allow the addition of particles into the box.
	void addParticle(Particle _particle){
		stdd::particlesInBox.push_back(_particle);
	}

	//Which side does it collide with (returns an integer).
	int whichSideCollides(){
		//TODO
	}	

	//Which (up)side does it collide with
	bool upBoxSideCollides(int side){
		if(side==0){
			return true;
		}
		else{
			return false;
		}
	}

	//Which (low)side does it collide with
	bool lowBoxSideCollides(int side){
		if(side==2){
			return true;
		}
		else{
			return false;
		}
	}

	//Which (right)side does it collide with
	bool rightBoxSideCollides(int side){
		if(side==1){
			return true;
		}
		else{
			return false;
		}
	}

	//Which (left)side does it collide with
	bool leftBoxSideCollides(int side){
		if(side==3){
			return true;
		}
		else{
			return false;
		}
	}
};