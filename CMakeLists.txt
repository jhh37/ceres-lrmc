CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(lrmf_ceres)

FIND_PACKAGE(Ceres REQUIRED)
INCLUDE_DIRECTORIES(${CERES_INCLUDE_DIRS})

# C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(SOURCES
    Ceres/main.cpp
    Ceres/experiment.cpp
    Ceres/matrix.cpp
    Ceres/residuals_analytic.cpp
    Ceres/residuals_autodiff.cpp
    Ceres/options.cpp
    Ceres/parser.cpp
)

# LRMC
ADD_EXECUTABLE(lrmf_ceres_exec ${SOURCES})
TARGET_LINK_LIBRARIES(lrmf_ceres_exec ${CERES_LIBRARIES})
