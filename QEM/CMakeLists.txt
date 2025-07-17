cmake_minimum_required(VERSION 3.1)
project(final_proj)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-O3")


include_directories(dependencies/ dependencies/eigen/ source/ )

add_executable(final_proj 
	main.cpp
        source/Remeshing.cpp
	source/edge.cpp
	source/edgeHeap.cpp
	source/vertex.cpp
        source/mesh.cpp
)

target_link_libraries(final_proj -pthread)

