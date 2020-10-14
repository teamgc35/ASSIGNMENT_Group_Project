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
add_compile_options(-Wextra -Werror -ansi -std=c99)

add_executable(TestCase_Encryption ${PROJECT_SOURCE_DIR}/test/TestCase_Encryption.c)
target_link_libraries(TestCase_Encryption assignment)

add_executable(TestCase_LinkedList ${PROJECT_SOURCE_DIR}/test/TestCase_LinkedList.c)
target_link_libraries(TestCase_LinkedList assignment)

add_executable(TestCase_Array ${PROJECT_SOURCE_DIR}/test/TestCase_Array.c)
target_link_libraries(TestCase_Array assignment)

add_executable(hd_program main.c)
target_link_libraries(hd_program assignment)
