#pragma once
#include "base.h"
#include "atom.h"


class BondType: public Base {
    public:
        BondType(const unsigned int &id) {
            this->id = id;
        }
};


class Bond {
    public:
        Bond(Atom* atom1, Atom* atom2, BondType* bondtype) {
            this->atom1 = atom1;
            this->atom2 = atom2;
            this->type = bondtype;
            this->id_atom1 = atom1->id;
            this->id_atom2 = atom2->id;
            this->id_type = bondtype->id;
        }

        Atom *atom1, *atom2;
        BondType *type;
        unsigned int id_atom1, id_atom2, id_type;
        
        unsigned int id;
};
