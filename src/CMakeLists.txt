cmake_minimum_required(VERSION 3.27)

# 进入三方库文件夹
add_subdirectory(MiniCircle)

# 进入执行文件文件夹
add_subdirectory(app0)
# add_subdirectory(app1)
# add_subdirectory(CmakeEigen)
# add_subdirectory(CmakeMat)
# add_subdirectory(DBSCAN)
# add_subdirectory(LeetCode)

add_subdirectory(app-cuda0)
add_subdirectory(app-cuda1)
add_subdirectory(TensorRT-build)
add_subdirectory(TensorRT-runtime)