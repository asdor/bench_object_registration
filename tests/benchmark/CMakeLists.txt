find_package(benchmark REQUIRED)

file(GLOB BENCH_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(${PROJECT_NAME}-bench ${BENCH_SRC})

target_link_libraries(${PROJECT_NAME}-bench
    PRIVATE
        benchmark::benchmark_main
        naive_by_condition-lib
        compile_time_by_variant-lib
        compile_time_by_variant_factory-lib
        compile_time_by_variant_self_reg-lib
        virtual_factory-lib
        virtual_factory_self_reg-lib
)
