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

	//Gets the time of collision of the particle with the wall.
	double getTimeOfCollisionP2P(Movement movA,
		Movement movB,
		std::tuple<int,int> cordA,
		std::tuple<int,int> cordB,
		int radiusA,
		int radiusB){
		// printf("RUNNING getTimeOfCollisionP2P\n");
		std::tuple<double,double> velA=movA.getVelocity();
		std::tuple<double,double> velB=movB.getVelocity();
		bool xCorSame=tO.isSameI(std::get<0>(cordA),std::get<0>(cordB));
		bool yCorSame=tO.isSameI(std::get<1>(cordA),std::get<1>(cordB));
		bool xVelSame=tO.isSameD(std::get<0>(velA),std::get<0>(velB));
		bool yVelSame=tO.isSameD(std::get<1>(velA),std::get<1>(velB));
		printf("COLLISION WITH PARTICLE==\n");
		printf("CORDINATES(0): (%d,%d)\n",std::get<0>(cordA),std::get<1>(cordA));
		printf("CORDINATES(1): (%d,%d)\n",std::get<0>(cordB),std::get<1>(cordB));
		printf("VELOCITY(0): (%.6lf,%.6lf)\n",std::get<0>(velA),std::get<1>(velA));
		printf("VELOCITY(1): (%.6lf,%.6lf)\n",std::get<0>(velB),std::get<1>(velB));
		printf("%d %d %d %d\n",xCorSame,yCorSame,xVelSame,yVelSame);
		if(xVelSame && yVelSame){
			return -1.0;
		}
		if(xCorSame && yCorSame){
			return 0.0;
		}
		else if(xCorSame && !yCorSame){
			double timeY=-(std::get<1>(cordA)-std::get<1>(cordB))/(std::get<1>(velA)-std::get<1>(velB));
			if(xVelSame){
				if(timeY>=0){
					printf("xCorSame && !yCorSame (%.6lf)\n",timeY);
					return timeY;
				}
			}
		}
		else if(!xCorSame && yCorSame){
			double timeX=-(std::get<0>(cordA)-std::get<0>(cordB))/(std::get<0>(velA)-std::get<0>(velB));
			if(yVelSame){
				if(timeX>=0){
					printf("!xCorSame && yCorSame (%.6lf)\n",timeX);
					return timeX;
				}
			}
		}
		else if(!xCorSame && !yCorSame){
			double timeX=-(std::get<0>(cordA)-std::get<0>(cordB))/(std::get<0>(velA)-std::get<0>(velB));
			double timeY=-(std::get<1>(cordA)-std::get<1>(cordB))/(std::get<1>(velA)-std::get<1>(velB));
			if(tO.isSameD(timeX,timeY) && timeX>=0.0){
				printf("!xCorSame && !yCorSame (%.6lf)\n",timeX);
				return timeX;
			}
		}
		printf("INVALID EVENT\n");
		return -1.0;
	}

	//Gets the time and direction of collision of the two particles.
	std::pair<double,int> getTimeDirectionOfCollisionP2B(
		Movement movA,
		std::tuple<int,int> corA,
		int radius,
		int w){
		std::tuple<double,double> velParticle=movA.getVelocity();
		std::tuple<int,int> cordinate=movA.getCordinates();
		double velX=std::get<0>(velParticle);
		double velY=std::get<1>(velParticle);
		int cordX=std::get<0>(cordinate);
		int cordY=std::get<1>(cordinate);
		bool isVelXZero=tO.isZero(velX);
		bool isVelYZero=tO.isZero(velY);
		int sideToCollideX=-1;
		int sideToCollideY=-1;
		double timeY,timeX;
		if(isVelXZero && isVelYZero){
			return std::make_pair(-1.0,-1);
		}
		if(!isVelYZero){
			if(velY>=0){
				timeY=((double)(w-1-cordY))/velY;
				sideToCollideY=2;
			}
			else{
				timeY=-((double)cordY)/velY;
				sideToCollideY=0;
			}
		}
		if(!isVelXZero){
			if(velX>=0){
				timeX=((double)(w-1-cordX))/velX;
				sideToCollideX=3;
			}
			else{
				timeX=-((double)cordX)/velX;
				sideToCollideX=1;
			}
		}
		timeX=floor(timeX);
		timeY=floor(timeY);
		if(abs(timeX)==0){
			timeX=timeX+1;
		}
		if(abs(timeY)==0){
			timeY=timeY+1;
		}
		printf("COLLISION WITH WALL===\n");
		printf("VELOCITY: (%.6lf,%.6lf)\n",std::get<0>(velParticle),std::get<1>(velParticle));
		printf("CORDINATES: (%d,%d)\n",w-std::get<0>(cordinate),w-std::get<1>(cordinate));
		printf("TIME_TO_HIT_WALL: (%.6lf,%.6lf)\n",timeX,timeY);
		printf("IS_VELOCITY_ZERO: (%d,%d)\n",isVelXZero,isVelYZero);
		printf("SIDE_TO_COLLIDE: (%d,%d)\n",sideToCollideX,sideToCollideY);
		if(sideToCollideY==-1 || sideToCollideX==-1){
			if(sideToCollideX!=-1){
				return std::make_pair(timeX,sideToCollideX);
			}
			else if(sideToCollideY!=-1){
				return std::make_pair(timeY,sideToCollideY);
			}
			else{
				return std::make_pair(-1,sideToCollideX);
			}
		}
		else{
			if(timeY<timeX){
				return std::make_pair(timeY,sideToCollideY);
			}
			else{
				return std::make_pair(timeX,sideToCollideX);
			}
		}
	}

	//Gets the finalVelocities of the particles after the collision.
	std::pair<Movement,Movement> getFinalVelocities(Particle particleA,Particle particleB){
		Movement moveA=particleA.getMovementData();
		Movement moveB=particleB.getMovementData();
		int massA=particleA.getMass();
		int massB=particleB.getMass();
		std::tuple<double,double> velA=moveA.getVelocity();
		std::tuple<double,double> velB=moveB.getVelocity();
		std::tuple<double,double> finalVelA=velB;
		std::tuple<double,double> finalVelB=velA;
		bool isSameDirectX=tO.checkIsSameSign(std::get<0>(velA),std::get<0>(velB));
		bool isSameDirectY=tO.checkIsSameSign(std::get<1>(velA),std::get<1>(velB));
		// if(isSameDirectX && isSameDirectY){
		// 	//TODO Throw Error
		// }
		// if(!isSameDirectY){
		// 	printf("NOT SAME DIRECTION Y\n");
		// 	std::get<1>(finalVelA)=-std::get<1>(finalVelA);
		// 	std::get<1>(finalVelB)=-std::get<1>(finalVelB);
		// }
		// if(!isSameDirectX){
		// 	printf("NOT SAME DIRECTION X\n");
		// 	std::get<0>(finalVelA)=-std::get<0>(finalVelA);
		// 	std::get<0>(finalVelB)=-std::get<0>(finalVelB);
		// }
		printf("FINAL: FirstParticle: (%.6lf,%.6lf)\n",std::get<0>(finalVelA),std::get<1>(finalVelA));
		printf("FINAL: SecondParticle: (%.6lf,%.6lf)\n",std::get<0>(finalVelB),std::get<1>(finalVelB));
		moveA.setVelocity(finalVelA);
		moveB.setVelocity(finalVelB);
		return std::make_pair(moveA,moveB);
	}
};

#endif