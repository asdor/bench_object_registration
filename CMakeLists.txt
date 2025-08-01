cmake_minimum_required(VERSION 3.23)
project(test_self_registration VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/compile_time_by_variant)
add_executable(test_self_registration main.cpp)

target_link_libraries(test_self_registration
    PRIVATE
        compile_time_by_variant-lib
)
