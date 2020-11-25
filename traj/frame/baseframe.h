#pragma once
#include "../basic/molecule.h"


class BaseFrame {
    public:
        void CenterOfMassTransform();
        void Sanitize();
        void Translation(const Vector &R);
        std::vector <Molecule> molecules;
        std::vector <Atom> coms;
        Vector BoxL;
        Vector BoxU;
};


void BaseFrame::CenterOfMassTransform(){
    if(coms.size() == molecules.size()){
        error("void Frame::CenterOfMassTransform() error\n");
    }
    for(unsigned i=0;i<molecules.size();++i){
        coms.push_back(molecules[i].get_center_of_mass());
    }
}


void BaseFrame::Sanitize() {
    for(unsigned int i=0;i<coms.size();++i){
        coms[i].x -= BoxL;
    }
    BoxU -= BoxL;
    BoxL[0] = BoxL[1] = BoxL[2] == 0.;
}