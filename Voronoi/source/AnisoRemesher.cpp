// AnisoRemesher.cpp
#include "AnisoRemesher.h"
#include <ctime>

AnisoRemesher::AnisoRemesher(
    int numCluster,
    int ringLevel,
    bool validation,
    unsigned seed
) : opts_{
        static_cast<size_t>(numCluster),
        /*adaptive=*/false,
        /*anisotropic=*/true,
        /*quadMetric=*/false,
        validation,
        ringLevel,
        static_cast<int>(seed)
    },
    vclust_{opts_}
{}

void AnisoRemesher::input(const std::string &inputFile) {
    vclust_.input(inputFile);
}

void AnisoRemesher::start() {
    vclust_.start();
}

void AnisoRemesher::build() {
    vclust_.build();
}

void AnisoRemesher::output(const std::string &outputFile) {
    vclust_.output(outputFile);
}

void AnisoRemesher::stat() {
    vclust_.stat();
}
