#include "edgeHeap.h"
#include "mesh.h"
#include <cstdlib>
#include <cstdio>
#include <string>
#include <Eigen/Dense>

using namespace std;
class Remeshing
{
	double ratio;
	int numFace,numDelFace;
	EdgeHeap* Heap;
	Mesh* mesh;
public:
	Remeshing(void);
	~Remeshing(void);

	void setRatio(double);

	void input(std::istream&);
	void Remesh();
	void output(std::ostream&);

	Eigen::Matrix4d vertexQuadErrMx(int);
	Eigen::Vector3d vertexPos(Edge &e, const Eigen::Matrix4d &m);
	
	void contractionCost(Edge &e);
};
