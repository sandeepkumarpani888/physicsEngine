#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <bits/stdc++.h>
#include "particle.hpp"
#include "tupleOperations.hpp"

class Physics
{
private:
	TupleOperations tO;
public:

	//Gets the side of the wall with which to collide.
	int getSideToCollideWith(Movement move){
		//TODO
	}

	//Gets the time of collision of the particle with the wall.
	double getTimeOfCollisionP2P(Movement movA,
		Movement movB,
		std::tuple<int,int> cordA,
		std::tuple<int,int> cordB,
		int radiusA,
		int radiusB){
		std::tuple<double,double> velA=movA.getVelocity();
		std::tuple<double,double> velB=movB.getVelocity();
		bool xCorSame=tO.isSameI(std::get<0>(cordA),std::get<0>(cordB));
		bool yCorSame=tO.isSameI(std::get<1>(cordA),std::get<1>(cordB));
		bool xVelSame=tO.isSameD(std::get<0>(velA),std::get<0>(velB));
		bool yVelSame=tO.isSameD(std::get<1>(velA),std::get<1>(velB));
		if(xCorSame && yCorSame){
			return 0.0;
		}
		else if(xCorSame && !yCorSame){
			double timeY=(std::get<1>(cordA)-std::get<1>(cordB))/(std::get<1>(velA)-std::get<1>(velB));
			if(xVelSame){
				if(timeY>=0){
					return timeY;
				}
			}
		}
		else if(!xCorSame && yCorSame){
			double timeX=(std::get<0>(cordA)-std::get<0>(cordB))/(std::get<0>(velA)-std::get<0>(velB));
			if(yVelSame){
				if(timeX>=0){
					return timeX;
				}
			}
		}
		else if(!xCorSame && !yCorSame){
			double timeX=(std::get<0>(cordA)-std::get<0>(cordB))/(std::get<0>(velA)-std::get<0>(velB));
			double timeY=(std::get<1>(cordA)-std::get<1>(cordB))/(std::get<1>(velA)-std::get<1>(velB));
			if(tO.isSameD(timeX,timeY) && timeX>=0.0){
				return timeX;
			}
		}
		return -1.0;
	}

	//Gets the time of collision of the two particles.
	int getTimeOfCollisionP2B(
		Movement movA,
		std::tuple<int,int> corA,
		int radius){
		//TODO
	}

	//Gets the finalVelocities of the particles after the collision.
	std::pair<Movement,Movement> getFinalVelocities(Particle particleA,Particle particleB){
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
			tO.aT(tO.sM(velB,(massB-massA)),tO.sM(velA,2*massB)),
			massA+massB);
		moveA.setVelocity(finalVelA);
		moveB.setVelocity(finalVelB);
	}
};

#endif