cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(Simulation)

set(CMAKE_EXE_LINKER_FLAGS "-Wl,-rpath,/usr/lib/x86_64-linux-gnu")

# Find Geant4 package
find_package(Geant4 REQUIRED ui_all vis_all)

# Include Geant4 package
include(${Geant4_USE_FILE})

# Collect source files correctly
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Include Macros
file(GLOB macros ${PROJECT_SOURCE_DIR}/macros/*.mac)

# Include DATA files
file(GLOB data ${PROJECT_SOURCE_DIR}/*.dat)


file(COPY ${macros} DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${data} DESTINATION ${PROJECT_BINARY_DIR})

# Define the executable target
add_executable(Simulation sim.cc ${sources})

# Link against Geant4 libraries
target_link_libraries(Simulation ${Geant4_LIBRARIES})

# OPTIONAL: Custom target with a different name
add_custom_target(RunSimulation DEPENDS Simulation)
