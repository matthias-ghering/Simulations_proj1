cmake_minimum_required(VERSION 3.7.2)
project(simulation_1)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE ON)

# Set Compile and Linker flags

set(GCC_COVERAGE_COMPILE_FLAGS "-lfreeglut_static -lopengl32 -static-libgcc -lwinmm -lgdi32 -Wl,--subsystem,windows")
SET(GCC_COVERAGE_LINK_FLAGS    "-D FREEGLUT_STATIC")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")




set(SOURCE_FILES
        ParticleToy/CircularWireConstraint.cpp
        ParticleToy/CircularWireConstraint.h
        ParticleToy/linearSolver.cpp
        ParticleToy/linearSolver.h
        ParticleToy/Particle.cpp
        ParticleToy/Particle.h
        ParticleToy/ParticleToy.cpp
        ParticleToy/RodConstraint.cpp
        ParticleToy/RodConstraint.h
        ParticleToy/Solver.cpp
        ParticleToy/SpringForce.cpp
        ParticleToy/SpringForce.h
        ParticleToy/Force.cpp
        ParticleToy/Force.h
        ParticleToy/GravityForce.cpp
        ParticleToy/GravityForce.h
        ParticleToy/ConstraintForce.cpp
        ParticleToy/ConstraintForce.h
        )

find_package (OpenGL REQUIRED)
#find_package (GLUT REQUIRED)

link_directories(ParticleToy/lib/freeglut)

include_directories(${OPENGL_INCLUDE_DIR} ParticleToy/include)

add_executable(simulation_1 ${SOURCE_FILES})

target_link_libraries(simulation_1 ${OPENGL_LIBRARIES} freeglut)

MESSAGE( STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR} )

add_custom_command(TARGET simulation_1 POST_BUILD           # Adds a post-build event to simulation_1
        COMMAND ${CMAKE_COMMAND} -E copy_if_different       # which executes "cmake - E copy_if_different..."
        ${CMAKE_CURRENT_SOURCE_DIR}/ParticleToy/lib/freeglut/bin/freeglut.dll         # <--this is in-file
        $<TARGET_FILE_DIR:simulation_1>)                    # <--this is out-file path
