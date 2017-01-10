#include <bits/stdc++.h>
#include "particle.hpp"
#include "tupleOperations.hpp"

class physics
{
private:
	TupleOperations tO;
public:

	//Class construtor
	physics(){
		printf("Creating object for physics\n");
	};

	//Gets the side of the wall with which to collide.
	int getSideToCollideWith(Movement move){
		//TODO
	}

	//Gets the time of collision of the particle with the wall.
	int getTimeOfCollisionP2P(Movement movA,
		Movement movB,
		std::tuple<int,int> cordA,
		std::tuple<int,int> cordB){
		//TODO
	}

	//Gets the time of collision of the two particles.
	int getTimeOfCollisionP2B(Movement movA,set::tuple<int,int> corA){
		//TODO
	}

	//Gets the finalVelocities of the particles after the collision.
	pair<Movement,Movement> getFinalVelocities(Particle particleA,Particle particleB){
		Movement moveA=particleA.getMovementData();
		Movement moveB=particleB.getMovementData();
		int massA=particleA.getMass();
		int massB=particleB.getMass();
		std::tuple<double,double> velA=moveA.getVelocity();
		std::tuple<double,double> velB=moveB.getVelocity();
		std::tuple<double,double> finalVelA=tO.dT(
			tO.aT(tO.sM(velA,(massA-massB)),tO.sM(velB,2*massA)),
			massA+massB);
		std::tuple<double,double> finalVelB=tO.dT(
			tO.aT(tO.sM(velB,(massB-massA)),tO.sM(valA,2*massB)),
			massA+massB);
		moveA.setVelocity(finalVelA);
		moveB.setVelocity(finalVelB);
	}
};