#ifndef EDGE_H
#define EDGE_H
#include <Eigen/Dense>
#include <cstdlib>
#include <cstdio>

class Edge
{
public:
	Edge(int _u = -99,int _v = -99);

	int id; 
	int v1,v2; 
	Eigen::Vector3d v; 
	double costV; 
};

#endif