#ifndef Frame_h
#define Frame_h
#include "molecule.h"
#include "tools.h"
class Frame{
    public:
        void CenterOfMassTransform();
        vector <double> get_rdf(const string &center, const string &surround);
        vector <double> get_rdf(const string &center, const string &surround, const double &dx, const double&cutoff);      
        vector <string> get_distinct_mol_name_list();
        double volume();

    	vector <Molecule> molecules;
        vector <Atom> coms;
		Vector BoxR;
        double time;
    
    private:
};

void Frame::CenterOfMassTransform(){
    if(coms.size() == molecules.size()){
        error("void Frame::CenterOfMassTransform() error\n");
    }
    for(unsigned i=0;i<molecules.size();++i){
        coms.push_back(molecules[i].get_center_of_mass());
    }
}

double Frame::volume(){
    return BoxR[0] * BoxR[1] * BoxR[2];
}

vector <string> Frame::get_distinct_mol_name_list(){
    vector <string> distinct_mol_name_list;
    for(unsigned int i=0;i<molecules.size();++i){
        if(!IsInside(molecules[i].name, distinct_mol_name_list)){
            distinct_mol_name_list.push_back(molecules[i].name);
        }
    }
    return distinct_mol_name_list;
}

vector <double> Frame::get_rdf(const string &center, const string &surround, const double &dx, const double &cutoff){
    vector <double> rdf(ceil(cutoff/dx), 0.);
    if(center==surround){
        unsigned int atom_number = 0;
        for(unsigned int i=0;i<coms.size();++i){
            if(coms[i].name != center)
                continue;
            atom_number += 1;
            for(unsigned int j=i+1;j<coms.size();++j){
                if(coms[j].name != surround)
                    continue;
                double dr = get_distance(coms[i].x, coms[j].x, BoxR);
                if(dr<cutoff){
                    int n = floor(dr / dx);
                    rdf[n] += 1./4./pi/dr/dr/dx;
                }
            }
        }
        for(unsigned int i=0;i<rdf.size();++i){
            rdf[i] *= 2*volume()/atom_number/(atom_number-1);
        }
    }
    else{
        unsigned int atom_number_center = 0;
        unsigned int atom_number_surround = 0;
        for(unsigned int i=0;i<coms.size();++i){
            if(coms[i].name != center)
                continue;
            atom_number_center += 1;
            for(unsigned int j=0;j<coms.size();++j){
                if(coms[j].name != surround)
                    continue;
                atom_number_surround += 1;
                double dr = get_distance(coms[i].x, coms[j].x, BoxR);
                if(dr<cutoff){
                    int n = floor(dr / dx);
                    rdf[n] += 1./4./pi/dr/dr/dx;
                }
            }
        }
        atom_number_surround /= atom_number_center;
        for(unsigned int i=0;i<rdf.size();++i){
            rdf[i] *= volume()/atom_number_center/atom_number_surround;
        }
    }
    return rdf;
}

vector <double> Frame::get_rdf(const string &center, const string &surround){
    return get_rdf(center, surround, 0.01, 10.0);
}

#endif