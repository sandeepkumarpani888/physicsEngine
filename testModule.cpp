#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "bits/stdc++.h"
#include "unistd.h"
#include "class/physics.hpp"

#define w 4000

using namespace std;
using namespace cv;

int main(int argc,char** argv){
	char imageName[]="Drawing1";
	Mat atom_image=Mat::zeros(w,w,CV_8UC3);
	
	imshow(imageName,atom_image);
	tuple<int,int> positionNow;
	tuple<double,double> vel;
	get<0>(vel)=get<1>(vel)=2;
	get<0>(positionNow)=get<1>(positionNow)=200;
	drawCircle(atom_image,positionNow);
	for(int i=0;i<=10;i++){
		atom_image=Mat::zeros(w,w,CV_8UC3);
		drawCircle(atom_image,positionNow);
		positionNow=getNextPosition(positionNow,vel);
		imshow("imageName",atom_image);
		waitKey(0);
	}
	waitKey(0);
return 0;}