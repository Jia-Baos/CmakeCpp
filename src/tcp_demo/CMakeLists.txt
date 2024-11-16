cmake_minimum_required(VERSION 3.27)

project(tcp_demo)

message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Dir: ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(client)
add_subdirectory(server)
