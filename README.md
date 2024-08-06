# 技术文档

## vscode中cmake插件的文档

[cmake插件链接](https://vector-of-bool.github.io/docs/vscode-cmake-tools/index.html)

## 扫描电脑上所有编译器

点击vscode左下角的工具包设置（cmake配置下），之后再跳出的框中点击扫描工具包，之后就获取电脑上所有的编译工具。

## 编译命令

### Windows

```
cmake -B build -G "MinGW Makefiles"

cmake --build build --config Release --target install
```

[参考链接](https://github.com/Jia-Baos/Notes/blob/master/CMake/cmake-command.md)

### Linux

```
sudo mkdir build && cd build

sudo cmake ..

sudo make

sudo make install
```

## git添加子模块

```
git submodule add https://github.com/google/benchmark.git 3rdparty/benchmark

git submodule add https://github.com/google/googletest.git 3rdparty/googletest
```

若出现错误信息`fatal: 'benchmark' already exists in the index`，则按下面方式删除记录后再重新添加即可。

```
git rm -r --cached 3rdparty/benchmark

git rm -r --cached 3rdparty/googletest
```

## 注意事项

### 事项一

在使用前面给的Linux编译命令后，使用vs-code中的快捷键编译提示没有权限

```
CMake Error: : System Error: Permission denied
```

推测原因为建立文件夹时使用```sudo```权限，使得用快捷键进行编译时没有写入权限，实测删除build文件夹后，重新编译其可

递归修改文件夹的权限目前无法解决上述问题，有待进一步探索（时间：2024-06-09 22：02）

```
sudo chmod -R 777 [Dir]
```

问题定位及解决方案：新建build文件夹及执行cmake命令时，不要使用```sudo```权限。

### 事项二

在安装 CUDA 版本的 Pytorch 后，C++代码工程出现无法找到 CUDA 库的问题，经过定位发现Cmake中缺失了 CUDA 相关的 ```.cmake``` 文件，后重新安装 Cmake 解决问题。后面再次出现上述问题，重装 Cmake 无法解决问题，后指定架构和编译器解决问题。

```
set(CMAKE_CUDA_ARCHITECTURES 50)
set(CMAKE_CUDA_COMPILER /usr/local/cuda-11.8/bin/nvcc)

enable_language(CUDA)   // enable_language()前添加CUDA相关定义
```

[参考链接](https://blog.csdn.net/qq_19449259/article/details/128001426)

[参考链接](https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html#options-for-steering-gpu-code-generation)

### 事项三

在安装CUDA、cuDnn、TensorRT过程中，可能无错误出现，但对于代码工程如 ```TensorRT-build``` ，执行过程中提示函数没有找到，也有人说此问题在于GPU显存不够，后测试多个版本后发现代码工程无问题，现给出目前可正常使用的搭配。

```
cuda_11.8.0_520.61.05_linux.run
cudnn-linux-x86_64-8.6.0.163_cuda11-archive.tar.xz
TensorRT-8.5.3.1.Linux.x86_64-gnu.cuda-11.8.cudnn8.6.tar.gz
```


