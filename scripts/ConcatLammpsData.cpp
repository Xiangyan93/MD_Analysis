#include "../traj/frame/lammpsdata.h"


int main(int argc, char **argv) {
    LammpsData data1(argv[1]), data2(argv[2]);
    data1.Concatenate(data2, 2);
    data1.Save("test.data");
}