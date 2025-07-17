
 //clustering/VCEdge.h
#include "./vectores.h"
#include "VCFace.h"
#include "VCCluster.h" 

#pragma once



struct VCIQuad {
	virtual bool solveQuadMetric(const Matrix4d& E, Vector3d& result){

        Matrix4d E1;
	E1.row(0) = E.row(0);
	E1.row(1) << E(0, 1), E(1, 1), E(1, 2), E(1, 3);
	E1.row(2) << E(0, 2), E(1, 2), E(2, 2), E(2, 3);
	E1.row(3) << 0, 0, 0, 1;
	Vector4d b, x;
	b << 0, 0, 0, 1;
	x = E1.colPivHouseholderQr().solve(b);
	double relative_error = (E1 * x - b).norm() / b.norm();
	result(0) = x(0);
	result(1) = x(1);
	result(2) = x(2);
	return relative_error < 1e-6;
    }
    ;
};

class VCClusterQuad : public VCCluster, public VCIQuad
{
public:
	VCClusterQuad(int id) : VCCluster(id) {}
	virtual double energyWithItem(VCFace* f) override{
        Matrix4d Eo = E + f->E;
	Vector3d ws = weightedSum + f->center * f->area;
	double a = area + f->area;
	Vector3d zi = center(Eo);
	return a * zi.dot(zi) - 2 * zi.dot(ws);
    };
	virtual double energyWithoutItem(VCFace* f) override{
        if (items.size() <= 1)
		return ENG_NULL;
	Matrix4d Eo = E - f->E;
	Vector3d ws = weightedSum - f->center * f->area;
	double a = area - f->area;
	Vector3d zi = center(Eo);
	return a == 0 ? ENG_NULL : a * zi.dot(zi) - 2 * zi.dot(ws);
    };
	virtual Vector3d center() override{
        return center(E);
    };
	Vector3d center(const Matrix4d& E){
        Vector3d x;
	if (solveQuadMetric(E, x))
		return x;
	return VCCluster::center();
    };
};






