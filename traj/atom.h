#ifndef Atom_h
#define Atom_h
#include "elements.h"
class Atom{
    public:
		Atom();
		Atom(const Vector  x_, const Vector  v_, const string name_);
		Vector x;
		Vector v;
		double mass;
		string name;

    private:
		unsigned int atomic_number;
};

Atom::Atom(){
	x[0] = x[1] = x[2] =0.;
	v[0] = v[1] = v[2] =0.;
	mass = 0.;
}

Atom::Atom(const Vector x_, const Vector v_, const string name_){
	x = x_;
	v = v_;
	name = name_;
	mass = name2mass(name);
	atomic_number = name2atomic_number(name);
}
#endif
