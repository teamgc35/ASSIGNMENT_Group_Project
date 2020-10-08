project(ASSIGNMENT3)
cmake_minimum_required(VERSION 3.14)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_DIR)

add_library(
    assignment STATIC
    ${SRC_DIR}
)
add_compile_options(-Wextra)

add_executable(TestCase ${PROJECT_SOURCE_DIR}/test/TestCase.c)
target_link_libraries(TestCase assignment)

add_executable(hd_program main.c)
target_link_libraries(hd_program assignment)
