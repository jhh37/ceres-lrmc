CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

PROJECT(lrmf_ceres)

# Find Ceres-solver
FIND_PACKAGE(Ceres REQUIRED)
if (NOT CERES_USES_MINIGLOG)
  FIND_PACKAGE(GFLAGS)
  if (GFLAGS_FOUND)
    INCLUDE_DIRECTORIES(${gflags_INCLUDE_DIR})
  endif (GFLAGS_FOUND)
endif (NOT CERES_USES_MINIGLOG)
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

# List all the libraries required.
set(LRMF_CERES_LIBRARIES ${CERES_LIBRARIES})
if (GFLAGS_FOUND)
set(LRMF_CERES_LIBRARIES ${LRMF_CERES_LIBRARIES} ${gflags_LIBRARIES})
endif (GFLAGS_FOUND)

# Create the executable.
ADD_EXECUTABLE(lrmf_ceres_exec ${SOURCES})
TARGET_LINK_LIBRARIES(lrmf_ceres_exec ${LRMF_CERES_LIBRARIES})

# Install command
INSTALL(TARGETS lrmf_ceres_exec DESTINATION ${CMAKE_INSTALL_PREFIX})
