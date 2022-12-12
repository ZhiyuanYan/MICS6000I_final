cmake_minimum_required(VERSION 3.4)

project(floorplan)



set(CMAKE_CXX_STANDARD 17)
# add_subdirectory(src)


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# aux_source_directory(. MAIN_LIST)
aux_source_directory(src SRC_LIST)

add_library(source ${SRC_LIST})



add_executable(floorplan main.cpp)
TARGET_LINK_LIBRARIES(floorplan source)