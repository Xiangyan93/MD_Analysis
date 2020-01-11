#pragma once
using namespace std;
#include "../XYHeadFile/xy.h"
double name2mass(string name){
    map<string, double> element2mass;
    element2mass.insert(pair<string, double>("H", 1.00794));
    element2mass.insert(pair<string, double>("He",4.002602));
    element2mass.insert(pair<string, double>("Li",6.941));
    element2mass.insert(pair<string, double>("Be",9.012182));
    element2mass.insert(pair<string, double>("B", 10.811));
    element2mass.insert(pair<string, double>("C", 12.0107));
    element2mass.insert(pair<string, double>("N", 14.0067));
    element2mass.insert(pair<string, double>("O", 15.9994));
    element2mass.insert(pair<string, double>("F", 18.9984032));
    element2mass.insert(pair<string, double>("Ne",20.1797));
    element2mass.insert(pair<string, double>("Na",22.98976928));
    element2mass.insert(pair<string, double>("Mg",24.3050));
    element2mass.insert(pair<string, double>("Al",26.9815386));
    element2mass.insert(pair<string, double>("Si",28.0855));
    element2mass.insert(pair<string, double>("P", 30.973762));
    element2mass.insert(pair<string, double>("S", 32.065));
    element2mass.insert(pair<string, double>("Cl",35.453));
    element2mass.insert(pair<string, double>("Ar",39.948));
    element2mass.insert(pair<string, double>("K", 39.0983));
    element2mass.insert(pair<string, double>("Ca",40.078));
    element2mass.insert(pair<string, double>("Fe",55.845));
    element2mass.insert(pair<string, double>("Co",58.933195));
    element2mass.insert(pair<string, double>("Ni",58.6934));
    element2mass.insert(pair<string, double>("Cu",63.546));
    element2mass.insert(pair<string, double>("Br",79.904));
    element2mass.insert(pair<string, double>("I ",126.90447));

    element2mass.insert(pair<string, double>("CH1", 13.018));
    element2mass.insert(pair<string, double>("CH2", 14.026));
    element2mass.insert(pair<string, double>("CH3", 15.034));
    map <string, double>::iterator key = element2mass.find(name);
    if (key != element2mass.end()) {
		return key->second;
	}
    else{
        return 0.;
    }
}

unsigned int name2atomic_number(string name){
    map<string, unsigned int> element2atomic_number;
    element2atomic_number.insert(pair<string, unsigned int>("H",  1));
    element2atomic_number.insert(pair<string, unsigned int>("He", 2));
    element2atomic_number.insert(pair<string, unsigned int>("Li", 3));
    element2atomic_number.insert(pair<string, unsigned int>("Be", 4));
    element2atomic_number.insert(pair<string, unsigned int>("B",  5));
    element2atomic_number.insert(pair<string, unsigned int>("C",  6));
    element2atomic_number.insert(pair<string, unsigned int>("N",  7));
    element2atomic_number.insert(pair<string, unsigned int>("O",  8));
    element2atomic_number.insert(pair<string, unsigned int>("F",  9));
    element2atomic_number.insert(pair<string, unsigned int>("Ne",10));
    element2atomic_number.insert(pair<string, unsigned int>("Na",11));
    element2atomic_number.insert(pair<string, unsigned int>("Mg",12));
    element2atomic_number.insert(pair<string, unsigned int>("Al",13));
    element2atomic_number.insert(pair<string, unsigned int>("Si",14));
    element2atomic_number.insert(pair<string, unsigned int>("P", 15));
    element2atomic_number.insert(pair<string, unsigned int>("S", 16));
    element2atomic_number.insert(pair<string, unsigned int>("Cl",17));
    element2atomic_number.insert(pair<string, unsigned int>("Ar",18));
    element2atomic_number.insert(pair<string, unsigned int>("K", 19));
    element2atomic_number.insert(pair<string, unsigned int>("Ca",20));
    element2atomic_number.insert(pair<string, unsigned int>("Fe",26));
    element2atomic_number.insert(pair<string, unsigned int>("Co",27));
    element2atomic_number.insert(pair<string, unsigned int>("Ni",28));
    element2atomic_number.insert(pair<string, unsigned int>("Cu",29));
    element2atomic_number.insert(pair<string, unsigned int>("Br",35));
    element2atomic_number.insert(pair<string, unsigned int>("I ",53));
    map <string, unsigned int>::iterator key = element2atomic_number.find(name);
    if (key != element2atomic_number.end()) {
		return key->second;
	}
    else{
        return 0;
    }
}