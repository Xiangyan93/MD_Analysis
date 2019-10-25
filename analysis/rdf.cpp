#include "../XYHeadFile/xy.h"
#include "../traj/trajectory.h"

int main(int argc, char **argv){
    Trajectory traj(argv[1]);
    string center = argv[2];
    string surround = argv[3];
    double dx = atof(argv[4]);
    double cutoff = atof(argv[5]);
    vector <string> mol_name_list;
    vector <string> distinct_mol_name_list;
    vector <double> rdf;
    for(unsigned i=0;i<traj.frame_number;++i){
        printf("\r%d / %d", i+1, traj.frame_number);
        fflush(stdout);
        Frame frame = traj.ReadFrame();
        if(i==0){
            distinct_mol_name_list = frame.get_distinct_mol_name_list();
            for(unsigned int j=0;j<frame.coms.size();++j){
                mol_name_list.push_back(frame.molecules[j].name);
            }
        }
        if(frame.molecules.size()==0){
            break;
        }
        frame.CenterOfMassTransform();
        if(i==0)
            rdf=frame.get_rdf(center, surround, dx, cutoff);
        else{
            vector <double> _rdf=frame.get_rdf(center, surround, dx, cutoff);
            for(unsigned int j=0;j<rdf.size();++j){
                rdf[j] += _rdf[j];
            }
        }
    }
    FILE *fp=fopen("rdf.txt", "w");
    for(unsigned int j=0;j<rdf.size();++j){
        rdf[j] /= traj.frame_number;
        fprintf(fp, "%f %f\n", (j+0.5)*dx, rdf[j]);
    }
}