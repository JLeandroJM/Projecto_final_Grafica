// UniformRemesher.cpp
#include "UniformRemesher.h"
#include <ctime>

UniformRemesher::UniformRemesher(
    int numCluster,
    int ringLevel,
    bool validation,
    unsigned seed
) : opts_{
        static_cast<size_t>(numCluster),
        /*adaptive=*/false,
        /*anisotropic=*/false,
        /*quadMetric=*/false,
        validation,
        ringLevel,
        static_cast<int>(seed)
    },
    vclust_{opts_}
{}

void UniformRemesher::input(const std::string &inputFile) {
    vclust_.input(inputFile);
}

void UniformRemesher::start() {
    vclust_.start();
}

void UniformRemesher::build() {
    vclust_.build();
}

void UniformRemesher::output(const std::string &outputFile) {
    vclust_.output(outputFile);
}

void UniformRemesher::stat() {
    vclust_.stat();
}
