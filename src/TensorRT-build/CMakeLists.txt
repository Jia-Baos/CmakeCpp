cmake_minimum_required(VERSION 3.27)

project(TensorRT-build)

set(CMAKE_CUDA_ARCHITECTURES 86)
set(CMAKE_CUDA_COMPILER /usr/local/cuda-12.6/bin/nvcc)

enable_language(CUDA)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加nvcc编译选项
# add_definitions("-gencode arch=compute_50,code=sm_50")
# set(CMAKE_CUDA_FLAGS "-gencode arch=compute_50,code=sm_50") # 根据您的 GPU 架构调整

message(STATUS "Project Name: ${PROJECT_NAME}")
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

# TensorRT
set(TENSORRT_ROOT "/usr/local/TensorRT-10.12.0.36")

find_path(TENSORRT_INCLUDE_DIR NvInfer.h
        HINTS ${TENSORRT_ROOT} PATH_SUFFIXES include/)
message(STATUS "Found TensorRT headers at ${TENSORRT_INCLUDE_DIR}")
find_library(TENSORRT_LIBRARY_INFER nvinfer
        HINTS ${TENSORRT_ROOT} ${TENSORRT_BUILD} ${CUDA_TOOLKIT_ROOT_DIR}
        PATH_SUFFIXES lib lib64 lib/x64)
find_library(TENSORRT_LIBRARY_ONNXPARSER nvonnxparser
        HINTS  ${TENSORRT_ROOT} ${TENSORRT_BUILD} ${CUDA_TOOLKIT_ROOT_DIR}
        PATH_SUFFIXES lib lib64 lib/x64)
find_library(TENSORRT_LIBRARY_PLUGIN nvinfer_plugin
        HINTS  ${TENSORRT_ROOT} ${TENSORRT_BUILD} ${CUDA_TOOLKIT_ROOT_DIR}
        PATH_SUFFIXES lib lib64 lib/x64)
set(TENSORRT_LIBRARY ${TENSORRT_LIBRARY_INFER} ${TENSORRT_LIBRARY_ONNXPARSER} ${TENSORRT_LIBRARY_PLUGIN})
message(STATUS "Find TensorRT libs: ${TENSORRT_LIBRARY}")

# 将源代码添加到此项目的可执行文件。
# aux_source_directory(. main_files)
file(GLOB main_files ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.cu )
add_executable(${PROJECT_NAME} ${main_files})

# 链接库头文件路径
target_include_directories(${PROJECT_NAME} PRIVATE ${CUDAToolkit_INCLUDE_DIRS} ${TENSORRT_INCLUDE_DIR})

# 链接库文件夹
target_link_directories(${PROJECT_NAME} PRIVATE ${TensorRT_DIR}/lib)

# 如果动态链接库和静态链接库同名，优先调用静态链接库
target_link_libraries(${PROJECT_NAME} PRIVATE CUDA::cudart ${TENSORRT_LIBRARY})

install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)