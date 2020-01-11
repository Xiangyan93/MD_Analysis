#pragma once
#define DP2CUT 10.0
double GetDistance(double x1, double x2, double bound){
    double dx = x1 - x2;
    if (dx > 0.5 * bound) dx -= bound;
    if (dx < -0.5 * bound) dx += bound;
    return dx;
}

class Gaussian{
    public:
        Gaussian();
        Gaussian(const std::vector <double> &cv_, const std::vector <double> &sigma_, const double height_);
        double evaluateGaussian(const std::vector <double> &cv, const std::vector <double> &lower_bounds, const std::vector <double> &upper_bounds, 
            const std::vector <bool> &periodicities) const;
        double evaluateGaussian(const std::vector <double> &cv, const std::vector <double> &lower_bounds, const std::vector <double> &upper_bounds, 
            const std::vector <bool> &periodicities, bool MPC_correction) const;
        std::vector <double> center;
        std::vector <double> sigma;
        double height;
};

Gaussian::Gaussian(){
    center.resize(0);
    sigma.resize(0);
    height =0.;
}

Gaussian::Gaussian(const std::vector <double> &cv_, const std::vector <double> &sigma_, const double height_){
    center = cv_;
    sigma = sigma_;
    height = height_;
}

double Gaussian::evaluateGaussian(const std::vector <double> &cv, const std::vector <double> &lower_bounds, const std::vector <double> &upper_bounds, 
const std::vector <bool> &periodicities) const{
    double dp2 = 0.;
    for(unsigned int i=0;i<cv.size();++i){
        double dx;
        if (periodicities[i]) dx = GetDistance(center[i], cv[i], upper_bounds[i] - lower_bounds[i]);
        else dx = center[i] - cv[i];
        double dp = dx / sigma[i];
        dp2 += dp * dp / 2;
    }
    if (dp2<DP2CUT)
        return height * exp(-dp2);
    else
        return 0.;
}

double Gaussian::evaluateGaussian(const std::vector <double> &cv, const std::vector <double> &lower_bounds, const std::vector <double> &upper_bounds, 
const std::vector <bool> &periodicities, bool MPC_correction) const{
    double dp2 = 0.;
    double mpc_factor = 1.;
    for(unsigned int i=0;i<cv.size();++i){
        double dx;
        if (periodicities[i]){
            dx = GetDistance(center[i], cv[i], upper_bounds[i] - lower_bounds[i]);
        }
        else{
            dx = center[i] - cv[i];
            double temp1 = (cv[i] - lower_bounds[i]) / sigma[i] / sqrt(2);
            double temp2 = (upper_bounds[i] - cv[i]) / sigma[i] / sqrt(2);
            mpc_factor *= 0.5 * (erf(temp1) + erf(temp2));
        }
        double dp = dx / sigma[i];
        dp2 += dp * dp / 2;
    }
    if (dp2>DP2CUT)
        return 0.;
    else if (MPC_correction)
        return height * exp(-dp2) / mpc_factor;
    else
        return height * exp(-dp2);
}