#ifndef UTILS_H
#define UTILS_H
#include "vectores.h"
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <iostream>

using namespace std;

using namespace Eigen;


/* some helper functions */

static Vec3d VCEigenToMyvec(const Vector3d& v) {
	return Vec3d(v.x(), v.y(), v.z());
}
static Vector3d VCMyvecToEigen(const Vec3d& v) {
	return Vector3d(v.x, v.y, v.z);
}

static Vector3d operator- (const Vec3d& v1, const Vector3d& v2) {
	return Vector3d(v1.x - v2.x(), v1.y - v2.y(), v1.z - v2.z());
}
static Vector3d operator- (const Vector3d & v1, const Vec3d & v2) {
	return Vector3d(v1.x() - v2.x, v1.y() - v2.y, v1.z() - v2.z);
}

static double angleBetween(Vec3d v1, Vec3d v2) {
	const double PI = atan(1) * 4;
	Vec3d u1(v1.getUnitVectorOfThis()), u2(v2.getUnitVectorOfThis());
	return acos(u1.getDot(u2))* 180.0 / PI; //in degrees
}


class Edge
{
public:
	Edge(int _u = -99,int _v = -99){
      id = -999;
        v1 = _u;
        v2 = _v;
        costV = INF * 1.0;

  };
	~Edge(void){};
	int id; 
	int v1,v2; 
	Vec3d v; 
	double costV; 
};



class EdgeHeap
{
public:
	EdgeHeap(void){
cntEdge = 0;
	for(int i = 0;i < MAX_NUM_EDGES;i++)
		isDeleted[i] = false;
  };
	~EdgeHeap(void){};
	struct cmp{
		bool operator() (Edge X, Edge Y){
			return X.costV > Y.costV;
		}
	};
	priority_queue<Edge,vector<Edge>,cmp> pq; 
	map<pair<int, int>, int> mapEdgeToID; 
	bool isDeleted[MAX_NUM_EDGES+1];
	int cntEdge; 
	void addEdge(Edge& e){
        cntEdge++;
          e.id = cntEdge;
          int u = min(e.v1,e.v2);
          int v = max(e.v1,e.v2);	
          mapEdgeToID[make_pair(u,v)] = cntEdge;
          pq.push(e);

  }; 
	void delEdge(Edge e){
      int u = min(e.v1,e.v2);
      int v = max(e.v1,e.v2);
      int ID = mapEdgeToID[make_pair(u,v)];
      isDeleted[ID] = true;
};
	Edge getMinCost(){

        if(pq.size() <= 0){
        return Edge(0,0);
      }
      while(isDeleted[pq.top().id]){
        pq.pop();
      }
      Edge e = pq.top();
      pq.pop();
      return e;
      }; 
};




class MA
{
public:
	MA(void){
    for(int i = 0;i < 4;i++){
		for(int j = 0;j < 4;j++){
			mat[i][j] = 0;
		}
	}
  };

	double mat[5][5];
	friend MA operator + (const MA& A, const MA& B){

    
	MA m;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m.mat[i][j] = A.mat[i][j] + B.mat[i][j];
	return m;



  };
};


class Solve
{
public:
	Solve(MA& _m,Vector4& _v){
	for(int i = 0;i < 4;i++)
		for(int j = 0;j < 4;j++)
			m.mat[i][j] = _m.mat[i][j];
	for(int i  =0;i < 4;i++)
		v.v[i] = _v.v[i];
};
	~Solve(void){};
	Vector4 getAns(){
	for (int i = 0; i < 4; i++) {
		int j = 0;
		while (j < 4 && fabs(m.mat[i][j]) < EPS)
			j++;
		if (j == 4)
			continue;
		for (int k = 0; k < 4; k++) {
			if (k != i) {
				double rate = m.mat[k][j] / m.mat[i][j];
				 for (int l = 0; l < 4; l++)
					m.mat[k][l] -= m.mat[i][l] * rate;
				v.v[k] -= v.v[i] * rate;
			}
		}
	}	
	Vector4 X;
	for (int i = 0; i < 4; i++) {
		int j = 0;
		while (j < 4 && fabs(m.mat[i][j]) < EPS)
			j++;
		if (j == 4)
			return Vector4(0, 0, 0, -1);
		X.v[i] = v.v[i] / m.mat[i][j];
	}
	X.v[4] = 1;
	return X;
};
	MA m;
	Vector4 v;
};






class Vertex
{
public:
	Vertex(void){
    id = -99;
      neighborVertexIds.clear();
  };
	Vertex(Vec3d t){
        id = -98;
      neighborVertexIds.clear();
      pos = t;
  };
	Vertex(double x,double y,double z)
    {
      id = -97;
      neighborVertexIds.clear();
      pos = Vec3d(x,y,z);
    }
	~Vertex(void){};

	int id;
	Vec3d pos;
	set<int> neighborVertexIds;
	void addNeighborVertex(int num){
	neighborVertexIds.insert(num);
};
	void delNeighborVertex(int num){
	neighborVertexIds.erase(num);
};
	bool hasNeighborVertex(int num){
	return (neighborVertexIds.count(num) >  0);
};
};



class VertexGroup
{
public:
	VertexGroup(void){
	cntVertex = 0;
	isDeleted = new bool[MAX_NUM_VERTICES];
	for(int i = 0;i < MAX_NUM_VERTICES;i++)
		isDeleted[i] = false;
};
	~VertexGroup(void){};
	Vertex group[MAX_NUM_VERTICES];
	int cntVertex;
	bool* isDeleted;
	int addVertex(Vertex p){
    cntVertex++;
    p.id = cntVertex;
    group[cntVertex] = p;
    return cntVertex;
};
	void delVertex(int _id){
	if(_id >= MAX_NUM_VERTICES){
		return;
	}	
	isDeleted[_id] = true;

	for(set<int>::iterator it = group[_id].neighborVertexIds.begin();it != group[_id].neighborVertexIds.end();it++){
		group[(*it)].delNeighborVertex(_id);
	}

};
	int getCommonVertexNum(int u,int v){
	int cnt = 0;
	for (set<int>::iterator it = group[u].neighborVertexIds.begin();
		it != group[u].neighborVertexIds.end();it++){
			if(group[v].hasNeighborVertex(*it)){
				cnt++;
			}

	}
	return cnt;
};
};






#endif