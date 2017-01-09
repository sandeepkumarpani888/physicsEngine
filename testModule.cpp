#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "bits/stdc++.h"
#include "unistd.h"

#define w 4000

using namespace std;
using namespace cv;

tuple<int,int> getNextPosition(tuple<int,int> pos,tuple<double,double> vel){
	tuple<int,int> finalPos=pos;
	get<0>(finalPos)=get<0>(finalPos)+(int)get<0>(vel)*3;
	get<1>(finalPos)=get<1>(finalPos)+(int)get<1>(vel)*3;
	return finalPos;
}

void drawCircle(Mat image,tuple<int,int> pos){
	int thickness=2;
	int lineType=2;
	Point centre;
	centre.x=get<0>(pos);
	centre.y=get<1>(pos);
	printf("%d %d\n",centre.x,centre.y);
	circle(image,
		centre,
		w/32,
		Scalar(0,125,255),
		thickness,
		lineType
		);
	printf("exiting function\n");
}

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