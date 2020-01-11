#include "../../CPP_HEAD/XYHeadFile/xy.h"
#include "../traj/trajectory.h"
#include "../analysis/function.h"

void GetACFandDiffusionConstant(const vector <double> &t_list, const vector <vector <double>> &_acf_list, const vector <string> &mol_name_list, const string mol_name){
    vector <vector <double>> _acf_list_new;
    double dt = t_list[1] - t_list[0];
    for(unsigned int i=0;i<mol_name_list.size();++i){
        if(mol_name=="System" || mol_name_list[i]==mol_name){
            _acf_list_new.push_back(_acf_list[i]);
        }
    }
    vector <double> acf_list = GetAverage(_acf_list_new);
    string file_name = "V-acf-" + mol_name + ".txt";
    FILE *fp = fopen(file_name.c_str(), "w");
    fprintf(fp, "#time(ps)\tACF(nm^2/ps^2)\n");
    for(unsigned int i=0;i<t_list.size();++i) {
		fprintf(fp, "%f\t%f\n", t_list[i], acf_list[i]);
	}
    fclose(fp);

    file_name = "diff-" + mol_name + ".txt";
    fp = fopen(file_name.c_str(), "w");
    fprintf(fp, "#time(ps)\tdiffusion_constant(cm^2/s)\n");
    double convert = 1. / 300.;
    double diffusion_constant = convert * acf_list[0] * dt /2;
    for(unsigned int i=1;i<t_list.size();++i){
        fprintf(fp, "%f\t%.10f\n", t_list[i] - 0.5 * dt, diffusion_constant);
        diffusion_constant += convert * acf_list[i] * dt;
    }
    fclose(fp);
}
int main(int argc, char **argv){
    Trajectory traj(argv[1]);
    vector <vector <Vector>> velocity;
    vector <string> mol_name_list;
    // velocity[i][j] = i-th molecule, j-th frame
    double t0, t1;
    vector <string> distinct_mol_name_list;
    for(unsigned i=0;i<traj.frame_number;++i){
        printf("\r%d / %d", i+1, traj.frame_number);
        fflush(stdout);
        Frame frame = traj.ReadFrame();
        if(frame.molecules.size()==0){
            break;
        }
        frame.CenterOfMassTransform();
        velocity.resize(frame.coms.size());
        for(unsigned int j=0;j<frame.coms.size();++j){
            velocity[j].push_back(frame.coms[j].v);
        }
        if(i==0){
            t0=frame.time;
            distinct_mol_name_list = frame.get_distinct_mol_name_list();
            for(unsigned int j=0;j<frame.coms.size();++j){
                mol_name_list.push_back(frame.molecules[j].name);
            }
        }
        if(i==1) t1=frame.time;
    }
    
    double dt = t1 - t0;
    vector <vector <double>> _acf_list;
    //_acf_list[i] = i-th molecule auto-correlation function
    vector <double> t_list;
    printf("\nCalculate auto-correlation function\n");
    for(unsigned int i=0;i<velocity.size();++i){
        printf("\r%d / %ld", i+1, velocity.size());
        _acf_list.push_back(GetACF(velocity[i], dt, t_list));
    }
    GetACFandDiffusionConstant(t_list, _acf_list, mol_name_list, "System");
    for(unsigned i=0;i<distinct_mol_name_list.size();++i){
        GetACFandDiffusionConstant(t_list, _acf_list, mol_name_list, distinct_mol_name_list[i]);
    }
}

