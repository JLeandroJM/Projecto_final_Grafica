#ifndef EDGEHEAP_H
#define EDGEHEAP_H
#include "edge.h"
#include <queue>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

class EdgeHeap
{
public:
	EdgeHeap(void);
	struct cmp{
		bool operator() (Edge X, Edge Y){
			return X.costV > Y.costV;
		}
	};
	std::priority_queue<Edge,std::vector<Edge>,cmp> pq; 
	map<pair<int, int>, int> mapEdgeToID;

	bool isDeleted[20000000+1];
	int cntEdge;

	void addEdge(Edge&); 
	void delEdge(Edge);

	Edge getMinCost(); 
};
#endif
