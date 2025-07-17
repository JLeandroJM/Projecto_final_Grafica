#include "mesh.h"
Mesh::Mesh(void)
{
    numVertex = 0;
	isDeleted = new bool[1000000];
	for(int i = 0;i < 1000000;i++)
		isDeleted[i] = false;
}


int Mesh::addVertex(Vertex p){
	numVertex++;
	p.id = numVertex;
	group[numVertex] = p;
	return numVertex;
}

int Mesh::getCommonVertexNum(int u, int v){
	int cnt = 0;
	for (set<int>::iterator it = group[u].neighborVertexIds.begin();
		it != group[u].neighborVertexIds.end();it++){
			if(group[v].hasNeighborV(*it)){
				cnt++;
			}

	}
	return cnt;
}
