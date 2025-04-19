cmake_minimum_required(VERSION 3.14)
project(optimization_core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(pybind11 REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}/optimizers/include
    ${PROJECT_SOURCE_DIR}/portfolio/include
    ${PROJECT_SOURCE_DIR}/utils/include
)

file(GLOB_RECURSE OPTIMIZERS_SRC optimizers/src/*.cpp)
file(GLOB_RECURSE PORTFOLIO_SRC portfolio/src/*.cpp)
file(GLOB_RECURSE UTILS_SRC utilsportfolio/src/*.cpp)

set(BINDINGS_SRC bindings/bindings.cpp)

include_directories(${CMAKE_SOURCE_DIR}/external/eigen)

pybind11_add_module(_core
    ${OPTIMIZERS_SRC}
    ${PORTFOLIO_SRC}
    ${UTILS_SRC}
    ${BINDINGS_SRC}
)