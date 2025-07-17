// IRemesher.h
#pragma once

#include <string>

/// Interfaz común para todos los remesher: uniform, adaptive, anisotropic, anisotropic+quad
class IRemesher {
public:
    virtual ~IRemesher() = default;

    /// Carga la malla de entrada
    virtual void input(const std::string &inputFile) = 0;

    /// Ejecuta el algoritmo de remeshing (paso principal)
    virtual void start() = 0;

    /// Construye o refina la estructura interna tras el cálculo
    virtual void build() = 0;

    /// Exporta la malla resultante a disco
    virtual void output(const std::string &outputFile) = 0;

    /// Imprime estadísticas, logs o métricas finales
    virtual void stat() = 0;
};
