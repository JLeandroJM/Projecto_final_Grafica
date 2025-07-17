

 //clustering/VCEdge.h
#include "./vectores.h"
#include "VCFace.h"
#include "VCEdge.h"
#include "VCClusterAniso.h"
#include "VCClusterAnisoQuad.h"
#include "VCClusterQuad.h"
#include "VCCluster.h"


#pragma once

/* sort three number in ascending order */
template< typename T >
inline void VCSort3(T& a, T& b, T& c) {
	if (b > c) std::swap(b, c);
	if (a > b) std::swap(a, b);
	if (b > c) std::swap(b, c);
}

inline void make_coord_space(Matrix3d &o2w, const Vector3d & n) {
	Vector3d z = Vector3d(n);
	Vector3d h = z;
	if (fabs(h.x()) <= fabs(h.y()) && fabs(h.x()) <= fabs(h.z())) h.x() = 1.0;
	else if (fabs(h.y()) <= fabs(h.x()) && fabs(h.y()) <= fabs(h.z())) h.y() = 1.0;
	else h.z() = 1.0;
	
	z = z.normalized();
	Vector3d y = h.cross(z);
	y = y.normalized();
	Vector3d x = z.cross(y);
	x = x.normalized();
	
	o2w.col(0) = x;
	o2w.col(1) = y;
	o2w.col(2) = z;
}

struct VCPair {
	int a, b;
	VCPair(int a, int b) :
		a(a), b(b) {}
};

struct VCEdgeItemCmp {
	bool operator()(const VCPair& lhs, const VCPair& rhs) const {
		if (lhs.a < rhs.a)
			return true;
		if (lhs.a > rhs.a)
			return false;
		return lhs.b < rhs.b;
	}
	bool operator()(const VCEdge& lhs, const VCEdge& rhs) const {
		if (lhs.f1 < rhs.f1)
			return true;
		if (lhs.f1 > rhs.f1)
			return false;
		return lhs.f2 < rhs.f2;
	}
};


class VertexClustering
{
public:
	struct Options {
		size_t numCluster;
		bool adaptive;
		bool anisotropic;
		bool quadMetric;
		bool validation;
		int ringLevel;
		int seed;
	};
	VertexClustering(Options &opts): cntFace(0){
        srand(opts.seed);
	if (opts.anisotropic) {
		opts.adaptive = true;
	}
	this->opts = opts;
	vGroup = new VertexGroup();
	vGroupNew = NULL;
	angle_min = 180;
	angle_less_30 = 100;
	clusters.resize(opts.numCluster + 1); 
	if (opts.anisotropic) {
		if (opts.quadMetric) {
			for (int i = 0; i < clusters.size(); i++)
				clusters[i] = new VCClusterAnisoQuad(i);
		}
		else {
			for (int i = 0; i < clusters.size(); i++)
				clusters[i] = new VCClusterAniso(i);
		}
	}
	else
		if (opts.quadMetric) {
			for (int i = 0; i < clusters.size(); i++)
				clusters[i] = new VCClusterQuad(i);
		}
		else {
			for (int i = 0; i < clusters.size(); i++)
				clusters[i] = new VCCluster(i);
		}
	clusters[0]->isNull = true;


    };
	~VertexClustering(void){

        for (int i = 0; i < clusters.size(); i++)
		delete clusters[i];
	delete vGroup;
	if (vGroupNew)
		delete vGroupNew;
    };
	void input(const std::string& filePath) {
    FILE* fin = fopen(filePath.c_str(), "r");
    if (!fin) {
        std::cerr << "Error abriendo archivo: " << filePath << "\n";
        return;
    }

    int cntv = 0, cntf = 0;
    char s[256], _;
    std::vector<VCEdge> edges;
    std::vector<VCFace*> faces;

    while (fgets(s, sizeof s, fin) != nullptr) {
        switch (s[0]) {
        case '#': 
            break; 
        case 'v': {
            cntv++;
            double x, y, z;
            sscanf(s, "%c%lf%lf%lf", &_, &x, &y, &z);
            if (std::isnan(x) || std::isnan(y) || std::isnan(z)) {
                std::cout << "warning: nan vertex in input\n";
            }
            vGroup->addVertex(Vertex(x, y, z));
            break;
        }
        case 'f': {
            cntf++;
            cntFace++;
            int a, b, c;
            sscanf(s, "%c%d%d%d", &_, &a, &b, &c);
            VCSort3(a, b, c);

            // Conectar vecinos en el grupo de vértices
            vGroup->group[a].addNeighborVertex(b);
            vGroup->group[a].addNeighborVertex(c);
            vGroup->group[b].addNeighborVertex(a);
            vGroup->group[b].addNeighborVertex(c);
            vGroup->group[c].addNeighborVertex(a);
            vGroup->group[c].addNeighborVertex(b);

            // Crear la cara y agregarla al clúster 0
            VCFace* face = new VCFace(a, b, c, vGroup, clusters[0]);
            clusters[0]->addItem(face);
            faces.push_back(face);

            // Construir el mapa de aristas
            VCPair pairs[3] = { VCPair(a,b), VCPair(a,c), VCPair(b,c) };
            for (int i = 0; i < 3; ++i) {
                auto iter = edgeMap.find(pairs[i]);
                if (iter != edgeMap.end()) {
                    iter->second.f2 = face;
                    iter->second.f1->addNeighbor(face);
                    face->addNeighbor(iter->second.f1);
                    edges.push_back(iter->second);
                } else {
                    edgeMap[pairs[i]] = VCEdge(face, nullptr);
                }
            }
            break;
        }
        default: 
            break;
        }
    }
    fclose(fin);

    if (opts.adaptive) {
        calcCurvature(faces);  // solo para remeshing adaptativo
    }

    initClusters(edges);
    for (auto &e : edges) {
        if (e.isBoundary())
            boundary.push(e);
    }
}



	void start(){
        printf("--- first clustering iteration ---\n");
	computeClusters(false); 
	if (opts.validation) {
		if (removeUnconnected()) {
			printf("---second clustering iteration---\n");
			computeClusters(true);
		}
	}
    };
	void build(){
        	printf("start to rebuild the mesh from the clusters\n");
	clock_t start = clock();
	if (vGroupNew)
		delete vGroupNew;
	vGroupNew = new VertexGroup();
	for (int i = 1; i < clusters.size(); i++) {
		vGroupNew->addVertex(Vertex(VCEigenToMyvec(clusters[i]->center())));
		if (clusters[i]->size() == 0)
			vGroupNew->delVertex(i);
	}

	while(boundary.size() > 0) {
		VCEdge e = boundary.front();
		boundary.pop();
		if (e.isBoundary()) {
			int v1 = e.f1->cluster->id;
			int v2 = e.f2->cluster->id;
			vGroupNew->group[v1].addNeighborVertex(v2);
			vGroupNew->group[v2].addNeighborVertex(v1);
		}
	}
	//refine
	for (int i = 1; i <= vGroup->cntVertex; i++) {
		if (vGroup->isDeleted[i])
			continue;
		set<int> cset;
		Vertex* v = &vGroup->group[i];
		for (int u : v->neighborVertexIds) {
			VCPair pair(min(i, u), max(i, u));
			auto edgeIt = edgeMap.find(pair);
			if (edgeIt != edgeMap.end()) {
				if(edgeIt->second.f1)
					cset.insert(edgeIt->second.f1->cluster->id);
				if(edgeIt->second.f2)
					cset.insert(edgeIt->second.f2->cluster->id);
			}
		}
		if (cset.size() >= 4) {
			localRefine(cset);
		}
	}
	printf("Done, uses %lf s for building.\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    };

	void output(const string& filePath){
        FILE *f = fopen(filePath.c_str(), "w");
	if (!vGroupNew) {
		printf("please run build() before output()\n");
		return;
	}
	int cnt = 0;
	int cntf = 0;
	int cnt_less_30 = 0;
	for (int i = 1; i <= vGroupNew->cntVertex; i++) {
		if (vGroupNew->isDeleted[i])
			continue;
		Vertex* v = &vGroupNew->group[i];
		cnt++;
		v->id = cnt;
		fprintf(f, "v %lf %lf %lf\n", v->pos.x, v->pos.y, v->pos.z);
	}
	for (int i = 1; i <= vGroupNew->cntVertex; i++) {
		if (vGroupNew->isDeleted[i])
			continue;
		Vertex* v = &(vGroupNew->group[i]);
		for (set<int>::iterator it1 = v->neighborVertexIds.begin(); it1 != v->neighborVertexIds.end(); it1++) {
			if (i >= (*it1))
				continue;
			for (set<int>::iterator it2 = v->neighborVertexIds.begin(); it2 != v->neighborVertexIds.end(); it2++) {
				if ((*it1) < (*it2) && (vGroupNew->group[*it1].hasNeighborVertex(*it2))) {
					Vertex* v1 = &vGroupNew->group[*it1];
					Vertex* v2 = &vGroupNew->group[*it2];
					double a1 = angleBetween(v1->pos - v->pos, v2->pos - v->pos);
					double a2 = angleBetween(v->pos - v1->pos, v2->pos - v1->pos);
					double a3 = angleBetween(v->pos - v2->pos, v1->pos - v2->pos);
					VCSort3(a1, a2, a3);
					if (a1 < angle_min) angle_min = a1;
					if (a1 < 30) cnt_less_30++;
					if (a2 < 30) cnt_less_30++;
					fprintf(f, "f %d %d %d\n", v->id, vGroupNew->group[(*it1)].id, vGroupNew->group[(*it2)].id);
					cntf++;
				}
			}
		}
	}
	angle_less_30 = 100.0 * cnt_less_30 / (3.0 * cntf);

    };
	void stat(){
        printf("angle min: %lf\n", angle_min);
	printf("angle less than 30: %lf%%\n", angle_less_30);
    };
private:
	VertexGroup* vGroup;
	VertexGroup* vGroupNew;
	vector<VCCluster *> clusters;
	map<VCPair, VCEdge, VCEdgeItemCmp> edgeMap;
	queue<VCEdge> boundary;
	size_t cntFace;
	double angle_min;
	double angle_less_30;
	Options opts;
	
	void initClusters(vector<VCEdge>& edges){
        int n = edges.size();
	set<VCFace*> faces;
	if (opts.numCluster > n)
		opts.numCluster = n;
	while (faces.size() < opts.numCluster) {
		while (true) {
			int r = rand() % n;
			VCFace* f = edges[r].f1;
			if (faces.find(f) == faces.end()) {
				faces.insert(f);
				break;
			}
		}
	}
	vector<VCFace*> faces_vec(faces.begin(), faces.end());
	for (int i = 0; i < opts.numCluster; ++i) {
		clusters[0]->giveItem(faces_vec[i], clusters[i + 1]);
	}
    };

	void pushNeighbors(VCFace* f, VCEdge& e, queue<VCEdge> *q){
        VCEdge e1(edgeMap[VCPair(f->v1, f->v2)]);
	VCEdge e2(edgeMap[VCPair(f->v1, f->v3)]);
	VCEdge e3(edgeMap[VCPair(f->v2, f->v3)]);
	if (e1 == e) {
		q->push(e2);
		q->push(e3);
	}
	else if (e2 == e) {
		q->push(e1);
		q->push(e3);
	}
	else {
		q->push(e1);
		q->push(e2);
	}
    };

	double totalEnergy(){
        double energy = 0;
	for (int i = 0; i < clusters.size(); ++i) {
		energy += clusters[i]->energy();
	}
	return energy;
    };

	void calcCurvature(vector<VCFace *> &faces){
        printf("start to calculate curvature for %lu faces...\n", faces.size());
	clock_t start = clock();
	int cnt = 0, n10 = faces.size() / 10, percent = 1;
	for (VCFace* f : faces) {
		set<int> rings(collectRings(f));
		vector<Vector3d> pts(rings.size());
		int i = 0;
		Vector3d origin = f->center;
		for (int id : rings)
			pts[i++] = vGroup->group[id].pos - origin;
		Matrix3d o2w;
		make_coord_space(o2w, f->normal);
		Matrix3d w2o = o2w.transpose();
		for (i = 0; i < pts.size(); i++) {
			pts[i] = w2o * pts[i]; //now pts are in object coordinate
		}
		vector<double> poly(leastSquareFitting(pts));
		Matrix2d eVecs;
		Vector2d eValues;
		double weight = localCurvature(poly, eValues, eVecs);
		f->area *= weight;       //update density based on curvature
		if (opts.anisotropic) {  
			//D1, D2 are the priciple directions in xyz coordinate, their eigenvalues are principle curvatures
			Vector3d D1 = (o2w.col(0) * eVecs(0, 0) + o2w.col(1) * eVecs(1, 0)).normalized();
			Vector3d D2 = (o2w.col(0) * eVecs(0, 1) + o2w.col(1) * eVecs(1, 1)).normalized();
			Matrix3d Rotation;
			Rotation.col(0) = D1;
			Rotation.col(1) = D2;
			Rotation.col(2) = D1.cross(D2);
			Matrix3d Stretch;
			Stretch << fabs(eValues(0)), 0, 0,
				0, fabs(eValues(1)), 0,
				0, 0, max(fabs(eValues(0)), fabs(eValues(1)));
			f->K = Rotation * Stretch * Rotation.transpose(); //compute the Riemannian metric
		}
		if (++cnt > n10) {
			printf("%%%d...\n", 10 * percent);
			n10 = faces.size() / 10.0 * ++percent;
		}
	}
	printf("Done, uses %lf s for curvature.\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    };
	set<int> collectRings(VCFace* f){
        set<int> rings;
	queue< tuple<int, int> > q;
	q.push(make_tuple(f->v1, 0));
	q.push(make_tuple(f->v2, 0));
	q.push(make_tuple(f->v3, 0));
	while (!q.empty()) {
		tuple<int, int> t = q.front();
		q.pop();
		int d = get<1>(t);
		if (d > opts.ringLevel)
			break;
		int v = get<0>(t);
		if (rings.find(v) == rings.end()) {
			rings.insert(v);
			for (int neighbor : vGroup->group[v].neighborVertexIds) {
				q.push(make_tuple(neighbor, d + 1));
			}
		}
	}
	return rings;
    };
	vector<double> leastSquareFitting(const vector<Vector3d> &data){
        const int SIZE = 5;
	MatrixXd A(data.size(), SIZE);
	VectorXd w(SIZE), b(data.size());
	for (int i = 0; i < data.size(); i++) {
		A.row(i) << data[i].x(),
			data[i].y(),
			data[i].x() * data[i].x(),
			data[i].x()* data[i].y(),
			data[i].y()* data[i].y();
		b(i) = data[i].z();
	}
	MatrixXd At(A.transpose());
	w = (At * A).inverse() * At * b;
	vector<double> ret(SIZE);
	for (int i = 0; i < ret.size(); i++)
		ret[i] = w(i);
	return ret;
    };

	double localCurvature(const vector<double>& poly, Vector2d& egs, Matrix2d& evs){
        double sa1 = poly[0] * poly[0];
	double sa2 = poly[1] * poly[1];
	double b = 1 / sqrt(sa1 + sa2 + 1);
	double E = 1 + sa1;
	double F = poly[1] * poly[0];
	double G = 1 + sa2;
	double e = 2 * poly[2] * b;
	double f = poly[3] * b;
	double g = 2 * poly[4] * b;
	Matrix2d m1, m2;
	m1 << -e, -f, -f, -g;
	m2 << E, F, F, G;
	Matrix2d m = m1 * m2.inverse();
	Eigen::EigenSolver<Matrix2d> solver;
	solver.compute(m, true);
	egs = solver.eigenvalues().real();
	evs = solver.eigenvectors().real();
	return egs.dot(egs);
    };

	double quadricCost(const Matrix4d& E, const Vector3d& v) {
		Vector4d v4;
		v4 << v(0), v(1), v(2), 1;
		return v4.transpose() * E * v4;
	}
	void localRefine(const set<int> &cset){
        //build a min heap
	deque<int> ring = sortNeighbor(cset);
	if (ring.size() != cset.size())
		return; //not a maniford, cannot refine
	typedef tuple<int, int, double> CostPair;
	auto cmp = [](const CostPair e1, const CostPair & e2) -> bool {return get<2>(e1) < get<2>(e2); };
	set<CostPair, decltype(cmp)> candidates(cmp);
	Matrix4d E;
	E.setZero();
	for (int c : cset)
		E += clusters[c]->E;
	for (int a : cset) {
		for (int b : cset) {
			if (a < b && !vGroupNew->group[a].hasNeighborVertex(b)) {
				Vec3d v1 = vGroupNew->group[a].pos;
				Vec3d v2 = vGroupNew->group[b].pos;
				Vector3d m = VCMyvecToEigen(v1 + v2) / 2;
				double cost = quadricCost(E, m);
				candidates.insert(make_tuple(a, b, cost));
			}
		}
	}
	int r = ring.size();
	if (candidates.size() <= r - (int)3)
		return;
	auto find_order = [&ring](int i) -> int
		{ return find(ring.begin(), ring.end(), i) - ring.begin(); };
	while (!candidates.empty()) {
		auto first = candidates.begin();
		CostPair pair = *first;
		candidates.erase(first);
		int a = get<0>(pair), b = get<1>(pair);
		vGroupNew->group[a].addNeighborVertex(b);
		vGroupNew->group[b].addNeighborVertex(a);
		int ai = find_order(a), bi = find_order(b);
		if (ai > bi)
			swap(ai, bi);
		auto iter = candidates.begin();
		while (iter != candidates.end()) {
			CostPair e = *iter;
			int ci = find_order(get<0>(e)), di = find_order(get<1>(e));
			if (ci > di) {
				swap(ci, di);
			}
			if ((ci < ai && di < bi) || (ci > ai && di > bi)) {
				iter = candidates.erase(iter);
			}
			else {
				++iter;
			}
		}
	}
    };

	deque<int> sortNeighbor(const set<int>& neighbor){
        set<int> unsorted(neighbor);
	int first = *(unsorted.begin());
	unsorted.erase(first);
	deque<int> q;
	q.push_back(first);
	while (!unsorted.empty()) {
		bool modified = false;
		for (int n : unsorted) {
			if (vGroupNew->group[q.front()].hasNeighborVertex(n)) {
				q.push_front(n);
				unsorted.erase(n);
				modified = true;
				break;
			}
			if (vGroupNew->group[q.back()].hasNeighborVertex(n)) {
				q.push_back(n);
				unsorted.erase(n);
				modified = true;
				break;
			}
		}
		if (!modified)
			break;
	}
	return q;
        
    };
	void computeClusters(bool constrain){
        	queue<VCEdge> boundary_next;
	queue<VCEdge> *q1 = &boundary, *q2 = &boundary_next;
	int modification;
	int iteration = 0;
	clock_t start = clock();
	printf("---start clustering, with total energy: %.12lf---\n", totalEnergy());
	do {
		modification = 0;
		set<VCEdge, VCEdgeItemCmp> tested;
		while (!q1->empty()) {
			VCEdge e = q1->front();
			q1->pop();
			if (e.isBoundary() && tested.find(e) == tested.end()) {
				tested.insert(e);
				VCCluster *c1 = e.f1->cluster;
				VCCluster *c2 = e.f2->cluster;
				if (localEnergyRelease(c1, c2, e, q2, constrain)) {
					modification++;
				}
			}
		}
		printf("iteration: %d, modification: %d, ", ++iteration, modification);
		printf("total energy: %.12lf\n", totalEnergy());
		std::swap(q1, q2);
	} while (modification > 0);
	if (boundary.empty())
		boundary = boundary_next;

	printf("Done, uses %lf s for clustering.\n", (double)(clock() - start) / CLOCKS_PER_SEC);
	printf("---total energy: %.12lf---\n", totalEnergy());

    };
	bool removeUnconnected(){
        bool notDone = false;
	for (int i = 1; i < clusters.size(); i++) {
		if (clusters[i]->removeUnconnected(clusters[0])) {
			notDone = true;
		}
	}
	return notDone;

    };
	bool transferLeadsToDisconnect(VCCluster* c1, VCFace* f){
        c1->delItem(f);
	bool ret = c1->connected();
	c1->addItem(f);
	return !ret;
    };
	bool localEnergyRelease(VCCluster* c1, VCCluster* c2, VCEdge& e, queue<VCEdge>* q2, bool constrain){
        	double L0, L1, L2;
	if (c1->isNull) goto localEnergyRelease_c1_c2;
	if (c2->isNull) goto localEnergyRelease_c2_c1;
	L0 = c1->energy() + c2->energy();
	L1 = c1->energyWithItem(e.f2) + c2->energyWithoutItem(e.f2);
	L2 = c1->energyWithoutItem(e.f1) + c2->energyWithItem(e.f1);
	double minEnergy;
	if (constrain) {
		bool c1_ok = transferLeadsToDisconnect(c1, e.f1);
		bool c2_ok = transferLeadsToDisconnect(c2, e.f2);
		if (!c2_ok) 
			L1 = numeric_limits<double>::max();
		if (!c1_ok) 
			L2 = numeric_limits<double>::max();
	}
	minEnergy = min(min(L0, L1), L2);
	if (minEnergy == L1) 
		goto localEnergyRelease_c2_c1;
	else if (minEnergy == L2) 
		goto localEnergyRelease_c1_c2;
	q2->push(e);
	return false;

localEnergyRelease_c2_c1:
	c2->giveItem(e.f2, c1);
	pushNeighbors(e.f2, e, q2);
	return true;
localEnergyRelease_c1_c2:
	c1->giveItem(e.f1, c2);
	pushNeighbors(e.f1, e, q2);
	return true;
    };
};




