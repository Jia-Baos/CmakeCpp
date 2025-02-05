#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/system/error_code.hpp>

int main(int argc, char* argv[]){
    boost::filesystem::path boost_path = "/dev";

    // in fact, we just need to open the required serial port
    if (boost::filesystem::exists(boost_path) && boost::filesystem::is_directory(boost_path)) {
        for (auto& entry : boost::filesystem::directory_iterator(boost_path)) {
            const auto& file_path = entry.path();
                std::cout << file_path << std::endl;
                std::string serial_port_name = file_path.string();

                if (true/*serial_port_name.find("tty") != std::string::npos*/)
                {
                    // 创建Boost.Asio的IO服务对象
                    boost::asio::io_service io_service;

                    // 创建串口对象
                    boost::asio::serial_port serial_port(io_service, serial_port_name);

                    // 配置串口参数，例如波特率、奇偶校验位等
                    serial_port.set_option(boost::asio::serial_port::baud_rate(115200));
                    serial_port.set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));
                    serial_port.set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));
                    serial_port.set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none));

                    // 写入数据到串口
                    try{
                        boost::system::error_code error;
                        std::string data_to_write = serial_port_name;   // 串口正常则串口模拟器收到控制器内串口的名称
                        boost::asio::write(serial_port, boost::asio::buffer(data_to_write, data_to_write.length()), error);

                        // 检查是否有错误发生
                        if (error) {
                            std::cerr << "Error writing to serial port: " << error.message() << std::endl;
                            return 1;
                        }
                    }
                    catch(const boost::system::system_error &e){
                        std::cout << "error: " << e.what() << std::endl;
                    }

                    std::cout << "Data written successfully!" << std::endl;

                    // "/dev/ttyS31"
                    // terminate called after throwing an instance of 'boost::wrapexcept<boost::system::system_error>'
                    //   what():  open: Input/output error
                    // Aborted (core dumped)
                }
        }
    }
    return 0;
}
