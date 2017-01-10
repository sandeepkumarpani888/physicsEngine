#include <bits/stdc++.h>

class TupleOperations
{
public:

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
		set::get<1>(first)+=std::get<1>(second);
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