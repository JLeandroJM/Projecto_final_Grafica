#include "Remeshing.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>

int contarVertices(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        if (line.substr(0, 2) == "v ") count++;
    }
    return count;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Uso: final_proj <archivo_entrada.obj> <archivo_salida.obj> <vértices_deseados>\n";
        return 1;
    }

    std::string archivoEntrada = argv[1];
    std::string archivoSalida = argv[2];
    int verticesDeseados = std::atoi(argv[3]);

    if (verticesDeseados <= 0) {
        std::cerr << "Número de vértices inválido.\n";
        return 1;
    }

    int inputVerts = contarVertices(archivoEntrada);
    if (inputVerts == 0) {
        std::cerr << "No se encontraron vértices en el archivo de entrada.\n";
        return 1;
    }

    float radio = static_cast<float>(verticesDeseados) / inputVerts;
    std::cout << "Ratio ajustado: " << radio << " (de " << inputVerts << " a " << verticesDeseados << " vértices)" << std::endl;

    std::ifstream inFile(archivoEntrada);
    std::ofstream outFile(archivoSalida);

    auto t_start = std::chrono::high_resolution_clock::now();

    Remeshing* ms = new Remeshing();
    ms->setRatio(radio);

    auto t1 = std::chrono::high_resolution_clock::now();
    ms->input(inFile);
    auto t2 = std::chrono::high_resolution_clock::now();
    ms->Remesh();
    auto t3 = std::chrono::high_resolution_clock::now();
    ms->output(outFile);
    auto t4 = std::chrono::high_resolution_clock::now();

    delete ms;

    std::chrono::duration<double> total = t4 - t_start;
    std::chrono::duration<double> t_input = t2 - t1;
    std::chrono::duration<double> t_remesh = t3 - t2;
    std::chrono::duration<double> t_output = t4 - t3;

    std::cout << "Remeshing completado.\n";
    std::cout << "Tiempo total:    " << total.count()   << " s\n";
    std::cout << "Lectura:         " << t_input.count()  << " s\n";
    std::cout << "Remallado:      " << t_remesh.count() << " s\n";
    std::cout << "Escritura:       " << t_output.count() << " s\n";

    return 0;
}
