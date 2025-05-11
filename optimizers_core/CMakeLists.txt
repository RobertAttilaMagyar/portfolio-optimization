cmake_minimum_required(VERSION 3.14)
project(portfolio_bindings LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(extern/pybind11)

include_directories(
    portfolio/include
    utils/include
)

pybind11_add_module(portfoliomodule
    bindings/bindings.cpp
    portfolio/src/portfolio.cpp
)