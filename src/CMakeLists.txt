cmake_minimum_required(VERSION 3.27)

# 进入三方库文件夹
add_subdirectory(MiniCircle)

# 进入执行文件文件夹
add_subdirectory(mini_circle_demo)

add_subdirectory(demo)
# add_subdirectory(fmt_demo)
# add_subdirectory(spdlog_demo)
# add_subdirectory(eigen_demo)
# add_subdirectory(rangeV3_demo)
# add_subdirectory(tcp_demo)

add_subdirectory(serial_tools)

# add_subdirectory(app)
# add_subdirectory(DBSCAN)
# add_subdirectory(LeetCode)

# add_subdirectory(app-cuda0)
# add_subdirectory(app-cuda1)
# add_subdirectory(TensorRT-build)
# add_subdirectory(TensorRT-runtime)
