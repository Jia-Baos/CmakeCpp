// #include <boost/asio.hpp>
// #include <boost/asio/detail/chrono.hpp>
// #include <boost/optional.hpp>
// #include <boost/asio/io_service.hpp>
// #include <boost/asio/steady_timer.hpp>
// #include <boost/bind/bind.hpp>
// #include <boost/system/error_code.hpp>

// #include <cstddef>
// #include <iostream>
// #include <string>

// class TcpServer {
// public:
//     TcpServer(const std::string &local_name, const std::string &remote_name)
//         : io_service_(),
//           socket_(io_service_),
//           acceptor_(io_service_),
//           deadline_(io_service_),
//           local_name_(local_name),
//           remote_name_(remote_name) {}

//     TcpServer(const std::string &host, const short port, const short timeout, const std::string &local_name, const std::string &remote_name)
//         : io_service_(),
//           socket_(io_service_),
//           acceptor_(io_service_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
//           deadline_(io_service_),
//           timeout_(timeout),
//           local_name_(local_name),
//           remote_name_(remote_name)
//     {
//         boost::asio::ip::tcp::resolver resolver(io_service_);
//         boost::asio::ip::tcp::resolver::query query(host, std::to_string(port));
//         endpoint_iterator_ = resolver.resolve(query);

//         // acceptor_ = boost::asio::ip::tcp::acceptor(io_service_, *endpoint_iterator_);
//         // acceptor_.open(boost::asio::ip::tcp::v4());
//         // acceptor_.bind(*endpoint_iterator_);

//         StartAccept();
//     }

//     ~TcpServer()
//     {
//         if (this->IsOpen()) {
//             try {
//                 Close();
//             }
//             catch (const boost::system::system_error &e) {
//                 std::cerr << e.what() << std::endl;
//             }
//         }
//     }

//     bool IsOpen() const
//     {
//         return socket_.is_open();
//     }

//     void Close()
//     {
//         if (!this->IsOpen()) {
//             return;
//         }

//         boost::system::error_code endpoint_error;
//         std::string local_ip = socket_.local_endpoint(endpoint_error).address().to_string();
//         std::string local_port = std::to_string(socket_.local_endpoint(endpoint_error).port());

//         std::string remote_ip = socket_.remote_endpoint(endpoint_error).address().to_string();
//         std::string remote_port = std::to_string(socket_.remote_endpoint(endpoint_error).port());

//         boost::system::error_code shutdown_error;
//         socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, shutdown_error);

//         boost::system::error_code close_error;
//         socket_.close(close_error);
//         io_service_.restart(); // 如果在指定的超时时间内没有连接成功，定时器将执行回调函数

//         if (endpoint_error) {
//             throw boost::system::system_error(endpoint_error,
//                                               local_name_ + " --> " + remote_name_ + " connection closure endpoint error");
//         } else if (shutdown_error) {
//             throw boost::system::system_error(shutdown_error,
//                                               local_name_ + " --> " + remote_name_ + " connection closure shutdown error");
//         } else if (close_error) {
//             throw boost::system::system_error(close_error,
//                                               local_name_ + " --> " + remote_name_ + " connection closure close error");
//         }
//     }

//     void StartAccept()
//     {
//         if (this->IsOpen()) {
//             this->Close();
//         }

//         boost::optional<boost::system::error_code> timer_result;
//         deadline_.expires_after(boost::asio::chrono::milliseconds(timeout_));
//         deadline_.async_wait([&timer_result](const boost::system::error_code &error) { timer_result.reset(error); });

//         boost::optional<boost::system::error_code> accept_result;
//         acceptor_.async_accept(socket_,
//                                boost::bind(&TcpServer::HandleAccept, this, accept_result, boost::placeholders::_1));

//         io_service_.restart();
//         while (io_service_.run_one()) {
//             if (accept_result.has_value()) {
//                 deadline_.cancel();
//             } else if (timer_result.has_value()) {
//                 acceptor_.cancel();
//             }
//         }

//         if (accept_result.has_value()) {
//             boost::system::error_code endpoint_error;
//             std::string local_ip = socket_.local_endpoint(endpoint_error).address().to_string();
//             std::string local_port = std::to_string(socket_.local_endpoint(endpoint_error).port());

//             boost::system::error_code close_error;
//             socket_.close(close_error);

//             if (endpoint_error) {
//                 throw boost::system::system_error(endpoint_error,
//                                                   local_name_ + " --> " + remote_name_ + " connection closure endpoint_error");
//             } else if (close_error) {
//                 throw boost::system::system_error(close_error,
//                                                   local_name_ + " --> " + remote_name_ + " connection closure close_error");
//             }

//             if (accept_result.value() == boost::asio::error::operation_aborted) {
//                 throw boost::system::system_error(accept_result.value(),
//                                                   local_name_ + " --> " + remote_name_ + " connection timeout");
//             } else {
//                 throw boost::system::system_error(accept_result.value(),
//                                                   local_name_ + " --> " + remote_name_ + " connection internal error");
//             }
//         }
//     }

//     void HandleAccept(boost::optional<boost::system::error_code> &accept_result, const boost::system::error_code &error)
//     {
//         accept_result.reset(error);
//         if (!error) {
//             std::cout << "Client connected!" << std::endl;

//             auto read_res = this->StartRead(); // 处理客户端请求并返回响应
//             if (read_res) {
//                 std::cout << "server, read message successed." << std::endl;
//             }

//         } else {
//             std::cout << "Error during accept: " << error.message() << std::endl;
//             // 继续接受下一个连接
//             StartAccept();
//         }
//     }

//     bool StartWrite(const std::string &msg, const short timeout)
//     {
//         std::cout << "server start write..." << std::endl;

//         boost::optional<boost::system::error_code> timer_result;
//         deadline_.expires_after(boost::asio::chrono::milliseconds(timeout));
//         deadline_.async_wait([&timer_result](const boost::system::error_code &error) { timer_result.reset(error); });

//         boost::optional<boost::system::error_code> write_result;
//         async_write(socket_, boost::asio::buffer(msg.c_str(), msg.size()), boost::bind(&TcpServer::HandleWrite, this, write_result, boost::placeholders::_1));

//         io_service_.restart();
//         while (io_service_.run_one()) {
//             if (write_result.has_value()) {
//                 deadline_.cancel();
//             } else if (timer_result.has_value()) {
//                 socket_.cancel();
//             }
//         }

//         if (write_result.has_value()) {
//             boost::system::error_code endpoint_error;
//             std::string local_ip = socket_.local_endpoint(endpoint_error).address().to_string();
//             std::string local_port = std::to_string(socket_.local_endpoint(endpoint_error).port());

//             boost::system::error_code close_error;
//             socket_.close(close_error);

//             if (endpoint_error) {
//                 throw boost::system::system_error(endpoint_error,
//                                                   local_name_ + " --> " + remote_name_ + " connection closure endpoint_error");
//             } else if (close_error) {
//                 throw boost::system::system_error(close_error,
//                                                   local_name_ + " --> " + remote_name_ + " connection closure close_error");
//             }

//             if (write_result.value() == boost::asio::error::operation_aborted) {
//                 throw boost::system::system_error(write_result.value(),
//                                                   local_name_ + " --> " + remote_name_ + " connection timeout");
//             } else {
//                 throw boost::system::system_error(write_result.value(),
//                                                   local_name_ + " --> " + remote_name_ + " connection internal error");
//             }
//         }

//         if (!write_result.has_value()) {
//             return true;
//         } else {
//             return false;
//         }
//     }

//     void HandleWrite(boost::optional<boost::system::error_code> &write_result, const boost::system::error_code &error)
//     {
//         write_result.reset(error);
//         if (!error) {
//             std::cout << "Message sent to client!" << std::endl;

//             auto read_res = this->StartRead(); // 处理客户端请求并返回响应
//         } else {
//             std::cerr << "Error during write: " << error.message() << std::endl;
//         }
//     }

//     bool StartRead()
//     {
//         std::cout << "server start read..." << std::endl;

//         // 检查套接字是否仍然有效
//         if (!this->IsOpen()) {
//             std::cout << "Socket is not open. Cannot start reading." << std::endl;
//             return false;
//         }

//         boost::optional<boost::system::error_code> timer_result;
//         deadline_.expires_after(boost::asio::chrono::milliseconds(timeout_));
//         deadline_.async_wait([&timer_result](const boost::system::error_code &error) { timer_result.reset(error); });

//         boost::optional<boost::system::error_code> read_result;

//         socket_.async_read_some(
//             boost::asio::buffer(data_, kMaxLength),
//             boost::bind(&TcpServer::HandleRead, this, read_result, boost::placeholders::_1, boost::placeholders::_2));

//         io_service_.restart();
//         while (io_service_.run_one()) {
//             if (read_result.has_value()) {
//                 deadline_.cancel();
//             } else if (timer_result.has_value()) {
//                 acceptor_.cancel();
//             }
//         }

//         if (read_result.has_value()) {
//             boost::system::error_code endpoint_error;
//             std::string local_ip = socket_.local_endpoint(endpoint_error).address().to_string();
//             std::string local_port = std::to_string(socket_.local_endpoint(endpoint_error).port());

//             boost::system::error_code close_error;
//             socket_.close(close_error);

//             if (endpoint_error) {
//                 throw boost::system::system_error(endpoint_error,
//                                                   local_name_ + " --> " + remote_name_ + " connection closure endpoint_error");
//             } else if (close_error) {
//                 throw boost::system::system_error(close_error,
//                                                   local_name_ + " --> " + remote_name_ + " connection closure close_error");
//             }

//             if (read_result.value() == boost::asio::error::operation_aborted) {
//                 throw boost::system::system_error(read_result.value(),
//                                                   local_name_ + " --> " + remote_name_ + " connection timeout");
//             } else {
//                 throw boost::system::system_error(read_result.value(),
//                                                   local_name_ + " --> " + remote_name_ + " connection internal error");
//             }
//         }

//         if (!read_result.has_value()) {
//             return true;
//         } else {
//             return false;
//         }
//     }

//     void HandleRead(boost::optional<boost::system::error_code> &read_result, const boost::system::error_code &error, const size_t length)
//     {
//         read_result.reset(error);
//         if (!error) {
//             std::cout << "Received: " << std::string(data_, length) << std::endl;

//             auto write_res = this->StartWrite("hello world too", 200);
//         } else if (error == boost::asio::error::operation_aborted) {
//             std::cout << "Error during read: Operation canceled. Waiting for new connection." << std::endl;
//             // 不要立即重新启动读取操作，等待新的连接
//             StartAccept();
//         } else if (error == boost::asio::error::eof) {
//             std::cout << "End of file. Client has closed the connection." << std::endl;
//             // 客户端已经关闭连接，不重新启动读取操作
//             StartAccept();
//         } else {
//             std::cout << "Error during read: " << error.message() << std::endl;
//         }
//     }

// private:
//     boost::asio::io_service io_service_;
//     boost::asio::ip::tcp::socket socket_;
//     boost::asio::ip::tcp::acceptor acceptor_;

//     boost::asio::steady_timer deadline_;
//     boost::asio::ip::tcp::resolver::iterator endpoint_iterator_;

//     short timeout_;
//     std::string local_name_;
//     std::string remote_name_;

//     enum { kMaxLength = 1024 };
//     char data_[kMaxLength];
// };

// int main()
// {
//     try {
//         TcpServer server("localhost", 12345, 3000, "local", "remote"); // 连接到本地服务端12345端口
//         server.StartRead();
//     }
//     catch (const std::exception &e) {
//         std::cerr << "Exception: " << e.what() << std::endl;
//     }

//     return 0;
// }
