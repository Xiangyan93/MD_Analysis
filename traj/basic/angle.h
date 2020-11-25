#pragma once
#include "base.h"
#include "atom.h"


class AngleType: public Base {
    public:
        AngleType(const unsigned int &id) {
            this->id = id;
        }
        std::vector <double> coeffs_bb; 
        std::vector <double> coeffs_ba;
};


class Angle {
    public:
        Angle(Atom* atom1, Atom* atom2, Atom* atom3, AngleType* angletype) {
            this->atom1 = atom1;
            this->atom2 = atom2;
            this->atom3 = atom3;
            this->type = angletype;
            this->id_atom1 = atom1->id;
            this->id_atom2 = atom2->id;
            this->id_atom3 = atom3->id;
            this->id_type = angletype->id;
        }

        Atom *atom1, *atom2, *atom3;
        AngleType *type;
        unsigned int id_atom1, id_atom2, id_atom3, id_type;

        unsigned int id;
};
