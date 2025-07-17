// // main.cpp

// #include "UniformRemesher.h"
// #include "AdaptiveRemesher.h"
// #include "AnisoRemesher.h"
// #include "AnisoQuadRemesher.h"

// int main() {
//     // -------------------------------
//     // 1) Remeshing Uniforme
//     // -------------------------------
//     // {
//     //     UniformRemesher remesher(
//     //         /* numCluster */ 800,
//     //         /* ringLevel  */ 2,
//     //         /* validation */ false
//     //         // semilla por defecto = time(nullptcr)
//     //     );
//     //     remesher.input("../models/dragon.obj");
//     //     remesher.start();
//     //     remesher.build();
//     //     remesher.output("../output/dragon_uniform.obj");
//     //     remesher.stat();
//     // }

//     // -------------------------------
//     // 2) Remeshing Adaptativo
//     // -------------------------------

//     // {
//     //     AdaptiveRemesher remesher(
//     //         /* numCluster */ 500,
//     //         /* ringLevel  */ 3,
//     //         /* validation */ true
//     //     );
//     //     remesher.input("meshes/entrada.obj");
//     //     remesher.start();
//     //     remesher.build();
//     //     remesher.output("outputs/entrada_adaptativo.obj");
//     //     remesher.stat();
//     // }

    


//     // -------------------------------
//     // 3) Remeshing Anisotrópico
//     // -------------------------------
    
//     {
//         AnisoRemesher remesher(
//             /* numCluster */ 1000,
//             /* ringLevel  */ 2,
//             /* validation */ false
//         );
//         remesher.input("../models/dragon.obj");
//         remesher.start();
//         remesher.build();
//         remesher.output("../output/dragon_anisotropico.obj");
//         remesher.stat();
//     }
    

//     // -------------------------------
//     // 4) Remeshing Anisotrópico + Cuadrática
//     // -------------------------------
    
//     // {
//     //     AnisoQuadRemesher remesher(
//     //         /* numCluster */ 300,
//     //         /* ringLevel  */ 2,
//     //         /* validation */ false
//     //     );
//     //     remesher.input("meshes/entrada.obj");
//     //     remesher.start();
//     //     remesher.build();
//     //     remesher.output("outputs/entrada_aniso_quad.obj");
//     //     remesher.stat();
//     // }
    

//     return 0;
// }

#include <iostream>
#include <string>
#include <cstdlib>
#include "UniformRemesher.h"
#include "AdaptiveRemesher.h"
#include "AnisoRemesher.h"
#include "AnisoQuadRemesher.h"

int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cerr << "Uso: " << argv[0] << " <modo: 0=uniform, 1=adaptive, 2=aniso, 3=anisoquad> <input.obj> <output.obj> <numCluster>\n";
        return 1;
    }

    int modo = std::atoi(argv[1]);
    std::string input = argv[2];
    std::string output = argv[3];
    int numCluster = std::atoi(argv[4]);

    int ringLevel = 2;
    bool validation = false;

    switch (modo) {
        case 0: {
            UniformRemesher remesher(numCluster, ringLevel, validation);
            remesher.input(input);
            remesher.start();
            remesher.build();
            remesher.output(output);
            remesher.stat();
            break;
        }
        case 1: {
            validation = true;
            ringLevel = 3;
            AdaptiveRemesher remesher(numCluster, ringLevel, validation);
            remesher.input(input);
            remesher.start();
            remesher.build();
            remesher.output(output);
            remesher.stat();
            break;
        }
        case 2: {
            AnisoRemesher remesher(numCluster, ringLevel, validation);
            remesher.input(input);
            remesher.start();
            remesher.build();
            remesher.output(output);
            remesher.stat();
            break;
        }
        case 3: {
            AnisoQuadRemesher remesher(numCluster, ringLevel, validation);
            remesher.input(input);
            remesher.start();
            remesher.build();
            remesher.output(output);
            remesher.stat();
            break;
        }
        default:
            std::cerr << "Modo no válido. Usa 0 (uniform), 1 (adaptive), 2 (aniso), o 3 (anisoquad)\n";
            return 1;
    }

    return 0;
}
