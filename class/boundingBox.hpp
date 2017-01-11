#include <bits/stdc++.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "particle.hpp"
#include "eventQueue.hpp"
#include "physics.hpp"
#include "timeKeeper.hpp"

const char imageName[]="Output";
#define w 4000

class BoundingBox
{
private:
	std::vector<Particle> particlesInBox;
	EventQueue events;
	Physics py;
public:

	BoundingBox(){
		this->particlesInBox.clear();
	};

	//Returns the event object in case of collision between particle
	//and the box.
	Event getCollisionEventP2B(Particle partA){
		int timeOfCollision=py.getTimeOfCollisionP2B(
			partA.getMovementData(),
			partA.getCordinates(),
			partA.getRadius());
		Particle partB;
		partB.setMass(-1);
		return Event{timeOfCollision,partA,partB};
	}

	//Returns the event object in case of collision between the given
	//particles.
	Event getCollisionEventP2P(Particle partA,Particle partB){
		int timeOfCollision=py.getTimeOfCollisionP2P(
			partA.getMovementData(),
			partB.getMovementData(),
			partA.getCordinates(),
			partB.getCordinates(),
			partA.getRadius(),
			partB.getRadius());
		return Event{timeOfCollision,partA,partB};
	}

	//Computes all the collision events between every pair of particles.
	void compute(){
		events.clear();
		int numParticles=(int)particlesInBox.size();
		for(int i=0;i<numParticles;i++){
			for(int j=i+1;j<numParticles;j++){
				Event collisionEvent=getCollisionEventP2P(
					particlesInBox[i],
					particlesInBox[j]);
				events.push(collisionEvent);
			}
		}

		for(int i=0;i<numParticles;i++){
			Event collisionEvent=getCollisionEventP2B(
				particlesInBox[i]);
			events.push(collisionEvent);
		}
	}

	void drawCircle(cv::Mat image,std::tuple<int,int> _pos){
		int thickness=2;int lineType=2;
		cv::Point centre;centre.x=std::get<0>(_pos);centre.y=std::get<1>(_pos);
		cv::circle(image,
			centre,
			w/32,
			cv::Scalar(0,125,255),
			thickness,
			lineType);
	}

	void reDraw(cv::Mat atom_image){
		int numParticles=(int)particlesInBox.size();
		atom_image=cv::Mat::zeros(w,w,CV_8UC3);
		
		for(int i=0;i<numParticles;i++){
			drawCircle(atom_image,this->particlesInBox[i].getCordinates());
		}

		cv::imshow(imageName,atom_image);
		
		for(int i=0;i<numParticles;i++){
			this->particlesInBox[i].updatePosition();
		}
	}

	//The function that starts it all.
	void startSimulation(){
		TimeKeeper tk;
		cv::Mat atom_image=cv::Mat::zeros(w,w,CV_8UC3);
		cv::imshow(imageName,atom_image);
		this->reDraw(atom_image);
		for(int i=0;i<1010;i++){
			int currTime=tk.getCurrentTime();
			if(events.isEventOccur(currTime)){
				this->compute();
			}
			this->reDraw(atom_image);
			tk.incrementTime();
		}
	}

	//Function which will allow the addition of particles into the box.
	void addParticle(Particle _particle){
		this->particlesInBox.push_back(_particle);
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