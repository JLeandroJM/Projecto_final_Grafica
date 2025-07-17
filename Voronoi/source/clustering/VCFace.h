// clustering/VCFace.h
#pragma once

#include <set>
#include <Eigen/Dense>
#include "./utils.h"
#include "./vectores.h"


using Eigen::Matrix3d;
using Eigen::Matrix4d;
using Eigen::Vector3d;
using Eigen::Vector4d;

class VertexGroup;
class VCCluster;

class VCFace
{
public:
	int v1, v2, v3;
	Vector3d normal;
	Matrix3d K; //metric tensor
	Matrix4d E; //quadric matrix
	VCFace(int v1, int v2, int v3, VertexGroup *vg, VCCluster* c):v1(v1), v2(v2), v3(v3), cluster(c){
        Vertex* p1 = &vg->group[v1];
	Vertex* p2 = &vg->group[v2];
	Vertex* p3 = &vg->group[v3];
	Vector3d u = VCMyvecToEigen(p2->pos - p1->pos);
	Vector3d v = VCMyvecToEigen(p3->pos - p1->pos);
	Vector3d n(u.cross(v)), a(VCMyvecToEigen(p1->pos));
	normal = n.normalized();
	area = 0.5 * sqrt(n.dot(n));
	center = VCMyvecToEigen((p1->pos + p2->pos + p3->pos) / 3);
	n.normalize();
	Vector4d plane;
	plane << n.x() , n.y() , n.z() ,-n.dot(a); 
	E = plane * plane.transpose();



    };
	void addNeighbor(VCFace* f) {
		neighbor.insert(f);
	}

	set<VCFace*> neighbor;
	double area;
	Vector3d center;
	VCCluster* cluster;
};


