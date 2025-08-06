cmake_minimum_required(VERSION 3.23)
project(bench_object_registration VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(${PROJECT_SOURCE_DIR}/cmake/utils.cmake)

add_subdirectory(src/compile_time_by_variant)
add_subdirectory(src/compile_time_by_variant_self_reg)
add_subdirectory(src/naive_by_condition)
add_subdirectory(src/virtual_factory)
add_subdirectory(src/virtual_factory_self_reg)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests/unit_tests)
    add_subdirectory(tests/benchmark)
endif()
