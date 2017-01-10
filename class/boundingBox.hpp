#include <bits/stdc++.h>
#include "particles.hpp"
#include "eventQueue.hpp"

class boundingBox
{
private:
	vector<Particle> particlesInBox;
	eventQueue events;
public:

	//Returns the event object in case of collision between particle
	//and the box.
	event getCollisionEventP2B(Particle partA){
		int timeOfCollision=getTimeOfCollisionP2B(
			partA.getMovementData(),
			partA.getCordinates());
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
			partB.getCordinates());
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

	//Which side does it collide with (returns an integer)
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