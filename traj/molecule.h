#ifndef Molecule_h
#define Molecule_h
#include "atom.h"
class Molecule{
    public:
        Atom get_center_of_mass();
        double get_e2e_distance();
        double get_gyration();

        vector <Atom> atoms;
        string name;
    private:
};

Atom Molecule::get_center_of_mass(){
    Atom com;
    com.name = name;
    for(unsigned i=0;i<atoms.size();++i){
        com.mass += atoms[i].mass;
        com.x += atoms[i].x * atoms[i].mass;
        com.v += atoms[i].v * atoms[i].mass;
    }
    com.x /= com.mass;
    com.v /= com.mass;
    return com;
}
double Molecule::get_e2e_distance(){
    return 0.;
}

double Molecule::get_gyration(){
    return 0.;
}
#endif