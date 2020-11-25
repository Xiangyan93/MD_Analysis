#pragma once
#include "XYHeadFile/xy.h"


class Base {
    public:
        Base() {}
        virtual ~Base() {}
        unsigned int id;
        // force field parameters
		std::vector <double> coeffs;
};
