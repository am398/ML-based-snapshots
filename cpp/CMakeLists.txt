cmake_minimum_required(VERSION 3.17)
project(adaptive_snapshots)

set(CMAKE_CXX_STANDARD 17)

# point PYTHON_EXECUTABLE to your venv python
set(pybind11_DIR "${CMAKE_SOURCE_DIR}/../ml/.venv/Lib/site-packages/pybind11/share/cmake/pybind11")
find_package(pybind11 REQUIRED CONFIG)

add_library(snapshot_predictor snapshot_predictor.cpp)
target_link_libraries(snapshot_predictor PRIVATE pybind11::embed)

add_executable(demo demo_main.cpp)
target_link_libraries(demo PRIVATE snapshot_predictor)
