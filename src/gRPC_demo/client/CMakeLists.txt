cmake_minimum_required(VERSION 3.27)

project(gRPC_client)

message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Dir: ${CMAKE_CURRENT_SOURCE_DIR}")

# 将源代码添加到此项目的可执行文件。
file(GLOB FILES_SRC "./*.cpp" "../proto/*.cc")
file(GLOB FILES_HEADERS "./*.h""../proto/*.h")
add_executable(${PROJECT_NAME} ${FILES_SRC} ${FILES_HEADERS})

# 查找 gRPC 和 Protobuf
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using protobuf-${Protobuf_VERSION}")
message(STATUS "Using gRPC-${gRPC_VERSION}")

# 链接库头文件路径
target_include_directories(${PROJECT_NAME}
       PUBLIC ${FILES_HEADERS} ${GRPC_INCLUDE_DIRS} ${PROTOBUF_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})

# 链接库文件路径
# target_link_directories()

# 链接库文件名称
# target_link_libraries(${PROJECT_NAME}
       PUBLIC gtest gtest_main gRPC::grpc++_reflection protobuf::libprotobuf)

install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})
