cmake_minimum_required(VERSION 3.14)
project(Demo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-m32")

aux_source_directory(src SRC_DIR)

set(SRCS ${SRC_DIR})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

set(TARGET_LIB "${PROJECT_SOURCE_DIR}/lib/libglfw3.a"
            "${PROJECT_SOURCE_DIR}/lib/libglfw3dll.a"
            "${PROJECT_SOURCE_DIR}/lib/libglew32.a"
            "${PROJECT_SOURCE_DIR}/lib/libglew32.dll.a"
        )

add_executable(Demo main.cpp ${SRCS})

target_link_libraries(Demo -lOpenGL32 -lglu32 ${TARGET_LIB})