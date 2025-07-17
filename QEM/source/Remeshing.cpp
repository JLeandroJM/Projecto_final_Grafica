#include "Remeshing.h"

Remeshing::Remeshing(void)
{
    Heap = new EdgeHeap();
    mesh = new Mesh();
    numFace = 0;
}


Remeshing::~Remeshing(void)
{
}

void Remeshing::contractionCost(Edge& e) {
    Eigen::Matrix4d vMatrix = vertexQuadErrMx(e.v1) + vertexQuadErrMx(e.v2);
    e.v = vertexPos(e, vMatrix);

    Eigen::Vector4d X(e.v[0], e.v[1], e.v[2], 1.0);

    if (mesh->getCommonVertexNum(e.v1, e.v2) != 2) {
        e.costV = 0;
        return;
    }

    double error = X.transpose() * vMatrix * X;
    e.costV = error;
}

Eigen::Matrix4d Remeshing::vertexQuadErrMx(int _id) {
    Eigen::Matrix4d quadErr = Eigen::Matrix4d::Zero();
    Vertex* pv = &(mesh->group[_id]);

    for (auto it1 = pv->neighborVertexIds.begin(); it1 != pv->neighborVertexIds.end(); ++it1) {
        for (auto it2 = pv->neighborVertexIds.begin(); it2 != pv->neighborVertexIds.end(); ++it2) {
            if ((*it1) < (*it2) && mesh->group[*it1].hasNeighborV(*it2)) {
                Vertex* v1 = &(mesh->group[*it1]);
                Vertex* v2 = &(mesh->group[*it2]);

                Eigen::Vector3d edge1 = v1->pos - pv->pos;
                Eigen::Vector3d edge2 = v2->pos - pv->pos;

                Eigen::Vector3d norm = edge1.cross(edge2).normalized();
                double poffset = -pv->pos.dot(norm);

                Eigen::Vector4d plane(norm[0], norm[1], norm[2], poffset);

                quadErr += plane * plane.transpose();
            }
        }
    }

    return quadErr;
}

Eigen::Vector3d Remeshing::vertexPos(Edge& e, const Eigen::Matrix4d& m) {
    Eigen::Vector3d mid = (mesh->group[e.v1].pos + mesh->group[e.v2].pos) / 2.0;

    Eigen::Matrix4d A = m;
    A.row(3) = Eigen::Vector4d(0, 0, 0, 1);

    Eigen::Vector4d b(0, 0, 0, 1);
    Eigen::Vector4d x = A.fullPivLu().solve(b);

    if (std::isnan(x[0]) || std::isnan(x[1]) || std::isnan(x[2]))
        return mid;

    return x.head<3>();
}

void Remeshing::setRatio(double _ratio){
    ratio = _ratio;
}

void Remeshing::input(std::istream& in) {
    std::string line;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "#" || prefix.empty()) {
            continue;
        } else if (prefix == "v") {
            double x, y, z;
            iss >> x >> y >> z;
            mesh->addVertex(Vertex(x, y, z));
        } else if (prefix == "f") {
            int a, b, c;
            iss >> a >> b >> c;
            numFace++;

            mesh->group[a].addNeighborV(b);
            mesh->group[a].addNeighborV(c);
            mesh->group[b].addNeighborV(a);
            mesh->group[b].addNeighborV(c);
            mesh->group[c].addNeighborV(a);
            mesh->group[c].addNeighborV(b);
        }
    }

    for (int i = 1; i <= mesh->numVertex; i++) {
        for (auto it : mesh->group[i].neighborVertexIds) {
            if (i < it) break;
            Edge e(it, i);
            contractionCost(e);
            Heap->addEdge(e);
        }
    }

    numDelFace = static_cast<int>((1 - ratio) * numFace);
}

void Remeshing::Remesh(){
	for(int i = 0; i < numDelFace; i += 2){
		Edge e = Heap->getMinCost();
		Vertex* v1 = &(mesh->group[e.v1]);
		Vertex* v2 = &(mesh->group[e.v2]);
		Vertex v0 = e.v;
		int v0_id = mesh->addVertex(v0);

		set<int> neighborV;
		neighborV.clear();
		Heap->delEdge(e);

		for(set<int>::iterator it = v1->neighborVertexIds.begin(); it != v1->neighborVertexIds.end();it++){
			if((*it)!=v2->id){
				Heap->delEdge(Edge((*it), v1->id));
                mesh->group[(*it)].delNeighborV(v1->id);
				neighborV.insert((*it));
			}

		}

		for(set<int>::iterator it = v2->neighborVertexIds.begin(); it != v2->neighborVertexIds.end();it++){
			if((*it)!=v1->id){
				Heap->delEdge(Edge((*it), v2->id));
                mesh->group[(*it)].delNeighborV(v2->id);
				neighborV.insert((*it));
			}

		}

		for (set<int>::iterator it = neighborV.begin();it != neighborV.end(); it++) {
            mesh->group[(*it)].addNeighborV(v0_id);
            mesh->group[v0_id].addNeighborV(*it);
		}
        mesh->isDeleted[v1->id] = true;
        mesh->isDeleted[v2->id] = true;

		for (set<int>::iterator it = neighborV.begin(); it != neighborV.end(); it++) {
			Edge e((*it),v0_id);
            contractionCost(e);
			Heap->addEdge(e);
		}

	}

}

void Remeshing::output(std::ostream& os) {
    int cnt = 0;
    int cntf = 0;

    for (int i = 1; i <= mesh->numVertex; i++) {
        if (mesh->isDeleted[i]) continue;
        Vertex* v = &mesh->group[i];
        cnt++;
        v->id = cnt;
        os << "v " << v->pos.x() << " " << v->pos.y() << " " << v->pos.z() << "\n";
    }

    for (int i = 1; i <= mesh->numVertex; i++) {
        if (mesh->isDeleted[i]) continue;
        Vertex* v = &mesh->group[i];
        for (auto it1 = v->neighborVertexIds.begin(); it1 != v->neighborVertexIds.end(); ++it1) {
            if (i >= *it1) continue;
            for (auto it2 = v->neighborVertexIds.begin(); it2 != v->neighborVertexIds.end(); ++it2) {
                if (*it1 < *it2 && mesh->group[*it1].hasNeighborV(*it2)) {
                    os << "f " << v->id << " " << mesh->group[*it1].id << " " << mesh->group[*it2].id << "\n";
                    cntf++;
                }
            }
        }
    }
}