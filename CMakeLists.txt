cmake_minimum_required(VERSION 3.15)
project(test)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/protos)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})  #添加头文件
include_directories(${CMAKE_CURRENT_BINARY_DIR})  #添加头文件
add_subdirectory(protos)


link_libraries(${PROTOBUF_LIBRARIES})

add_subdirectory(src)
add_subdirectory(test)








