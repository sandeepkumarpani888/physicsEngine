#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "bits/stdc++.h"
#include "unistd.h"
#include "class/physics.hpp"
#include "class/boundingBox.hpp"

using namespace std;
using namespace cv;

int main(int argc,char** argv){
	char imageName[]="Drawing1";
	Mat atom_image=Mat::zeros(w,w,CV_8UC3);
	Physics py;
	BoundingBox bb;
	Particle partA;
	Particle partB;
	Particle partC;
	std::tuple<int,int> cordC=std::make_tuple(10,200);
	std::tuple<int,int> cordA=std::make_tuple(10,300);
	std::tuple<int,int> cordB=std::make_tuple(10,400);
	std::tuple<double,double> velC=std::make_tuple(10,10);
	std::tuple<double,double> velA=std::make_tuple(10,10);
	std::tuple<double,double> velB=std::make_tuple(10,-20);
	partA.setCordinates(cordA);
	partB.setCordinates(cordB);
	partC.setCordinates(cordC);
	partA.setVelocity(velA);
	partB.setVelocity(velB);
	partC.setVelocity(velC);
	bb.addParticle(partA);
	bb.addParticle(partB);
	bb.addParticle(partC);
	bb.startSimulation();
return 0;}