#ifndef VERTEX_H
#define VERTEX_H
#include <Eigen/Dense>
#include <vector>
#include <set>

class Vertex
{
public:
	Vertex(void);
	Vertex(const Eigen::Vector3d&);
	Vertex(double,double,double);

	int id;
	Eigen::Vector3d pos;
	std::set<int> neighborVertexIds;
	void addNeighborV(int);
	void delNeighborV(int);
	bool hasNeighborV(int);
};
#endif 
