CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(je_ceres_lrmc)

FIND_PACKAGE(Ceres REQUIRED)
INCLUDE_DIRECTORIES(${CERES_INCLUDE_DIRS})

set(SOURCES
    LRMC/main.cpp
    LRMC/je_experiment.cpp
    LRMC/je_matrix.cpp
    LRMC/je_residuals_analytic.cpp
    LRMC/je_residuals_autodiff.cpp
    LRMC/je_options.cpp
    LRMC/je_parser.cpp
)

# LRMC
ADD_EXECUTABLE(je_ceres_lrmc ${SOURCES})
TARGET_LINK_LIBRARIES(je_ceres_lrmc ${CERES_LIBRARIES})