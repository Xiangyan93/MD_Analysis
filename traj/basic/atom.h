#pragma once
#include "elements.h"
#include "base.h"

class AtomType: public Base {
	public:
		double mass;
		// id based
		AtomType(const unsigned int &id, const double &mass) {
			this->id = id;
			this->mass = mass;
		}
		unsigned int id;
		// element based
		AtomType(const std::string &element) {
			this->element = element;
		}
		std::string element;
		unsigned int atomic_number;
};


class Atom {
    public:
		Atom(const Vector &x, const Vector &v, AtomType* atomtype) {
			this->x = x;
			this->v = v;
			this->type = atomtype;
			this->id_type = atomtype->id;
		}
		Atom(const Vector &x, const Vector &v, const std::string &element) {
			this->x = x;
			this->v = v;
			AtomType type(element);
			this->type = &type;
			this->id_type = type.id;
		}

		// necessary
		Vector x;
		Vector v;
		AtomType *type;
		unsigned int id_type;
		// not necessary
		double charge;
		unsigned int id, mol_id;
};
