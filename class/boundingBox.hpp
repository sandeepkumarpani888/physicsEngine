#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_

#include <bits/stdc++.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "particle.hpp"
#include "eventQueue.hpp"
#include "physics.hpp"
#include "timeKeeper.hpp"

const char imageName[]="Output";
#define w 500

class BoundingBox
{
private:
	std::vector<Particle> particlesInBox;
	EventQueue events;
	Physics py;
	TimeKeeper tk;
public:

	BoundingBox(){
		this->particlesInBox.clear();
	};

	//Returns the event object in case of collision between particle
	//and the box.
	Event getCollisionEventP2B(Particle partA){
		std::pair<double,int> timeDirOfCollision=py.getTimeDirectionOfCollisionP2B(
			partA.getMovementData(),
			partA.getCordinates(),
			partA.getRadius(),
			w);
		if(((int)ceil(timeDirOfCollision.first))!=-1){
			Particle partB;
			partB.setMass(-1);
			partB.setIndex(timeDirOfCollision.second);
			return Event{(int)(ceil(timeDirOfCollision.first))+tk.getCurrentTime(),partA,partB,1};
		}
	}

	//Returns the event object in case of collision between the given
	//particles.
	Event getCollisionEventP2P(Particle partA,Particle partB){
		int timeOfCollision=ceil(py.getTimeOfCollisionP2P(
			partA.getMovementData(),
			partB.getMovementData(),
			partA.getCordinates(),
			partB.getCordinates(),
			partA.getRadius(),
			partB.getRadius()));
		if(timeOfCollision==-1){
			return Event{-1,partA,partB,0};
		}
		else{
			timeOfCollision+=tk.getCurrentTime();
			return Event{timeOfCollision,partA,partB,0};
		}
	}

	//Computes all the collision events between every pair of particles.
	void compute(){
		events.clear();
		printf("RUNNING COMPUTATION\n");
		int numParticles=(int)particlesInBox.size();
		for(int i=0;i<numParticles;i++){
			for(int j=i+1;j<numParticles;j++){
				Event collisionEvent=getCollisionEventP2P(
					particlesInBox[i],
					particlesInBox[j]);
				if(collisionEvent.getTime()!=-1){
					printf("EVENTS: (time = %d) %d %d\n",collisionEvent.getTime(),i,j);
					events.push(collisionEvent);
				}
			}
		}

		for(int i=0;i<numParticles;i++){
			Event collisionEvent=getCollisionEventP2B(
				particlesInBox[i]);
			printf("EVENTS WITH WALL: %d\n",collisionEvent.getTime());
			if(collisionEvent.getTime()!=-1){
				events.push(collisionEvent);
			}
		}
	}

	void drawCircle(cv::Mat image,std::tuple<int,int> _pos,int index){
		int thickness=2;int lineType=2;
		cv::Point centre;centre.x=std::get<0>(_pos);centre.y=std::get<1>(_pos);
		cv::circle(image,
			centre,
			w/64,
			cv::Scalar(index*100,index*100,255),
			thickness,
			lineType);
	}

	void reDraw(cv::Mat atom_image){
		int numParticles=(int)particlesInBox.size();
		atom_image=cv::Mat::zeros(w,w,CV_8UC3);
		
		for(int i=0;i<numParticles;i++){
			drawCircle(atom_image,this->particlesInBox[i].getCordinates(),i);
		}

		cv::imshow(imageName,atom_image);
		
		for(int i=0;i<numParticles;i++){
			this->particlesInBox[i].updatePosition();
		}
	}

	void printVelocities(){
		int numParticles=this->particlesInBox.size();
		for(int i=0;i<numParticles;i++){
			std::tuple<double,double> vel=this->particlesInBox[i].getVelocity();
			printf("INDEX:(%d) VELOCITY:(%.6lf,%.6lf)\n",i,std::get<0>(vel),std::get<1>(vel));
		}
	}

	void printPosition(){
		int numParticles=this->particlesInBox.size();
		for(int i=0;i<numParticles;i++){
			std::tuple<int,int> pos=this->particlesInBox[i].getCordinates();
			printf("INDEX:(%d) POSITION:(%d,%d)\n",i,std::get<0>(pos),std::get<1>(pos));
		}
	}

	//Update the velocities of the particle after collision.
	void updateParticles(Event currEvent){
		if(currEvent.getType()==0){
			std::vector<Particle> particlesInvolved=currEvent.getParticles();
			assert(particlesInvolved.size()==2);
			std::tuple<double,double> velA=particlesInvolved[0].getVelocity();
			std::tuple<double,double> velB=particlesInvolved[1].getVelocity();
			// printf("PARTICLES: (%d %d)\n",particlesInvolved[0].getIndex(),particlesInvolved[1].getIndex());
			// printf("INITIAL: FirstParticle: (%.6lf,%.6lf)\n",std::get<0>(velA),std::get<1>(velA));
			// printf("INITIAL: SecondParticle: (%.6lf,%.6lf)\n",std::get<0>(velB),std::get<1>(velB));
			std::pair<Movement,Movement> finalMovement=py.getFinalVelocities(
				particlesInvolved[0],
				particlesInvolved[1]);
			int firstIndex=particlesInvolved[0].getIndex();
			int secondIndex=particlesInvolved[1].getIndex();
			this->particlesInBox[firstIndex].setVelocity(finalMovement.first.getVelocity());
			this->particlesInBox[secondIndex].setVelocity(finalMovement.second.getVelocity());
			velA=this->particlesInBox[firstIndex].getVelocity();
			velB=this->particlesInBox[secondIndex].getVelocity();
			// printf("FINAL: FirstParticle(%d): (%.6lf,%.6lf)\n",firstIndex,std::get<0>(velA),std::get<1>(velA));
			// printf("FINAL: SecondParticle(%d): (%.6lf,%.6lf)\n",secondIndex,std::get<0>(velB),std::get<1>(velB));
		}
		else if(currEvent.getType()==1){
			std::vector<Particle> particlesInvolved=currEvent.getParticles();
			assert(particlesInvolved.size()==2);
			int sideOfWall=particlesInvolved[1].getIndex();
			int particleIndex=particlesInvolved[0].getIndex();
			std::tuple<double,double> velA=particlesInvolved[0].getVelocity();
			if(sideOfWall==0 || sideOfWall==2){
				std::get<1>(velA)=-std::get<1>(velA);
			}
			else if(sideOfWall==1 || sideOfWall==3){
				std::get<0>(velA)=-std::get<0>(velA);
			}
			this->particlesInBox[particleIndex].setVelocity(velA);
		}
	}

	//The function that starts it all.
	void startSimulation(){
		printf("SIMULATION STARTS\n");
		tk.startTime();
		cv::Mat atom_image=cv::Mat::zeros(w,w,CV_8UC3);
		cv::imshow(imageName,atom_image);
		this->reDraw(atom_image);
		this->compute();
		for(int i=0;i<1010;i++){
			bool doesEventOccur=false;
			int currTime=tk.getCurrentTime();
			printf("currentTime: %d\n",currTime);
			events.clearRedundant(currTime);
			while(events.isEventOccur(currTime)){
				this->updateParticles(events.getEvent());
				doesEventOccur=true;
			}
			this->reDraw(atom_image);
			printf("DOES EVENT OCCUR %d\n",doesEventOccur);
			if(doesEventOccur){
				printf("EVENT OCCURS\n");
				this->compute();
			}
			this->printVelocities();
			this->printPosition();
			cv::waitKey(0);
			tk.incrementTime();
		}
		// cv::waitKey(0);
	}

	//Function which will allow the addition of particles into the box.
	void addParticle(Particle _particle){
		_particle.setIndex((int)this->particlesInBox.size());
		this->particlesInBox.push_back(_particle);
		printf("Particle INDEX: %d\n",this->particlesInBox[this->particlesInBox.size()-1].getIndex());
	}

};

#endif