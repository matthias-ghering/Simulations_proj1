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
        ParticleToy/constraints/RodConstraint.cpp
        ParticleToy/constraints/RodConstraint.h
        ParticleToy/constraints/CircularWireConstraint.cpp
        ParticleToy/constraints/CircularWireConstraint.h
        ParticleToy/solvers/linearSolver.cpp
        ParticleToy/solvers/linearSolver.h
        ParticleToy/Particle.cpp
        ParticleToy/Particle.h
        ParticleToy/ParticleToy.cpp
        ParticleToy/solvers/Solver.cpp
        ParticleToy/solvers/EulerianSolver.cpp
        ParticleToy/solvers/EulerianSolver.h
        ParticleToy/solvers/ForwardEulerianSolver.cpp
        ParticleToy/solvers/ForwardEulerianSolver.h
        ParticleToy/solvers/Runge4Solver.cpp
        ParticleToy/solvers/Runge4Solver.h
        ParticleToy/solvers/MidPointSolver.cpp
        ParticleToy/solvers/MidPointSolver.h
        ParticleToy/forces/Force.h
        ParticleToy/forces/SpringForce.cpp
        ParticleToy/forces/SpringForce.h
        ParticleToy/forces/GravityForce.cpp
        ParticleToy/forces/GravityForce.h
        ParticleToy/forces/DampeningForce.cpp
        ParticleToy/forces/DampeningForce.h
        ParticleToy/forces/StaticForce.cpp
        ParticleToy/forces/StaticForce.h
        ParticleToy/forces/WallForce.cpp
        ParticleToy/forces/WallForce.h
        ParticleToy/SparseMatrix.cpp
        ParticleToy/SparseMatrix.h
        ParticleToy/constraints/Constraint.h
        ParticleToy/constraints/ConstraintSolver.h
        ParticleToy/constraints/ConstraintSolver.cpp
        ParticleToy/constraints/LineConstraint.cpp
        ParticleToy/constraints/LineConstraint.h
        ParticleToy/ParticleSystem.cpp
        ParticleToy/ParticleSystem.h
        ParticleToy/SceneBuilder.cpp
        ParticleToy/SceneBuilder.h)


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
