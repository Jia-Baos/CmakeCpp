cmake_minimum_required(VERSION 3.27)

project(spd_log_demo)

message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Dir: ${CMAKE_CURRENT_SOURCE_DIR}")

# 将源代码添加到此项目的可执行文件。
aux_source_directory(. main_files)
add_executable(${PROJECT_NAME} ${main_files})

# 链接库头文件路径
target_include_directories(${PROJECT_NAME}
       PUBLIC ${CMAKE_SOURCE_DIR}/3rdparty/spdlog/include)

# 链接库文件路径
# target_link_directories()

# 链接库文件名称
# target_link_libraries()

install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})