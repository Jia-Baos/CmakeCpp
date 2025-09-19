#pragma once
#include <iostream>
#include <string>

// 主题接口
class File {
public:
    virtual ~File() = default;
    virtual void Read() = 0; // 读取文件内容
};

// 真实对象：具体的文件类
class RealFile : public File {
private:
    std::string file_name_;

public:
    RealFile(const std::string &name)
        : file_name_(name)
    {
        std::cout << "Loading file: " << file_name_ << std::endl;
    }

    void Read() override
    {
        std::cout << "Reading file: " << file_name_ << std::endl;
    }
};

// 代理对象
class ProxyFile : public File {
private:
    RealFile *real_file_;
    std::string file_name_;

public:
    ProxyFile(const std::string &name)
        : file_name_(name), real_file_(nullptr) {}

    void Read() override
    {
        // 延迟加载
        if (real_file_ == nullptr) {
            real_file_ = new RealFile(file_name_);
        }
        real_file_->Read();
    }

    ~ProxyFile()
    {
        delete real_file_;
    }
};

// 客户端代码
void ProxyTest()
{
    // 使用代理加载文件
    File *file = new ProxyFile("large_file.txt");

    // 文件读取时才真正加载
    file->Read(); // 第一次读取会加载文件
    file->Read(); // 第二次读取直接使用已加载的文件

    delete file;
}
