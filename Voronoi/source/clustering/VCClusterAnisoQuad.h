

 //clustering/VCEdge.h
#include "./vectores.h"
#include "VCFace.h"
#include "VCClusterAniso.h"
#include "VCClusterQuad.h"
#include "VCCluster.h" 

#pragma once

class VCClusterAnisoQuad : public VCClusterAniso, public VCIQuad
{
public:
	VCClusterAnisoQuad(int id) : VCClusterAniso(id)
	{
	}
	virtual double energyWithItem(VCFace* f) override{
        Matrix3d sK = sumK + f->K;
	Vector3d sKP = sumKPos + f->K * f->center;
	Matrix4d Eo = E + f->E;
	Vector3d zi = center(Eo, sK, sKP);
	return zi.dot(sK * zi) - 2 * zi.dot(sKP);
    };
	virtual double energyWithoutItem(VCFace* f) override{
        if (items.size() <= 1)
		return ENG_NULL;
	Matrix3d sK = sumK - f->K;
	Vector3d sKP = sumKPos - f->K * f->center;
	Matrix4d Eo = E - f->E;
	Vector3d zi = center(Eo, sK, sKP);
	return zi.dot(sK * zi) - 2 * zi.dot(sKP);
    };
	virtual Vector3d center() override{
        return center(E, sumK, sumKPos);
    };
	Vector3d center(const Matrix4d& E, const Matrix3d& sumK, const Vector3d& sumKPos){
        Vector3d x;
	if (solveQuadMetric(E, x))
		return x;
	return VCClusterAniso::center(sumK, sumKPos);
    };
};


