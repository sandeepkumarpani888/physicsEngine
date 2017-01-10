#include <bits/stdc++.h>

class boundingBox
{
public:
	boundingBox();

	int whichSideCollides(){
		//TODO
	}	

	bool upBoxSideCollides(int side){
		if(side==0){
			return true;
		}
		else{
			return false;
		}
	}

	bool lowBoxSideCollides(int side){
		if(side==2){
			return true;
		}
		else{
			return false;
		}
	}

	bool rightBoxSideCollides(int side){
		if(side==1){
			return true;
		}
		else{
			return false;
		}
	}

	bool leftBoxSideCollides(int side){
		if(side==3){
			return true;
		}
		else{
			return false;
		}
	}
};