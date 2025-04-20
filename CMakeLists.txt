cmake_minimum_required(VERSION 3.10)
project(cache_simulator VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Add source files
set(SOURCES
    src/main.cpp
    src/cache/core/cache_block.cpp
    src/cache/core/cache_set.cpp
    src/cache/simulator/cache_simulator.cpp
    src/cache/simulator/statistics.cpp
    src/utils/address_utils.cpp
    src/utils/math_utils.cpp
)

# Add the main executable
add_executable(cache_simulator ${SOURCES})


if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt)
    enable_testing()
    add_subdirectory(tests)
endif()


if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/examples/CMakeLists.txt)
    add_subdirectory(examples)
endif() 