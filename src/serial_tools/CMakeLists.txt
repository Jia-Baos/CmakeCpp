cmake_minimum_required(VERSION 3.27)

project(serial_tools)

message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Dir: ${CMAKE_CURRENT_SOURCE_DIR}")

# 将源代码添加到此项目的可执行文件。
aux_source_directory(. main_files)
add_executable(${PROJECT_NAME} ${main_files})

find_package(Boost REQUIRED COMPONENTS filesystem)

if(Boost_FOUND)
        message(STATUS "Boost_VERSION: ${Boost_VERSION}")
        message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
        message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
        message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
else()
        message(STATUS "Could not find Boost library")
endif()

# 添加Boost库的头文件路径
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})  # 头文件路径
target_link_directories(${PROJECT_NAME} PUBLIC ${Boost_LIBRARY_DIRS}) # 库文件路径
target_link_libraries(${PROJECT_NAME} PUBLIC Boost::filesystem pthread) # 未添加dl会报错

install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})
