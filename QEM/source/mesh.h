#include "vertex.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Mesh
{
public:
	Mesh(void);
	Vertex group[1000000];
	
	int numVertex;
	bool* isDeleted;

	int addVertex(Vertex);
	int getCommonVertexNum(int,int);
};

