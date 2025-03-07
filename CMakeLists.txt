cmake_minimum_required(VERSION 3.20)
project(test)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION OFF)
# 禁用未使用变量警告（可选）
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE BOOL "")
# 用于生成错误信息
include(${CMAKE_CURRENT_SOURCE_DIR}/GitErrorCMakeLists.txt)

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










