// clustering/VCCluster.h
#pragma once

#include <set>
#include <Eigen/Dense>
using Eigen::Matrix4d;
using Eigen::Vector3d;

#include "./utils.h"
#include "./vectores.h"
#include "VCFace.h"



class VCFace;

class VCCluster
{
private:
	void bfs(VCFace *init, set< VCFace* >* component, set<VCFace*>* unvisited = NULL){
queue<VCFace*> q;
	q.push(init);
	while (!q.empty()) {
		VCFace *f = q.front();
		q.pop();
		if (component->find(f) == component->end()) {
			if(unvisited)
				unvisited->erase(f);
			component->insert(f);
			for (VCFace* n : f->neighbor) {
				if (n->cluster == this)
					q.push(n);
			}
		}
	}

    };
protected:
	virtual void addItemAdditionalAct(VCFace* f) {}
	virtual void delItemAdditionalAct(VCFace* f) {}
	static constexpr double ENG_NULL =0;
public:
	VCCluster(int id):id(id), area(0), isNull(false), weightedSum(0,0,0){
        E.setZero();
    };

	virtual ~VCCluster(){

        for (VCFace *f : items)
		delete f;
    }; //WARNING: delete a VCCluster will delete all of its faces
	void addItem(VCFace* f){

        if (items.find(f) == items.end()) {
		items.insert(f);
		area += f->area;
		weightedSum = weightedSum + f->center * f->area;
		f->cluster = this;
		E += f->E;
		addItemAdditionalAct(f);
	}
    };
	void delItem(VCFace* f){

        auto it = items.find(f);
	if (it != items.end()) {
		items.erase(it);
		area -= f->area;
		weightedSum = weightedSum - f->center * f->area;
		f->cluster = NULL;
		E -= f->E;
		delItemAdditionalAct(f);
	}
    };
	virtual double energy(){

        Vector3d zi = center();
	return area == 0 ? ENG_NULL : area * zi.dot(zi) - 2 * zi.dot(weightedSum);
    };
	virtual double energyWithItem(VCFace* f){

        Vector3d ws = weightedSum + f->center * f->area;
	double a = area + f->area;
	Vector3d zi = center();
	return a * zi.dot(zi) - 2 * zi.dot(ws);
    };
	virtual double energyWithoutItem(VCFace* f){

        Vector3d ws = weightedSum - f->center * f->area;
	double a = area - f->area;
	Vector3d zi = center();
	return a == 0 ? ENG_NULL : a * zi.dot(zi) - 2 * zi.dot(ws);
    };
	void giveItem(VCFace* f, VCCluster *c){

        delItem(f);
	c->addItem(f);
    };
	virtual Vector3d center(){

        if (area == 0)
		return Vector3d(0,0,0);
	return weightedSum / area;
    };
	size_t size() { return items.size(); }
	bool removeUnconnected(VCCluster *cNull){

        vector< set<VCFace*> * > components;
	set<VCFace*> unvisited(items);
	while (!unvisited.empty()) {
		set<VCFace*>* comp = new set<VCFace*>();
		bfs(*unvisited.begin(), comp, &unvisited);
		components.push_back(comp);
	}
	if (components.size() <= 1) {
		if(components.size() == 1)
			delete components[0];
		return false;
	}
	set<VCFace*>* largest = *max_element(components.begin(), components.end(),
		[](set<VCFace*> * s1, set<VCFace*> * s2) -> bool { return s1->size() < s2->size(); });
	for (set<VCFace*>* s : components) {
		if (s != largest) {
			for (VCFace* item : *s) {
				giveItem(item, cNull);
			}
			delete s;
		}
	}
	delete largest;
	return true;
    };

	bool connected(){

        if (items.size() < 2) return true;
	set<VCFace*> c;
	bfs(*items.begin(), &c);
	return c.size() == items.size();
    };

	int id;
	set<VCFace*> items;
	Vector3d weightedSum; //sum(p_i*y_i)
	double area;         //sum(p_i)
	bool isNull;
	Matrix4d E;
};


