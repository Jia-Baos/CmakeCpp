cmake_minimum_required(VERSION 3.27)

project(app-cuda0)
enable_language(CUDA)

# 添加nvcc编译选项
add_definitions("-gencode arch=compute_50,code=sm_50")
# set(CUDA_NVCC_FLAGS "-gencode arch=compute_50,code=sm_50") # 已被弃用

message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Dir: ${CMAKE_CURRENT_SOURCE_DIR}")

# 设置CMake策略以抑制警告
# cmake_policy(SET CMP0146 NEW)
 
# 设置CUDAToolkit路径
# set(CUDAToolkit_ROOT /usr/local/cuda)
# set(CMAKE_PREFIX_PATH ${CUDAToolkit_ROOT})
 
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
add_executable(${PROJECT_NAME} ${main_files})

# 设置目标属性
# target_compile_features()
# target_compile_definitions()
# target_compile_options(${PROJECT_NAME} PUBLIC -fno-elide-constructors)

# 链接库头文件路径
target_include_directories(${PROJECT_NAME} PRIVATE ${CUDAToolkit_INCLUDE_DIRS})

# 链接库文件夹
# 如果动态链接库和静态链接库同名，优先调用静态链接库
target_link_libraries(${PROJECT_NAME} CUDA::cudart)

install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})
