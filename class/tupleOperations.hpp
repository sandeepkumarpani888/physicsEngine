#ifndef TUPLEOPERATIONS_H_
#define TUPLEOPERATIONS_H_
#include <bits/stdc++.h>

class TupleOperations
{
public:

	bool checkIsSameSign(int _first,int _second){
		if(_first*_second>=0){
			return true;
		}
		else{
			return false;
		}
	}

	bool checkIsSameSign(double _first,double _second){
		if(_first*_second>=0){
			return true;
		}
		else{
			return false;
		}
	}

	bool isSameI(int _first,int _second){
		if(_first==_second){
			return true;
		}
		else{
			return false;
		}
	}

	bool isSameD(double _first,double _second){
		if(abs(_first-_second)<=1e-6){
			return true;
		}
		else{
			return false;
		}
	}

	std::tuple<int,int> sM(std::tuple<int,int> tupleToOperate,int coff){
		std::get<0>(tupleToOperate)*=coff;
		std::get<1>(tupleToOperate)*=coff;
		return tupleToOperate;
	}

	std::tuple<double,double> sM(std::tuple<double,double> tupleToOperate,int coff){
		std::get<0>(tupleToOperate)/=(double)(coff);
		std::get<1>(tupleToOperate)/=(double)(coff);
		return tupleToOperate;
	}

	std::tuple<int,int> aT(std::tuple<int,int> first,std::tuple<int,int> second){
		std::get<0>(first)+=std::get<0>(second);
		std::get<1>(first)+=std::get<1>(second);
		return first;
	}

	std::tuple<double,double> aT(std::tuple<double,double> first,std::tuple<double,double> second){
		std::get<0>(first)+=std::get<0>(second);
		std::get<1>(first)+=std::get<1>(second);
		return first;
	}

	std::tuple<int,int> dT(std::tuple<int,int> tupleToOperate,int coff){
		std::get<0>(tupleToOperate)/=coff;
		std::get<1>(tupleToOperate)/=coff;
		return tupleToOperate;
	}

	std::tuple<double,double> dT(std::tuple<double,double> tupleToOperate,int coff){
		std::get<0>(tupleToOperate)/=(double)(coff);
		std::get<1>(tupleToOperate)/=(double)(coff);
		return tupleToOperate;
	}
};

#endif