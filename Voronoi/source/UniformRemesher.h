// UniformRemesher.h
#pragma once

#include "IRemesher.h"
#include "./clustering/VertexClustering.h"
#include <string>
#include <ctime>

class UniformRemesher : public IRemesher {
public:
    UniformRemesher(
        int numCluster = 400,
        int ringLevel  = 2,
        bool validation = false,
        unsigned seed   = static_cast<unsigned>(std::time(nullptr))
    );

    void input(const std::string &inputFile) override;
    void start() override;
    void build() override;
    void output(const std::string &outputFile) override;
    void stat() override;

private:
    VertexClustering::Options opts_;
    VertexClustering            vclust_;
};
