cmake_minimum_required(VERSION 3.10)

# Project name and language
project(MemSim C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Enable warnings
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")

# Source files
set(SOURCES
    memsim.c
    LRUMethod.c
    clock.c
    rand.c
)

# Header files (optional)
set(HEADERS
    page.h
    LRUMethod.h
    clock.h
    rand.h
)

# Create executable
add_executable(memsim ${SOURCES} ${HEADERS})
