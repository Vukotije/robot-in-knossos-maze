cmake_minimum_required(VERSION 3.15)

# Project configuration
project(RobotInKnossosMaze 
    VERSION 1.0.0
    DESCRIPTION "A C++ maze game inspired by the Greek myth of Theseus and the Minotaur"
    LANGUAGES CXX
)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Source files
set(SOURCES
    RobotInKnossosMaze/main.cpp
    RobotInKnossosMaze/Field.cpp
    RobotInKnossosMaze/Game.cpp
    RobotInKnossosMaze/GameIO.cpp
    RobotInKnossosMaze/Item.cpp
    RobotInKnossosMaze/Maze.cpp
    RobotInKnossosMaze/MazeGenerator.cpp
)

# Header files
set(HEADERS
    RobotInKnossosMaze/Consts.h
    RobotInKnossosMaze/Field.h
    RobotInKnossosMaze/Game.h
    RobotInKnossosMaze/GameIO.h
    RobotInKnossosMaze/Item.h
    RobotInKnossosMaze/Maze.h
    RobotInKnossosMaze/MazeGenerator.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/RobotInKnossosMaze
)

# Compiler flags
if(MSVC)
    # Visual Studio specific flags
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4          # Warning level 4
        /WX-         # Warnings not as errors (for flexibility)
        /permissive- # Standards conformance mode
        /utf-8       # UTF-8 source and execution character sets
    )
    # Set subsystem to console
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
    )
else()
    # GCC/Clang flags
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# Build type specific flags
if(CMAKE_BUILD_TYPE MATCHES Release)
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE /O2)
    else()
        target_compile_options(${PROJECT_NAME} PRIVATE -O3)
    endif()
endif()

# Installation rules (optional)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Display build information
message(STATUS "")
message(STATUS "=== RobotInKnossosMaze Configuration ===")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "========================================")
message(STATUS "")
