#pragma once
using namespace std;
#include "../XYHeadFile/xy.h"
double get_distance(const Vector x, const Vector y, const Vector BoxR){
    Vector dr = x-y;
    if(dr[0] > BoxR[0] / 2)
        dr[0] -= BoxR[0];
    if(dr[0] < - BoxR[0] / 2)
        dr[0] += BoxR[0];
    if(dr[1] > BoxR[1] / 2)
        dr[1] -= BoxR[1];
    if(dr[1] < - BoxR[1] / 2)
        dr[1] += BoxR[1];
    if(dr[2] > BoxR[2] / 2)
        dr[2] -= BoxR[2];
    if(dr[2] < - BoxR[2] / 2)
        dr[2] += BoxR[2];
    return dr.modulo();
}
