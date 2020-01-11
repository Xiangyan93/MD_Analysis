#pragma once
#include "../../CPP_HEAD/XYHeadFile/xy.h"
#include "gaussian.h"
class FreeEnergySurface{
    public:
        FreeEnergySurface(const std::vector <double> &lower_bounds_, const std::vector <double> &upper_bounds_, 
            const std::vector <bool> &periodicities_);
        FreeEnergySurface(const std::vector <double> &lower_bounds_, const std::vector <double> &upper_bounds_, 
            const std::vector <bool> &periodicities_, const std::vector <unsigned int> &bins_);
        void AddGaussian(const Gaussian &hill);
        void AddGaussian(const Gaussian &hill, bool MPC_correction, double bias_factor);
        void WriteFES(std::string filename) const;

    private:
        unsigned int dimension;
        std::vector <double> lower_bounds;
        std::vector <double> upper_bounds;
        std::vector <bool> periodicities;
        std::vector <unsigned int> bins;
        std::vector <unsigned int> bins_1;// = bins + 1
        std::vector <double> spacings;
        std::vector <std::vector <double>> cv;
        std::vector <double> fe;
};

FreeEnergySurface::FreeEnergySurface(const std::vector <double> &lower_bounds_, const std::vector <double> &upper_bounds_, 
const std::vector <bool> &periodicities_){
    FreeEnergySurface(lower_bounds_, upper_bounds_, periodicities_, std::vector <unsigned int> (lower_bounds_.size(), 50));
}

FreeEnergySurface::FreeEnergySurface(const std::vector <double> &lower_bounds_, const std::vector <double> &upper_bounds_, 
const std::vector <bool> &periodicities_, const std::vector <unsigned int> &bins_){
    if (lower_bounds_.size() != upper_bounds_.size() || lower_bounds_.size() != periodicities_.size() || lower_bounds_.size() != bins_.size()){
        printf("%ld,%ld,%ld,%ld\n", lower_bounds_.size(), upper_bounds_.size(), periodicities_.size(), bins_.size());
        error("FreeEnergySurface Initialization failed\n");
    }
    dimension = lower_bounds_.size();
    lower_bounds = lower_bounds_;
    upper_bounds = upper_bounds_;
    periodicities = periodicities_;
    bins = bins_;
    for(unsigned i=0;i<bins.size();++i){
        bins_1.push_back(bins[i] + 1);
        spacings.push_back( ( upper_bounds[i] - lower_bounds[i] ) / bins[i] );
    }
    for(std::vector <unsigned int> idx(dimension, 0);;IDXPlusOne(idx, bins_1)){
        std::vector <double> _cv(dimension, 0.);
        for(unsigned int i=0;i<dimension;++i){
            _cv[i] = lower_bounds[i] + spacings[i] * idx[i];
        }
        cv.push_back(_cv);
        fe.push_back(0.);
        if (cv.size() == GetProduct(bins_1)) break;
    }
}

void FreeEnergySurface::AddGaussian(const Gaussian &hill){
    for(unsigned int i=0;i<cv.size();++i){
        fe[i] += - hill.evaluateGaussian(cv[i], lower_bounds, upper_bounds, periodicities, false);
    }
}

void FreeEnergySurface::AddGaussian(const Gaussian &hill, bool MPC_correction, double bias_factor){
    for(unsigned int i=0;i<cv.size();++i){
        if (bias_factor > 1.)
            fe[i] += - bias_factor / (bias_factor - 1) * hill.evaluateGaussian(cv[i], lower_bounds, upper_bounds, periodicities, MPC_correction);
        else
            fe[i] += - hill.evaluateGaussian(cv[i], lower_bounds, upper_bounds, periodicities, MPC_correction);
    }
}

void FreeEnergySurface::WriteFES(std::string filename) const{
    FILE *fp = fopen(filename.c_str(), "w");
    for(unsigned int i=0;i<cv.size();++i){
        for(unsigned int j=0;j<cv[i].size();++j){
            fprintf(fp, "%f\t", cv[i][j]);
        }
        fprintf(fp, "%f\n", fe[i]);
    }
    fclose(fp);
}