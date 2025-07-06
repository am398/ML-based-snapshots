cmake_minimum_required(VERSION 3.17)
project(adaptive_snapshots)
set(CMAKE_CXX_STANDARD 17)

set(Python_ROOT_DIR "C:/Program Files/WindowsApps/PythonSoftwareFoundation.Python.3.13_3.13.1520.0_x64__qbz5n2kfra8p0")
set(Python_INCLUDE_DIRS "C:/Program Files/WindowsApps/PythonSoftwareFoundation.Python.3.13_3.13.1520.0_x64__qbz5n2kfra8p0/Include")
set(Python_LIBRARIES "C:/Program Files/WindowsApps/PythonSoftwareFoundation.Python.3.13_3.13.1520.0_x64__qbz5n2kfra8p0/libs/python313.lib")

find_package(pybind11 REQUIRED HINTS "C:/Users/anuj.maurya/AppData/Local/Packages/PythonSoftwareFoundation.Python.3.13_qbz5n2kfra8p0/LocalCache/local-packages/Python313/site-packages/pybind11")


add_library(snapshot_predictor snapshot_predictor.cpp)
target_include_directories(snapshot_predictor PRIVATE 
    ${Python_INCLUDE_DIRS}
    ${pybind11_INCLUDE_DIRS}
)
target_link_libraries(snapshot_predictor PRIVATE
    ${Python_LIBRARIES}
    pybind11::embed
 )

add_executable(demo demo_main.cpp)
target_link_libraries(demo PRIVATE snapshot_predictor)


