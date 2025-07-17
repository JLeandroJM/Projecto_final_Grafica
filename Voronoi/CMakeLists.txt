cmake_minimum_required(VERSION 3.10...3.26)
project(Quadratic_remesh LANGUAGES CXX)

# Usamos C++17 y optimización
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include_directories(
    dependencies/
    dependencies/eigen/
    source/
)

set(SRC
  main.cpp
  source/AdaptiveRemesher.cpp
  source/AnisoQuadRemesher.cpp
  source/AnisoRemesher.cpp
  source/UniformRemesher.cpp
  source/vectores.cpp
)

add_executable(quadratic_remesh ${SRC})

