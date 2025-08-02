set(_CURRENT_PROTO_NAME naive_by_condition)
set(_CURRENT_LIB_NAME ${_CURRENT_PROTO_NAME}-lib)

file(GLOB _CURRENT_PROTO_NAME
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(${_CURRENT_LIB_NAME} ${_CURRENT_PROTO_NAME})

target_include_directories(${_CURRENT_LIB_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(${_CURRENT_LIB_NAME} PUBLIC
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
    -Wall -Wextra -Wpedantic -Werror>
    $<$<CXX_COMPILER_ID:MSVC>:
    /W4 /WX>
)
