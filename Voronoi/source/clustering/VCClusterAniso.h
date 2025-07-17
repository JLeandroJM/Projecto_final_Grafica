

 //clustering/VCEdge.h
#include "./vectores.h"
#include "VCFace.h"
#include "VCCluster.h" 

#pragma once

class VCClusterAniso : public VCCluster
{
protected:
	Matrix3d sumK;
	Vector3d sumKPos;
	virtual void addItemAdditionalAct(VCFace* f) override{
        sumK = sumK + f->K;
	sumKPos = sumKPos + f->K * f->center;
    };
	virtual void delItemAdditionalAct(VCFace* f) override{
        sumK = sumK - f->K;
	sumKPos = sumKPos - f->K * f->center;
    };
public:
	VCClusterAniso(int id) : VCCluster(id)
	{
		sumK.setZero();
		sumKPos.setZero();
	}
	virtual double energy() override{
        Vector3d zi = center();
	return zi.dot(sumK * zi) - 2 * zi.dot(sumKPos);
    };
	virtual double energyWithItem(VCFace* f) override{
        Matrix3d sK = sumK + f->K;
	Vector3d sKP = sumKPos + f->K * f->center;
	Vector3d zi = center(sK, sKP);
	return zi.dot(sK * zi) - 2 * zi.dot(sKP);
    };
	virtual double energyWithoutItem(VCFace* f) override{
        if (items.size() <= 1)
		return ENG_NULL;
	Matrix3d sK = sumK - f->K;
	Vector3d sKP = sumKPos - f->K * f->center;
	Vector3d zi = center(sK, sKP);
	return zi.dot(sK * zi) - 2 * zi.dot(sKP);
    };


	virtual Vector3d center()override {
        return center(sumK, sumKPos);
    };


	Vector3d center(const Matrix3d& sumK, const Vector3d &sumKPos){
        bool valid;
	Matrix3d sumKInv;
	double det;
	sumK.computeInverseAndDetWithCheck(sumKInv, det, valid);
	if (!valid) {
		return Vector3d(0, 0, 0);
	}
	return sumKInv * sumKPos;
    };
};






