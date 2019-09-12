cmake_minimum_required(VERSION 3.14)
project(Demo)

set(CMAKE_CXX_STANDARD 14)


aux_source_directory(src SRC_DIR)
aux_source_directory(Include/common COMMON_DIR)

set(SRCS ${SRC_DIR})
set(COMMON ${COMMON_DIR})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Include)
include_directories(${PROJECT_SOURCE_DIR}/Include/common)
link_directories(${PROJECT_SOURCE_DIR}/lib)

set(TARGET_LIB  "${PROJECT_SOURCE_DIR}/lib/libglfw3.a"
                "${PROJECT_SOURCE_DIR}/lib/libglfw3dll.a"
        )

add_executable(Demo main.cpp ${SRCS} ${COMMON})

target_link_libraries(Demo ${TARGET_LIB})