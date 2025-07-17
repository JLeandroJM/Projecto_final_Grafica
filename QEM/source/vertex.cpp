#include "vertex.h"


Vertex::Vertex() {
    id = -99;
    neighborVertexIds.clear();
    pos = Eigen::Vector3d::Zero();
}

Vertex::Vertex(const Eigen::Vector3d& t) {
    id = -98;
    neighborVertexIds.clear();
    pos = t;
}

Vertex::Vertex(double x, double y, double z) {
    id = -97;
    neighborVertexIds.clear();
    pos = Eigen::Vector3d(x, y, z);
}

void Vertex::addNeighborV(int num){
	neighborVertexIds.insert(num);
}

void Vertex::delNeighborV(int num){
	neighborVertexIds.erase(num);
}

bool Vertex::hasNeighborV(int num){
	return (neighborVertexIds.count(num) >  0);
}


