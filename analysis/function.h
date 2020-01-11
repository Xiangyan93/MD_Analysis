#pragma once
#include "../../CPP_HEAD/XYHeadFile/xy.h"
using namespace std;
vector <double> GetACF(const vector <Vector> &y_list, double dt, vector <double> &t_list){
	vector <double> _t_list;
	vector <double> acf_list;
    for (unsigned i = 0; i < (y_list.size() / 2); ++i) {
        double Dt = i * dt;
		double acf = 0.;
		for (unsigned j = 0; j < y_list.size() - i; ++j) {
			acf += dotProduct(y_list[j], y_list[i + j]);
		}
		acf /= (y_list.size() - i);
		_t_list.push_back(Dt);
		acf_list.push_back(acf);
	}
	if(t_list.size()==0) t_list = _t_list;
	return acf_list;
}