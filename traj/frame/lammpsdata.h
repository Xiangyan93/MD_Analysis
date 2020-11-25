#pragma once
#include "baseframe.h"
#include "../basic/bond.h"
#include "../basic/angle.h"
#include "../basic/dihedral.h"


class LammpsData: public BaseFrame {
    public:
        LammpsData(const std::string &filename);
        std::vector <AtomType> atom_types;
        std::vector <BondType> bond_types;
        std::vector <AngleType> angle_types;
        std::vector <DihedralType> dihedral_types;
        std::vector <DihedralType> improper_types;
        std::vector <Atom> atoms;
        std::vector <Bond> bonds;
        std::vector <Angle> angles;
        std::vector <Dihedral> dihedrals;
        std::vector <Dihedral> impropers;

        void Save(const std::string &filename);
        void Concatenate(LammpsData &data, const unsigned int d);
        void Sanitize();
        void Translation(const Vector &R);
        void Contraction(const Vector &R);

    private:
        unsigned int n_atoms, n_bonds, n_angles, n_dihedrals, n_impropers, n_molecules;
        unsigned int n_atom_type, n_bond_type, n_angle_type, n_dihedral_type, n_improper_type;
        void ReadTypes(const std::string &filename);
        void ReadCoordinates(const std::string &filename);
        template <typename Obj>
        void IdCheck(const std::vector <Obj> &obj);
        template <typename Obj>
        void ResetId(std::vector <Obj> &obj, const unsigned int);
        void ResetAtomId(const unsigned int id, const unsigned int mid, const unsigned int tid);
        void ResetBondId(const unsigned int id, const unsigned int aid, const unsigned int tid);
        void ResetAngleId(const unsigned int id, const unsigned int aid, const unsigned int tid);
        void ResetDihedralId(const unsigned int id, const unsigned int aid, const unsigned int tid);
        void ResetImproperId(const unsigned int id, const unsigned int aid, const unsigned int tid);
        void ResetAtomPointer();
        void ResetBondPointer();
        void ResetAnglePointer();
        void ResetDihedralPointer();
        void ResetImproperPointer();
};


LammpsData::LammpsData(const std::string &filename) {
    ReadTypes(filename);
    ReadCoordinates(filename);
}


void LammpsData::ReadTypes(const std::string &filename) {
    FILE *fp = fopen(filename.c_str(), "r");
    char p[1000];
    std::string split_symbol = "\\s+";
    while(fgets(p, 1000, fp)){
        std::vector <std::string> sp = split(p, split_symbol);
        switch (sp.size()) {
            case 1:
                if (sp[0].length() < 6) {}
                else if (sp[0].substr(0, 6) == "Masses") {
                    fgets(p, 1000, fp);
                    for(unsigned int i=0;i<n_atom_type;++i) {
                        fgets(p, 1000, fp);
                        sp = split(p, split_symbol);
                        unsigned int id = atoi(sp[0].c_str());
                        assert (id == i+1);
                        AtomType at(id, atof(sp[1].c_str()));
                        atom_types.push_back(at);
                    }
                }
                break;
            case 2:
                if (sp[1].substr(0, 5) == "atoms") {
                    n_atoms = atoi(sp[0].c_str());
                }
                else if (sp[1].substr(0, 5) == "bonds") {
                    n_bonds = atoi(sp[0].c_str());
                }
                else if (sp[1].substr(0, 6) == "angles") {
                    n_angles = atoi(sp[0].c_str());
                }
                else if (sp[1].substr(0, 9) == "dihedrals") {
                    n_dihedrals = atoi(sp[0].c_str());
                }
                else if (sp[1].substr(0, 9) == "impropers") {
                    n_impropers = atoi(sp[0].c_str());
                }
                else if (sp[0] == "Pair" and sp[1].substr(0, 6) == "Coeffs") {
                    fgets(p, 1000, fp);
                    for(unsigned int i=0;i<n_atom_type;++i) {
                        fgets(p, 1000, fp);
                        sp = split(p, split_symbol);
                        assert (sp.size() == 3);
                        for(unsigned int j=1;j<3;++j) {
                            atom_types[atoi(sp[0].c_str()) - 1].coeffs.push_back(atof(sp[j].c_str()));
                        }
                    }
                }
                else if (sp[0] == "Bond" and sp[1].substr(0, 6) == "Coeffs") {
                    fgets(p, 1000, fp);
                    for(unsigned int i=0;i<n_bond_type;++i) {
                        fgets(p, 1000, fp);
                        sp = split(p, split_symbol);
                        assert (atoi(sp[0].c_str()) == i + 1);
                        assert (sp.size() == 5);
                        unsigned int id = atoi(sp[0].c_str());
                        BondType bt(id);
                        for(unsigned int j=1;j<5;++j) {
                            bt.coeffs.push_back(atof(sp[j].c_str()));
                        }
                        bond_types.push_back(bt);
                    }
                }
                else if (sp[0] == "Angle" and sp[1].substr(0, 6) == "Coeffs") {
                    fgets(p, 1000, fp);
                    for(unsigned int i=0;i<n_angle_type;++i) {
                        fgets(p, 1000, fp);
                        sp = split(p, split_symbol);
                        assert (atoi(sp[0].c_str()) == i + 1);
                        assert (sp.size() == 5);
                        unsigned int id = atoi(sp[0].c_str());
                        AngleType at(id);
                        for(unsigned int j=1;j<5;++j) {
                            at.coeffs.push_back(atof(sp[j].c_str()));
                        }
                        angle_types.push_back(at);
                    }
                }
                else if (sp[0] == "BondBond" and sp[1].substr(0, 6) == "Coeffs") {
                    fgets(p, 1000, fp);
                    for(unsigned int i=0;i<n_angle_type;++i) {
                        fgets(p, 1000, fp);
                        sp = split(p, split_symbol);
                        assert (atoi(sp[0].c_str()) == i + 1);
                        assert (sp.size() == 4);
                        unsigned int id = atoi(sp[0].c_str());
                        for(unsigned int j=1;j<4;++j) {
                            angle_types[id - 1].coeffs_bb.push_back(atof(sp[j].c_str()));
                        }
                    }
                }
                else if (sp[0] == "BondAngle" and sp[1].substr(0, 6) == "Coeffs") {
                    fgets(p, 1000, fp);
                    for(unsigned int i=0;i<n_angle_type;++i) {
                        fgets(p, 1000, fp);
                        sp = split(p, split_symbol);
                        assert (atoi(sp[0].c_str()) == i + 1);
                        assert (sp.size() == 5);
                        unsigned int id = atoi(sp[0].c_str());
                        for(unsigned int j=1;j<5;++j) {
                            angle_types[id - 1].coeffs_ba.push_back(atof(sp[j].c_str()));
                        }
                    }
                }
                else if (sp[0] == "Dihedral" and sp[1].substr(0, 6) == "Coeffs") {
                    fgets(p, 1000, fp);
                    for(unsigned int i=0;i<n_dihedral_type;++i) {
                        fgets(p, 1000, fp);
                        sp = split(p, split_symbol);
                        assert (atoi(sp[0].c_str()) == i + 1);
                        assert (sp.size() == 5);
                        unsigned int id = atoi(sp[0].c_str());
                        DihedralType dt(id);
                        for(unsigned int j=1;j<5;++j) {
                            dt.coeffs.push_back(atof(sp[j].c_str()));
                        }
                        dihedral_types.push_back(dt);
                    }
                }
                else if (sp[0] == "Improper" and sp[1].substr(0, 6) == "Coeffs") {
                    fgets(p, 1000, fp);
                    for(unsigned int i=0;i<n_improper_type;++i) {
                        fgets(p, 1000, fp);
                        sp = split(p, split_symbol);
                        unsigned int id = atoi(sp[0].c_str());
                        assert (id == i + 1);
                        assert (sp.size() == 3);
                        DihedralType dt(id);
                        for(unsigned int j=1;j<3;++j) {
                            dt.coeffs.push_back(atof(sp[j].c_str()));
                        }
                        improper_types.push_back(dt);
                    }
                }
                break;
            case 3:
                if (sp[1] == "atom" and sp[2].substr(0, 5) == "types") {
                    n_atom_type = atoi(sp[0].c_str());
                }
                else if (sp[1] == "bond" and sp[2].substr(0, 5) == "types") {
                    n_bond_type = atoi(sp[0].c_str());
                }
                else if (sp[1] == "angle" and sp[2].substr(0, 5) == "types") {
                    n_angle_type = atoi(sp[0].c_str());
                }
                else if (sp[1] == "dihedral" and sp[2].substr(0, 5) == "types") {
                    n_dihedral_type = atoi(sp[0].c_str());
                }
                else if (sp[1] == "improper" and sp[2].substr(0, 5) == "types") {
                    n_improper_type = atoi(sp[0].c_str());
                }
                break;
            case 4:
                if (sp[2] == "xlo" and sp[3].substr(0, 3) == "xhi") {
                    BoxL[0] = atof(sp[0].c_str());
                    BoxU[0] = atof(sp[1].c_str());
                }
                else if (sp[2] == "ylo" and sp[3].substr(0, 3) == "yhi") {
                    BoxL[1] = atof(sp[0].c_str());
                    BoxU[1] = atof(sp[1].c_str());
                }
                else if (sp[2] == "zlo" and sp[3].substr(0, 3) == "zhi") {
                    BoxL[2] = atof(sp[0].c_str());
                    BoxU[2] = atof(sp[1].c_str());
                }  
                break;
            default:
                break;
        }
    }
    fclose(fp);
}


void LammpsData::ReadCoordinates(const std::string &filename) {
    FILE *fp = fopen(filename.c_str(), "r");
    char p[1000];
    std::string split_symbol = "\\s+";
    while(fgets(p, 1000, fp)){
        std::vector <std::string> sp = split(p, split_symbol);
        if (sp[0].substr(0, 5) == "Atoms") {
            n_molecules = 0;
            fgets(p, 1000, fp);
            for(unsigned int i=0;i<n_atoms;++i) {
                fgets(p, 1000, fp);
                sp = split(p, split_symbol);
                Vector x(atof(sp[4].c_str()), atof(sp[5].c_str()), atof(sp[6].c_str())), v(0., 0., 0.);
                Atom atom(x, v, &atom_types[atoi(sp[2].c_str()) - 1]);
                atom.id = atoi(sp[0].c_str());
                assert (atom.id == i + 1);
                atom.mol_id = atoi(sp[1].c_str());
                if (atom.mol_id > n_molecules) n_molecules = atom.mol_id;
                atom.charge = atof(sp[3].c_str());
                atoms.push_back(atom);
            }
        }
        else if (sp[0].substr(0, 5) == "Bonds") {
            fgets(p, 1000, fp);
            for(unsigned int i=0;i<n_bonds;++i) {
                fgets(p, 1000, fp);
                sp = split(p, split_symbol);
                assert (sp.size() == 4);
                Bond bond(
                    &atoms[atoi(sp[2].c_str()) - 1], 
                    &atoms[atoi(sp[3].c_str()) - 1], 
                    &bond_types[atoi(sp[1].c_str()) - 1]
                );
                bond.id = atoi(sp[0].c_str());
                bonds.push_back(bond);
            }
        }
        else if (sp[0].substr(0, 6) == "Angles") {
            fgets(p, 1000, fp);
            for(unsigned int i=0;i<n_angles;++i) {
                fgets(p, 1000, fp);
                sp = split(p, split_symbol);
                assert (sp.size() == 5);
                Angle angle(
                    &atoms[atoi(sp[2].c_str()) - 1], 
                    &atoms[atoi(sp[3].c_str()) - 1], 
                    &atoms[atoi(sp[4].c_str()) - 1], 
                    &angle_types[atoi(sp[1].c_str()) - 1]
                );
                angle.id = atoi(sp[0].c_str());
                angles.push_back(angle);
            }
        }
        else if (sp[0].substr(0, 9) == "Dihedrals") {
            fgets(p, 1000, fp);
            for(unsigned int i=0;i<n_dihedrals;++i) {
                fgets(p, 1000, fp);
                sp = split(p, split_symbol);
                assert (sp.size() == 6);
                Dihedral dihedral(
                    &atoms[atoi(sp[2].c_str()) - 1],
                    &atoms[atoi(sp[3].c_str()) - 1], 
                    &atoms[atoi(sp[4].c_str()) - 1], 
                    &atoms[atoi(sp[5].c_str()) - 1], 
                    &dihedral_types[atoi(sp[1].c_str()) - 1]
                );
                dihedral.id = atoi(sp[0].c_str());
                dihedrals.push_back(dihedral);
            }
        }
        else if (sp[0].substr(0, 9) == "Impropers") {
            fgets(p, 1000, fp);
            for(unsigned int i=0;i<n_impropers;++i) {
                fgets(p, 1000, fp);
                sp = split(p, split_symbol);
                assert (sp.size() == 6);
                Dihedral improper(
                    &atoms[atoi(sp[2].c_str()) - 1],
                    &atoms[atoi(sp[3].c_str()) - 1], 
                    &atoms[atoi(sp[4].c_str()) - 1], 
                    &atoms[atoi(sp[5].c_str()) - 1], 
                    &improper_types[atoi(sp[1].c_str()) - 1]
                );
                improper.id = atoi(sp[0].c_str());
                impropers.push_back(improper);
            }
        }
    }
    fclose(fp);
}


template <typename ObjId>
void LammpsData::IdCheck(const std::vector <ObjId> &obj) {
    for(unsigned int i=0; i<obj.size(); ++i) {
        assert (obj[i].id == i+1);
    }
}


template <typename ObjId>
void LammpsData::ResetId(std::vector <ObjId> &obj, const unsigned int id) {
    for(unsigned int i=0; i<obj.size(); ++i) {
        assert (obj[i].id == i+1);
        obj[i].id += id;
    }
}


void LammpsData::ResetAtomId(const unsigned int id, const unsigned int mid, const unsigned int tid) {
    for(unsigned int i=0; i<atoms.size(); ++i) {
        atoms[i].id += id;
        atoms[i].mol_id += mid;
        atoms[i].id_type += tid;
    }
}


void LammpsData::ResetBondId(const unsigned int id, const unsigned int aid, const unsigned int tid) {
    for(unsigned int i=0; i<bonds.size(); ++i) {
        bonds[i].id += id;
        bonds[i].id_atom1 += aid;
        bonds[i].id_atom2 += aid;
        bonds[i].id_type += tid;
    }
}


void LammpsData::ResetAngleId(const unsigned int id, const unsigned int aid, const unsigned int tid) {
    for(unsigned int i=0; i<angles.size(); ++i) {
        angles[i].id += id;
        angles[i].id_atom1 += aid;
        angles[i].id_atom2 += aid;
        angles[i].id_atom3 += aid;
        angles[i].id_type += tid;
    }
}

void LammpsData::ResetDihedralId(const unsigned int id, const unsigned int aid, const unsigned int tid) {
    for(unsigned int i=0; i<dihedrals.size(); ++i) {
        dihedrals[i].id += id;
        dihedrals[i].id_atom1 += aid;
        dihedrals[i].id_atom2 += aid;
        dihedrals[i].id_atom3 += aid;
        dihedrals[i].id_atom4 += aid;
        dihedrals[i].id_type += tid;
    }
}


void LammpsData::ResetImproperId(const unsigned int id, const unsigned int aid, const unsigned int tid) {
    for(unsigned int i=0; i<impropers.size(); ++i) {
        impropers[i].id += id;
        impropers[i].id_atom1 += aid;
        impropers[i].id_atom2 += aid;
        impropers[i].id_atom3 += aid;
        impropers[i].id_atom4 += aid;
        impropers[i].id_type += tid;
    }
}


void LammpsData::ResetAtomPointer() {
    for(unsigned int i=0; i<atoms.size(); ++i) {
        atoms[i].type = &atom_types[atoms[i].id_type - 1];
    }
}


void LammpsData::ResetBondPointer() {
    for(unsigned int i=0; i<bonds.size(); ++i) {
        bonds[i].type = &bond_types[bonds[i].id_type - 1];
        bonds[i].atom1 = &atoms[bonds[i].id_atom1 - 1];
        bonds[i].atom2 = &atoms[bonds[i].id_atom2 - 1];
    }
}


void LammpsData::ResetAnglePointer() {
    for(unsigned int i=0; i<angles.size(); ++i) {
        angles[i].type = &angle_types[angles[i].id_type - 1];
        angles[i].atom1 = &atoms[angles[i].id_atom1 - 1];
        angles[i].atom2 = &atoms[angles[i].id_atom2 - 1];
        angles[i].atom3 = &atoms[angles[i].id_atom3 - 1];
    }
}


void LammpsData::ResetDihedralPointer() {
    for(unsigned int i=0; i<dihedrals.size(); ++i) {
        dihedrals[i].type = &dihedral_types[dihedrals[i].id_type - 1];
        dihedrals[i].atom1 = &atoms[dihedrals[i].id_atom1 - 1];
        dihedrals[i].atom2 = &atoms[dihedrals[i].id_atom2 - 1];
        dihedrals[i].atom3 = &atoms[dihedrals[i].id_atom3 - 1];
        dihedrals[i].atom4 = &atoms[dihedrals[i].id_atom4] - 1;
    }
}


void LammpsData::ResetImproperPointer() {
    for(unsigned int i=0; i<impropers.size(); ++i) {
        impropers[i].type = &improper_types[impropers[i].id_type - 1];
        impropers[i].atom1 = &atoms[impropers[i].id_atom1 - 1];
        impropers[i].atom2 = &atoms[impropers[i].id_atom2 - 1];
        impropers[i].atom3 = &atoms[impropers[i].id_atom3 - 1];
        impropers[i].atom4 = &atoms[impropers[i].id_atom4 - 1];
    }
}


void LammpsData::Concatenate(LammpsData &data, const unsigned int d) {
    Vector R = (BoxU - BoxL) / (data.BoxU - data.BoxL);
    R[d] = 1.;
    Vector T(0., 0., 0.);
    T[d] = (BoxU - BoxL)[d];
    Sanitize();
    data.Contraction(R);
    data.Translation(T);
    BoxU[d] += (data.BoxU[d] - data.BoxL[d]);
    IdCheck(atom_types);
    ResetId(data.atom_types, atom_types.size());
    atom_types.insert(atom_types.end(), data.atom_types.begin(), data.atom_types.end());

    IdCheck(bond_types);
    ResetId(data.bond_types, bond_types.size());
    bond_types.insert(bond_types.end(), data.bond_types.begin(), data.bond_types.end());

    IdCheck(angle_types);
    ResetId(data.angle_types, angle_types.size());
    angle_types.insert(angle_types.end(), data.angle_types.begin(), data.angle_types.end());

    IdCheck(dihedral_types);
    ResetId(data.dihedral_types, dihedral_types.size());
    dihedral_types.insert(dihedral_types.end(), data.dihedral_types.begin(), data.dihedral_types.end());

    IdCheck(improper_types);
    ResetId(data.improper_types, improper_types.size());
    improper_types.insert(improper_types.end(), data.improper_types.begin(), data.improper_types.end());

    IdCheck(atoms);
    data.ResetAtomId(n_atoms, n_molecules, n_atom_type);
    atoms.insert(atoms.end(), data.atoms.begin(), data.atoms.end());
    ResetAtomPointer();

    IdCheck(bonds);
    data.ResetBondId(n_bonds, n_atoms, n_bond_type);
    bonds.insert(bonds.end(), data.bonds.begin(), data.bonds.end());
    ResetBondPointer();

    IdCheck(angles);
    data.ResetAngleId(n_angles, n_atoms, n_angle_type);
    angles.insert(angles.end(), data.angles.begin(), data.angles.end());
    ResetAnglePointer();

    IdCheck(dihedrals);
    data.ResetDihedralId(n_dihedrals, n_atoms, n_dihedral_type);
    dihedrals.insert(dihedrals.end(), data.dihedrals.begin(), data.dihedrals.end());
    ResetDihedralPointer();

    IdCheck(impropers);
    data.ResetImproperId(n_impropers, n_atoms, n_improper_type);
    impropers.insert(impropers.end(), data.impropers.begin(), data.impropers.end());
    ResetImproperPointer();

    n_atoms += data.n_atoms;
    n_bonds += data.n_bonds;
    n_angles += data.n_angles;
    n_dihedrals += data.n_dihedrals;
    n_impropers += data.n_impropers;
    n_atom_type += data.n_atom_type;
    n_bond_type += data.n_bond_type;
    n_angle_type += data.n_angle_type;
    n_dihedral_type += data.n_dihedral_type;
    n_improper_type += data.n_improper_type;
}


void LammpsData::Save(const std::string &filename) {
    FILE *fp = fopen(filename.c_str(), "w");
    fprintf(fp, "# MD_Analysis generated LAMMPS data file\n\n");
    // count
    if (atoms.size() != 0) {
        fprintf(fp, "%d atoms\n", n_atoms);
    }
    if (bonds.size() != 0) {
        fprintf(fp, "%ld bonds\n", bonds.size());
    }
    if (angles.size() != 0) {
        fprintf(fp, "%ld angles\n", angles.size());
    }
    if (dihedrals.size() != 0) {
        fprintf(fp, "%ld dihedrals\n", dihedrals.size());
    }
    if (impropers.size() != 0) {
        fprintf(fp, "%ld impropers\n", impropers.size());
    }
    // types count
    if (atom_types.size() != 0) {
        fprintf(fp, "\n%ld  atom types\n", atom_types.size());
    }
    if (bond_types.size() != 0) {
        fprintf(fp, "%ld  bond types\n", bond_types.size());
    }
    if (angle_types.size() != 0) {
        fprintf(fp, "%ld  angle types\n", angle_types.size());
    }
    if (dihedral_types.size() != 0) {
        fprintf(fp, "%ld  dihedral types\n", dihedral_types.size());
    }
    if (improper_types.size() != 0) {
        fprintf(fp, "%ld  improper types\n", improper_types.size());
    }
    // box
    fprintf(fp, "\n\t  %.4f\t %.4f   xlo xhi\n", BoxL[0], BoxU[0]);
    fprintf(fp, "\t  %.4f\t %.4f   ylo yhi\n", BoxL[1], BoxU[1]);
    fprintf(fp, "\t  %.4f\t %.4f   zlo zhi\n", BoxL[2], BoxU[2]);
    // Masses
    fprintf(fp, "\nMasses\n\n");
    for(unsigned int i=0;i<atom_types.size();++i) {
        fprintf(fp, "\t\t   %d\t%.4f\n", atom_types[i].id, atom_types[i].mass);
    }
    // Atoms
    fprintf(fp, "\nAtoms\n\n");
    for(unsigned int i=0;i<n_atoms;++i) {
        Atom *atom = &atoms[i];

        fprintf(
            fp, "\t%d\t%d\t%d\t%.5f\t%.5f\t%.5f\t%.5f\n", 
            atom->id, atom->mol_id, atom->type->id, atom->charge, 
            atom->x[0], atom->x[1], atom->x[2]
        );
    }
    // Bonds
    fprintf(fp, "\nBonds\n\n");
    for(unsigned int i=0;i<bonds.size();++i) {
        Bond *bond = &bonds[i];
        fprintf(
            fp, "\t%d\t%d\t%d\t%d\n",
            bond->id, bond->type->id, bond->atom1->id, bond->atom2->id
        );
    }
    // Angles
    fprintf(fp, "\nAngles\n\n");
    for(unsigned int i=0;i<angles.size();++i) {
        Angle *angle = &angles[i];
        fprintf(
            fp, "\t%d\t%d\t%d\t%d\t%d\n",
            angle->id, angle->type->id, angle->atom1->id, angle->atom2->id, angle->atom3->id
        );
    }
    // Dihedrals
    fprintf(fp, "\nDihedrals\n\n");
    for(unsigned int i=0;i<dihedrals.size();++i) {
        Dihedral *dihedral = &dihedrals[i];
        fprintf(
            fp, "\t%d\t%d\t%d\t%d\t%d\t%d\n",
            dihedral->id, dihedral->type->id, dihedral->atom1->id, dihedral->atom2->id, dihedral->atom3->id, dihedral->atom4->id
        );
    }
    //Impropers

    fprintf(fp, "\nImpropers\n\n");
    for(unsigned int i=0;i<impropers.size();++i) {
        Dihedral *improper = &impropers[i];
        fprintf(
            fp, "\t%d\t%d\t%d\t%d\t%d\t%d\n",
            improper->id, improper->type->id, improper->atom1->id, improper->atom2->id, improper->atom3->id, improper->atom4->id
        );
    }
    //Pair Coeffs
    fprintf(fp, "\nPair Coeffs\n\n");
    for(unsigned int i=0;i<atom_types.size();++i) {
        AtomType *at = &atom_types[i];
        fprintf(fp, "\t%d\t%.5f\t%.5f\n", at->id, at->coeffs[0], at->coeffs[1]);
    }
    //Bond Coeffs
    fprintf(fp, "\nBond Coeffs\n\n");
    for(unsigned int i=0;i<bond_types.size();++i) {
        BondType *t = &bond_types[i];
        fprintf(fp, "\t%d\t%.5f\t%.5f\t%.5f\t%.5f\n", t->id, t->coeffs[0], t->coeffs[1], t->coeffs[2], t->coeffs[3]);
    }
    //Angle Coeffs
    fprintf(fp, "\nAngle Coeffs\n\n");
    for(unsigned int i=0;i<angle_types.size();++i) {
        AngleType *t = &angle_types[i];
        fprintf(fp, "\t%d\t%.5f\t%.5f\t%.5f\t%.5f\n", t->id, t->coeffs[0], t->coeffs[1], t->coeffs[2], t->coeffs[3]);
    }
    //BondBond Coeffs
    fprintf(fp, "\nBondBond Coeffs\n\n");
    for(unsigned int i=0;i<angle_types.size();++i) {
        AngleType *t = &angle_types[i];
        fprintf(fp, "\t%d\t%.5f\t%.5f\t%.5f\n", t->id, t->coeffs_bb[0], t->coeffs_bb[1], t->coeffs_bb[2]);
    }
    //BondAngle Coeffs
    fprintf(fp, "\nBondAngle Coeffs\n\n");
    for(unsigned int i=0;i<angle_types.size();++i) {
        AngleType *t = &angle_types[i];
        fprintf(fp, "\t%d\t%.5f\t%.5f\t%.5f\t%.5f\n", t->id, t->coeffs_ba[0], t->coeffs_ba[1], t->coeffs_ba[2], t->coeffs_ba[3]);
    }
    //Dihedral Coeffs
    fprintf(fp, "\nDihedral Coeffs\n\n");
    for(unsigned int i=0;i<dihedral_types.size();++i) {
        DihedralType *t = &dihedral_types[i];
        fprintf(fp, "\t%d\t%.5f\t%.5f\t%.5f\t%.5f\n", t->id, t->coeffs[0], t->coeffs[1], t->coeffs[2], t->coeffs[3]);
    }
    //Improper Coeffs
    fprintf(fp, "\nImproper Coeffs\n\n");
    for(unsigned int i=0;i<improper_types.size();++i) {
        DihedralType *t = &improper_types[i];
        fprintf(fp, "\t%d\t%.5f\t%.5f\n", t->id, t->coeffs[0], t->coeffs[1]);
    }
    fclose(fp);
}


void LammpsData::Sanitize() {
    Translation(BoxL);
}


void LammpsData::Translation(const Vector &R) {
    for(unsigned int i=0;i<atoms.size();++i) {
        atoms[i].x += R;
    }
    BoxU += R;
    BoxL += R;
}


void LammpsData::Contraction(const Vector &R) {
    Sanitize();
    for(unsigned int i=0;i<atoms.size();++i) {
        atoms[i].x = atoms[i].x * R;
    }
    BoxL *= R;
    BoxU *= R;
}
