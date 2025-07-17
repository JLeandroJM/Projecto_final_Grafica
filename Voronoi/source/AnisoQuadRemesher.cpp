// AnisoQuadRemesher.cpp
#include "AnisoQuadRemesher.h"
#include <ctime>

AnisoQuadRemesher::AnisoQuadRemesher(
    int numCluster,
    int ringLevel,
    bool validation,
    unsigned seed
) : opts_{
        static_cast<size_t>(numCluster),
        /*adaptive=*/false,
        /*anisotropic=*/true,
        /*quadMetric=*/true,
        validation,
        ringLevel,
        static_cast<int>(seed)
    },
    vclust_{opts_}
{}

void AnisoQuadRemesher::input(const std::string &inputFile) {
    vclust_.input(inputFile);
}

void AnisoQuadRemesher::start() {
    vclust_.start();
}

void AnisoQuadRemesher::build() {
    vclust_.build();
}

void AnisoQuadRemesher::output(const std::string &outputFile) {
    vclust_.output(outputFile);
}

void AnisoQuadRemesher::stat() {
    vclust_.stat();
}
