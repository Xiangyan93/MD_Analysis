#pragma once
#include "frame.h"

class Trajectory{
    public:
        Trajectory(const string file_name);
        Frame ReadFrame();
		unsigned int frame_number;
    private:
        FILE *traj_file;
        string traj_file_name;
        Frame ReadGroFrame();
};

Trajectory::Trajectory(const string file_name){
	
    traj_file_name = file_name;
    traj_file = fopen(file_name.c_str(), "r");

	FILE *fp = fopen(file_name.c_str(), "r");
	char p[1000];
	fgets(p, 1000, fp);
	fgets(p, 1000, fp);
	unsigned int atom_number = atoi(p);
	unsigned int line_number = 2;
	while(fgets(p, 1000, fp)){
		line_number++;
	}
	frame_number = line_number / (atom_number+3);
	printf("Reading %s, totally %d frames\n", file_name.c_str(), frame_number);
}

Frame Trajectory::ReadFrame(){
    string split_symbol = ".";
    vector <string> sp = split(traj_file_name, split_symbol);
    if (sp.back() == "gro") {
        return ReadGroFrame();
    }
}

Frame Trajectory::ReadGroFrame(){
	Frame frame;
	bool velocity = false;
	Molecule mol;
    char p[1000];
	string split_symbol = " \t\n";
	fgets(p, 1000, traj_file);
	vector <string> sp = split(p, split_symbol);
	for(unsigned int i=0;i<sp.size();++i){
		if(sp[i]=="t=" && i!=sp.size()-1){
			frame.time = atof(sp[i+1].c_str());
			break;
		}
		if( i==sp.size()-1){
			error("reading frame time error");
		}
	}
	fgets(p, 1000, traj_file);
	unsigned int atom_number = atoi(p);
	unsigned int molecule_id = 1;
	for (unsigned i = 0; i < atom_number; ++i) {
		fgets(p, 1000, traj_file);
		string q = string(p);

		if (q.length() > 45) {
			q.insert(60, " ");
			q.insert(52, " ");
			q.insert(44, " ");
		}
		if (q.length() > 25) {
			q.insert(20, " ");
			q.insert(15, " ");
			q.insert(5, " ");
		}
		sp = split(q, split_symbol);
		if(sp.size()==7){
		}
		else if(sp.size()==10){
			velocity=true;
		}
		else{
			printf("error line: %s\n", q.c_str());
			exit(0);
		}
		if(atoi(sp[0].c_str()) == molecule_id+1 || i == atom_number-1){
			molecule_id++;
			frame.molecules.push_back(mol);
			mol.atoms.resize(0);
		}
		Vector x(atof(sp[4].c_str()), atof(sp[5].c_str()), atof(sp[6].c_str()));
		Vector v(0., 0., 0.);
		if(velocity){
			v[0] = atof(sp[7].c_str());
			v[1] = atof(sp[8].c_str());
			v[2] = atof(sp[9].c_str());
		}
		Atom atom(x, v, sp[2]);
		mol.name = sp[1];
		mol.atoms.push_back(atom);
	}
	fgets(p, 1000, traj_file);
	sp = split(string(p), split_symbol);
	if (sp.size() == 3) {
		Vector BoxR(atof(sp[0].c_str()), atof(sp[1].c_str()), atof(sp[2].c_str()));
		frame.BoxR = BoxR;
	}
	return frame;
}