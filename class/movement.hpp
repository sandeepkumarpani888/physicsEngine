#include <bits/stdc++.h>

class Movement
{

private:
	std::tuple<int,int> pos;
	std::tuple<double,double> velocity;

public:
	Movement(){
		this->pos=std::tuple<int,int>(100,0);
		this->velocity=std::tuple<double,double>(0,0);
	};
	
	Movement(std::tuple<int,int> _pos,std::tuple<double,double> _vel){
		this->pos=_pos;
		this->velocity=_vel;
	};

	std::tuple<int,int> getCordinates(){
		return this->pos;
	};

	std::tuple<double,double> getVelocity(){
		return this->velocity;
	};

	void setVelocity(std::tuple<double,double> _velocity){
		this->velocity=_velocity;
	}

	void setCordinates(std::tuple<int,int> _pos){
		this->pos=_pos;
	}
};