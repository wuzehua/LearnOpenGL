cmake_minimum_required(VERSION 3.14)
project(Demo)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(src SRC_DIR)

set(SRCS ${SRC_DIR})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(Demo main.cpp ${SRCS})

target_link_libraries(Demo ${PROJECT_SOURCE_DIR}/lib/libglfw3.a ${PROJECT_SOURCE_DIR}/lib/libglfw3dll.a)