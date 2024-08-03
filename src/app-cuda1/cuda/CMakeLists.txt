cmake_minimum_required(VERSION 3.27)

project(deploy)
enable_language(CUDA)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加nvcc编译选项
# add_definitions("-gencode arch=compute_50,code=sm_50")
set(CMAKE_CUDA_FLAGS "-gencode arch=compute_50,code=sm_50")

# 定义项目版本号宏
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

# 生成版本号字符串
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project version: ${PROJECT_VERSION}")
message(STATUS "Project Dir: ${CMAKE_CURRENT_SOURCE_DIR}")

if(CMAKE_CUDA_COMPILER)
    message(STATUS "Find CUDA !")
else()
    message(FATAL_ERROR "Not found CUDA!")
endif()
 
# 查找CUDAToolkit包
find_package(CUDAToolkit REQUIRED)

if (CUDAToolkit_FOUND)
	message(STATUS "CUDAToolkit_FOUND=${CUDAToolkit_FOUND}")
	message(STATUS "CUDAToolkit_VERSION=${CUDAToolkit_VERSION}" )
	message(STATUS "CUDAToolkit_VERSION_MAJOR=${CUDAToolkit_VERSION_MAJOR}")
	message(STATUS "CUDAToolkit_VERSION_MINOR=${CUDAToolkit_VERSION_MINOR}")
	message(STATUS "CUDAToolkit_VERSION_PATCH=${CUDAToolkit_VERSION_PATCH}")
	message(STATUS "CUDAToolkit_BIN_DIR=${CUDAToolkit_BIN_DIR}")
	message(STATUS "CUDAToolkit_INCLUDE_DIRS=${CUDAToolkit_INCLUDE_DIRS}")
	message(STATUS "CUDAToolkit_LIBRARY_DIR=${CUDAToolkit_LIBRARY_DIR}")
	message(STATUS "CUDAToolkit_LIBRARY_ROOT=${CUDAToolkit_LIBRARY_ROOT}")
	message(STATUS "CUDAToolkit_TARGET_DIR=${CUDAToolkit_TARGET_DIR}")
	message(STATUS "CUDAToolkit_NVCC_EXECUTABLE=${CUDAToolkit_NVCC_EXECUTABLE}")
else()
	message(STATUS "Could not find CUDAToolkit")
endif()

# 将源代码添加到此项目的可执行文件。
# aux_source_directory(. main_files)
file(GLOB main_files ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.cu )

add_library(${PROJECT_NAME}_static STATIC ${main_files})
add_library(${PROJECT_NAME}_shared SHARED ${main_files})

set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.${PROJECT_VERSION}")
set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.${PROJECT_VERSION}")

target_include_directories(${PROJECT_NAME}_static PRIVATE ${CUDAToolkit_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME}_shared PRIVATE ${CUDAToolkit_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}_static CUDA::cudart)
target_link_libraries(${PROJECT_NAME}_shared CUDA::cudart)

install(TARGETS ${PROJECT_NAME}_static ${PROJECT_NAME}_shared
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp"
        PATTERN "CMakeLists.txt" EXCLUDE)
