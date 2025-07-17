// AdaptiveRemesher.cpp
#include "AdaptiveRemesher.h"
#include <ctime>

AdaptiveRemesher::AdaptiveRemesher(
    int numCluster,
    int ringLevel,
    bool validation,
    unsigned seed
) : opts_{
        static_cast<size_t>(numCluster),
        /*adaptive=*/true,
        /*anisotropic=*/false,
        /*quadMetric=*/false,
        validation,
        ringLevel,
        static_cast<int>(seed)
    },
    vclust_{opts_}
{}

void AdaptiveRemesher::input(const std::string &inputFile) {
    vclust_.input(inputFile);
}

void AdaptiveRemesher::start() {
    vclust_.start();
}

void AdaptiveRemesher::build() {
    vclust_.build();
}

void AdaptiveRemesher::output(const std::string &outputFile) {
    vclust_.output(outputFile);
}

void AdaptiveRemesher::stat() {
    vclust_.stat();
}
