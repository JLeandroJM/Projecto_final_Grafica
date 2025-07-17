# Remeshing 3D 🔍
## Descripción del Proyecto

El remeshing es una técnica fundamental en el procesamiento de geometría tridimensional, cuyo objetivo principal es modificar o mejorar la estructura de una malla existente sin alterar significativamente su forma o características geométricas. Las mallas, estan compuestas por vértices, aristas y caras, se utilizan para representar superficies y volúmenes en una amplia variedad de aplicaciones como simulaciones físicas, gráficos por computadora, impresión 3D, entre otras. Es por ello que en este proyecto se presentan dos modelos de remeshing que se basan en errores cuadricos y diagramas de voronoi.

## Integrantes del Equipo

|    Jean Pierre Sotomayor    |    Leandro Machaca    |    Gonzalo Rodriguez    |
| ----------- | ----------- | ----------- |
| ![](https://avatars.githubusercontent.com/u/85184643?v=4) | ![](https://avatars.githubusercontent.com/u/102132128?s=400&v=4) | ![](https://avatars.githubusercontent.com/u/85299734?v=4) |
| [github.com/JeanPierre](https://github.com/Jeanpierrre) | [github.com/JLeandroJM](https://github.com/JLeandroJM) | [github.com/Gonzalo-Rod](https://github.com/Gonzalo-Rod) 


## Estructura del Repositorio

- 📁 `backend`: En esta carpeta se encuentran los archivos necesarios para ejecutar el backend del proyecto
- | 📄 `backend.js`: En esta carpeta se encuentran los documentos de texto que explican el proyecto.
- | 📄 `quadric_remeshing.exe`: Ejecutable del modelo de Quadric Error.
- | 📄 `quadratic_remesh.exe`: Ejecutable del modelo de Voronoi.
- 📁 `frontend`: En esta carpeta se encuentran los archivos necesarios para ejecutar el frontend del proyecto
- | 📁 `src`: Carpeta con los recursos para ejecutar la aplicacion web.
- | | 📄 `main.js`: Archivo principal con logica de ejecucion de web.
- | | 📄 `App.vue`: Archivo con la base de Vue
- | | 📁 `components`: Componentes de Vue para iniciar la aplicacion web.
- | 📄 `index.html`: Base HTML para inicializar web.
- 📁 `QEM`: En esta carpeta se encuentran los archivos del modelo de Quadric Errors
- | 📁 `src`: Carpeta donde se encuentran los archivos necesarios para hace le error cuadratico
- | 📁 `dependencies`: Dependencias como librerias que se necesitan para ejecutar el remeshing
- | 📄 `CMakeList.txt`: CMAKE para crear un ejecutable del quadratic remeshing
- | 📄 `main.cpp`: Archivo principal para ejecuat el remeshing con Quadartic error
- 📁 `Voronoi`: En esta carpeta se encuentran los archivos del modelo de Voronoi
- | 📁 `source`: Archivo que contiene las clases de cada tipo de remeshing Voronoi
- | 📁 `dependencies`: Dependencias como librerias que se necesitan para ejecutar el remeshing
- | 📄 `CMakeList.txt`: CMAKE para crear un ejecutable del voronoi remeshing
- | 📄 `main.cpp`: Archivo principal para ejecuat el remeshing con tecnicas de Voronoi

# Remeshing (Backend)

## Flujo de Ejecucion

| Paso | Clase / Función clave                 | Breve descripción                                |
|------|---------------------------------------|--------------------------------------------------|
| 1    | `main.cpp`                            | Parsea CLI y crea el **Remesher** adecuado.      |
| 2    | `Remesher::input()`                   | Carga `.obj` y rellena `VertexGroup`.            |
| 3    | `VertexClustering::start()`           | Primera iteración de agrupamiento de caras.      |
| 4    | `VertexClustering::build()`           | Reconstruye la malla reducida.                   |
| 5    | `VertexClustering::output()`          | Escribe el resultado a disco.                    |
| 6    | `VertexClustering::stat()`            | Imprime métricas (ángulo mínimo, etc.).          |

## Clases auxiliares

| Archivo                     | Responsabilidad                                                                               |
|-----------------------------|-----------------------------------------------------------------------------------------------|
| `UniformRemesher`           | Implementa la **Malla Homogénea** (densidad fija).                                            |
| `AdaptiveRemesher`          | Implementa la **Malla Sensible a Curvatura** (densidad variable).                             |
| `AnisoRemesher`             | Implementa la **Malla Tensorial** (métrica anisotrópica).                                     |
| `AnisoQuadRemesher`         | Implementa la **Malla Cuádrica-Tensorial** (tensor + métrica cuádruple).                      |
| `VertexClustering`          | Orquesta todo el proceso: parseo OBJ, clustering iterativo, reconstrucción y exportación.     |
| `VCCluster (+derivadas)`    | Gestionan grupos de caras; calculan energía y centro según la métrica correspondiente.        |
| `VCFace / VCEdge`           | Representan primitivas de la topología (caras y aristas).                                     |

## Wiki
Para más información sobre nuestra implementación, puedes visitar nuestra [Wiki](https://github.com/Jeanpierrre/Computaci-n-Gr-fica--Remeshing/wiki/Abstract) donde encontrarás más detalles sobre el proyecto.


## Compilación

```bash
git clone <repo-url>
cd <repo>/build
cmake ..          
make -j$(nproc)    # genera el binario ./project_final

```

## Ejecucion del Proyecto

Ejemplo para el AnisoRemesh

```cpp
{
        AnisoRemesher remesher(
            /* numCluster */ 1000,
            /* ringLevel  */ 2,
            /* validation */ false
        );
        remesher.input("../models/dragon.obj");
        remesher.start();
        remesher.build();
        remesher.output("../output/dragon_anisotropico.obj");
        remesher.stat();
    }

```

# Ejecucion de Aplicación de Remeshing

## Inicia Backend:

1. Navega a la carpeta `Backend`:
   ```bash
   cd backend
   ```
2. Instala las dependencias necesarias:
   ```bash
   npm install express cors
   ```
3. Inicia el servidor:
   ```bash
   node backend.js
   ```

## FrontEnd:

1. Instala las dependencias necesarias:
   ```bash
   npm install
   ```
2. Inicia el servidor de desarrollo:
   ```bash
   npm run dev
   ```

### Ejecución por Consola

1. Navega a la carpeta del modelo:
   ```bash
   cd "modelo"
   ```
2. Crea una carpeta de compilación:
   ```bash
   mkdir build
   cd build
   ```
3. Configura el proyecto con CMake:
   ```bash
   cmake ..
   ```
4. Extrae la carpeta de dependencias.
5. Compila el proyecto:
   ```bash
   cmake --build .
   ```
   Esto generará el archivo ejecutable `modelo.exe`.
   
7. Para ejecutar el archivo ejecutable:
   ```bash
   modelo.exe input_obj output_obj
   ```
