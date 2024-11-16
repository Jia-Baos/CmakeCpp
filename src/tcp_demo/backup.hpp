// #include <boost/asio.hpp>
// #include <boost/bind/bind.hpp>
// #include <iostream>
// #include <thread>

// using namespace boost::asio;
// using namespace boost::asio::ip;
// using namespace std;

// class TcpServer
// {
// public:
//     TcpServer(io_service& io_service, short port)
//         : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
//           socket_(io_service)
//     {
//         start_accept();
//     }

// private:
//     void start_accept()
//     {
//         acceptor_.async_accept(socket_,
//             boost::bind(&TcpServer::handle_accept, this, boost::placeholders::_1));
//     }

//     void handle_accept(const boost::system::error_code& error)
//     {
//         if (!error)
//         {
//             cout << "Client connected!" << endl;
//             start_read();
//         }
//         else
//         {
//             cout << "Error during accept: " << error.message() << endl;
//         }

//         // 继续接受下一个连接
//         start_accept();
//     }

//     void start_read()
//     {
//         socket_.async_read_some(buffer(data_, max_length),
//             boost::bind(&TcpServer::handle_read, this, boost::placeholders::_1, boost::placeholders::_2));
//     }

//     void handle_read(const boost::system::error_code& error, size_t length)
//     {
//         if (!error)
//         {
//             cout << "Received: " << string(data_, length) << endl;
//             start_read();  // 持续读取数据
//         }
//         else
//         {
//             cout << "Error during read: " << error.message() << endl;
//         }
//     }

//     tcp::acceptor acceptor_;
//     tcp::socket socket_;
//     enum { max_length = 1024 };
//     char data_[max_length];
// };

// int main()
// {
//     try
//     {
//         io_service io_service;
//         TcpServer server(io_service, 12345);  // 监听端口12345
//         io_service.run();  // 启动异步操作
//     }
//     catch (const std::exception& e)
//     {
//         cerr << "Exception: " << e.what() << endl;
//     }

//     return 0;
// }


// #include <boost/asio.hpp>
// #include <boost/bind/bind.hpp>
// #include <iostream>
// #include <thread>

// using namespace boost::asio;
// using namespace boost::asio::ip;
// using namespace std;

// class TcpClient
// {
// public:
//     TcpClient(io_service& io_service, const string& host, short port)
//         : socket_(io_service)
//     {
//         tcp::resolver resolver(io_service);
//         tcp::resolver::query query(host, to_string(port));
//         endpoint_iterator_ = resolver.resolve(query);
//         start_connect();
//     }

// private:
//     void start_connect()
//     {
//         async_connect(socket_, endpoint_iterator_,
//             boost::bind(&TcpClient::handle_connect, this, boost::placeholders::_1));
//     }

//     void handle_connect(const boost::system::error_code& error)
//     {
//         if (!error)
//         {
//             cout << "Connected to server!" << endl;
//             start_write();
//         }
//         else
//         {
//             cerr << "Error during connect: " << error.message() << endl;
//         }
//     }

//     void start_write()
//     {
//         string msg = "Hello from client!";
//         async_write(socket_, buffer(msg),
//             boost::bind(&TcpClient::handle_write, this, boost::placeholders::_1, boost::placeholders::_2));
//     }

//     void handle_write(const boost::system::error_code& error, size_t length)
//     {
//         if (!error)
//         {
//             cout << "Message sent to server!" << endl;
//             start_read();
//         }
//         else
//         {
//             cerr << "Error during write: " << error.message() << endl;
//         }
//     }

//     void start_read()
//     {
//         socket_.async_read_some(buffer(data_, max_length),
//             boost::bind(&TcpClient::handle_read, this, boost::placeholders::_1, boost::placeholders::_2));
//     }

//     void handle_read(const boost::system::error_code& error, size_t length)
//     {
//         if (!error)
//         {
//             cout << "Received from server: " << string(data_, length) << endl;
//         }
//         else
//         {
//             cerr << "Error during read: " << error.message() << endl;
//         }
//     }

//     tcp::socket socket_;
//     tcp::resolver::iterator endpoint_iterator_;
//     enum { max_length = 1024 };
//     char data_[max_length];
// };

// int main()
// {
//     try
//     {
//         io_service io_service;
//         TcpClient client(io_service, "localhost", 12345);  // 连接到本地服务端12345端口
//         io_service.run();  // 启动异步操作
//     }
//     catch (const std::exception& e)
//     {
//         cerr << "Exception: " << e.what() << endl;
//     }

//     return 0;
// }
