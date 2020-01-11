#include "../Free_Energy/fes.h"
using namespace std;
int main(int argc, char **argv){
    FILE *fp = fopen(argv[1], "r");
    // Read HILLS file
    vector <Gaussian> hills;
    char p[1000];
    string split_symbol = " \t\n";
    while(fgets(p, 1000, fp)){
        if (p[0] != '#'){
            Gaussian new_hill;
            vector <string> sp = split(p, split_symbol);
            unsigned int dimension = (sp.size() - 3) / 2;
            for(unsigned int i=0;i<dimension;++i){
                new_hill.center.push_back(anything2double(sp[i+1]));
                new_hill.sigma.push_back(anything2double(sp[i+1+dimension]));
            }
            new_hill.height = anything2double(dimension * 2 + 1);
            hills.push_back(new_hill);
        }
	}
    //
    split_symbol = ",";
    vector <double> lower_bounds = anything2double(split(argv[2], split_symbol));
    vector <double> upper_bounds = anything2double(split(argv[3], split_symbol));
    vector <bool> periodicities = anything2bool(split(argv[4], split_symbol));
    vector <unsigned int> bins = anything2usint(split(argv[5], split_symbol));
    bool MPC_correction = anything2bool(argv[6]);
    unsigned int stride = anything2usint(argv[7]);
    FreeEnergySurface fes(lower_bounds, upper_bounds, periodicities, bins);
    for(unsigned int i=0;i<hills.size();++i){
        fes.AddGaussian(hills[i], MPC_correction);
        if(i%stride == 0) fes.WriteFES("fes_" + anything2str(i) + ".dat");
    }
}