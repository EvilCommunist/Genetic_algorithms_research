cmake_minimum_required(VERSION 3.15)
project(GeneticAlgorithms2D LANGUAGES CXX)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

add_executable(app 
    main.cpp
    GA/unit.cpp
    GA/genetic_islands.cpp
    GA/genetic_common.cpp
)

target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/GA)
target_link_libraries(app PRIVATE Threads::Threads)