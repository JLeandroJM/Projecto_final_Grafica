 //clustering/VCEdge.h
#include "./vectores.h"
#include "VCFace.h"
#pragma once

class VCFace;

/// Representa una arista entre dos caras
class VCEdge
{
public:
	VCFace* f1, * f2;
	VCEdge() : f1(NULL), f2(NULL) {}
	VCEdge(VCFace* f1, VCFace* f2) : f1(f1), f2(f2) {}
	bool isBoundary(){
        if (!f2 || !f1) return false;
	return f1->cluster != f2->cluster;
};
	bool operator==(const VCEdge &e) const {
		return (f1 == e.f1 && f2 == e.f2) || (f2 == e.f1 && f1 == e.f2);
	}
};

