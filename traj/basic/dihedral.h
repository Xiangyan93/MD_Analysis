#pragma once
#include "base.h"
#include "atom.h"

class DihedralType: public Base {
    public:
        DihedralType(const unsigned int &id) {
            this->id = id;
        }
};


class Dihedral {
    public:
        Dihedral(Atom* atom1, Atom* atom2, Atom* atom3, Atom* atom4, DihedralType* dihedraltype) {
            this->atom1 = atom1;
            this->atom2 = atom2;
            this->atom3 = atom3;
            this->atom4 = atom4;
            this->type = dihedraltype;
            this->id_atom1 = atom1->id;
            this->id_atom2 = atom2->id;
            this->id_atom3 = atom3->id;
            this->id_atom4 = atom4->id;
            this->id_type = dihedraltype->id;
        }
        Atom *atom1, *atom2, *atom3, *atom4;
        DihedralType *type;
        unsigned int id_atom1, id_atom2, id_atom3, id_atom4, id_type;

        unsigned int id;
};