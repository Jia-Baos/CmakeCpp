#include <boost/asio.hpp>
#include <boost/asio/detail/chrono.hpp>
#include <boost/optional.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/bind/bind.hpp>
#include <boost/system/error_code.hpp>

#include <cstddef>
#include <iostream>
#include <string>

class TcpClient {
public:
    TcpClient(const std::string local_name, const std::string remote_name)
        : io_service_(),
          socket_(io_service_),
          deadline_(io_service_),
          local_name_(local_name),
          remote_name_(remote_name) {}

    TcpClient(const std::string &host, const short port, const short timeout, const std::string local_name, const std::string remote_name)
        : io_service_(),
          socket_(io_service_),
          deadline_(io_service_),
          timeout_(timeout),
          local_name_(local_name),
          remote_name_(remote_name)
    {
        boost::asio::ip::tcp::resolver resolver(io_service_);
        boost::asio::ip::tcp::resolver::query query(host, std::to_string(port));
        endpoint_iterator_ = resolver.resolve(query);
        StartConnect();
    }

    ~TcpClient()
    {
        if (this->IsOpen()) {
            try {
                Close();
            }
            catch (const boost::system::system_error &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }

    bool IsOpen() const
    {
        return socket_.is_open();
    }

    void Close()
    {
        if (!this->IsOpen()) {
            return;
        }

        boost::system::error_code endpoint_error;
        std::string local_ip = socket_.local_endpoint(endpoint_error).address().to_string();
        std::string local_port = std::to_string(socket_.local_endpoint(endpoint_error).port());

        std::string remote_ip = socket_.remote_endpoint(endpoint_error).address().to_string();
        std::string remote_port = std::to_string(socket_.remote_endpoint(endpoint_error).port());

        boost::system::error_code shutdown_error;
        socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, shutdown_error);

        boost::system::error_code close_error;
        socket_.close(close_error);
        io_service_.restart(); // 如果在指定的超时时间内没有连接成功，定时器将执行回调函数

        if (endpoint_error) {
            throw boost::system::system_error(endpoint_error,
                                              local_name_ + " --> " + remote_name_ + " connection closure endpoint error");
        } else if (shutdown_error) {
            throw boost::system::system_error(shutdown_error,
                                              local_name_ + " --> " + remote_name_ + " connection closure shutdown error");
        } else if (close_error) {
            throw boost::system::system_error(close_error,
                                              local_name_ + " --> " + remote_name_ + " connection closure close error");
        }
    }

    void StartConnect()
    {
        if (this->IsOpen()) {
            this->Close();
        }

        boost::optional<boost::system::error_code> timer_result;
        deadline_.expires_after(boost::asio::chrono::milliseconds(timeout_));
        deadline_.async_wait([&timer_result](const boost::system::error_code &error) { timer_result.reset(error); });

        boost::optional<boost::system::error_code> conn_result;
        async_connect(socket_, endpoint_iterator_, boost::bind(&TcpClient::HandleConnect, this, conn_result, boost::placeholders::_1));

        io_service_.restart();

        auto flag = io_service_.run_one();
        while (flag) {
            std::cout << "io_service_.run_one()..." << flag << std::endl;
            if (conn_result.has_value()) {
                deadline_.cancel();
                std::cout << "deadline_.cancel()..." << std::endl;
            } else if (timer_result.has_value()) {
                socket_.cancel();
                std::cout << "socket.cancel()..." << std::endl;
            }
            flag = io_service_.run_one();
        }

        if (conn_result.has_value()) {
            boost::system::error_code endpoint_error;
            std::string local_ip = socket_.local_endpoint(endpoint_error).address().to_string();
            std::string local_port = std::to_string(socket_.local_endpoint(endpoint_error).port());

            boost::system::error_code close_error;
            socket_.close(close_error);

            if (endpoint_error) {
                throw boost::system::system_error(endpoint_error,
                                                  local_name_ + " --> " + remote_name_ + " connection closure endpoint_error");
            } else if (close_error) {
                throw boost::system::system_error(close_error,
                                                  local_name_ + " --> " + remote_name_ + " connection closure close_error");
            }

            if (conn_result.value() == boost::asio::error::operation_aborted) {
                throw boost::system::system_error(conn_result.value(),
                                                  local_name_ + " --> " + remote_name_ + " connection timeout");
            } else {
                throw boost::system::system_error(conn_result.value(),
                                                  local_name_ + " --> " + remote_name_ + " connection internal error");
            }
        }
    }

    void StartConnect(const std::string &host, const short port, const short timeout)
    {
        if (this->IsOpen()) {
            this->Close();
        }

        timeout_ = timeout;
        boost::asio::ip::tcp::resolver resolver(io_service_);
        boost::asio::ip::tcp::resolver::query query(host, std::to_string(port));
        endpoint_iterator_ = resolver.resolve(query);

        boost::optional<boost::system::error_code> timer_result;
        deadline_.expires_after(boost::asio::chrono::milliseconds(timeout_));
        deadline_.async_wait([&timer_result](const boost::system::error_code &error) { timer_result.reset(error); });

        boost::optional<boost::system::error_code> conn_result;
        async_connect(socket_, endpoint_iterator_, boost::bind(&TcpClient::HandleConnect, this, conn_result, boost::placeholders::_1));

        io_service_.restart();
        while (io_service_.run_one()) {
            if (conn_result.has_value()) {
                deadline_.cancel();
            } else if (timer_result.has_value()) {
                socket_.cancel();
            }
        }

        if (conn_result.has_value()) {
            boost::system::error_code endpoint_error;
            std::string local_ip = socket_.local_endpoint(endpoint_error).address().to_string();
            std::string local_port = std::to_string(socket_.local_endpoint(endpoint_error).port());

            boost::system::error_code close_error;
            socket_.close(close_error);

            if (endpoint_error) {
                throw boost::system::system_error(endpoint_error,
                                                  local_name_ + " --> " + remote_name_ + " connection closure endpoint_error");
            } else if (close_error) {
                throw boost::system::system_error(close_error,
                                                  local_name_ + " --> " + remote_name_ + " connection closure close_error");
            }

            if (conn_result.value() == boost::asio::error::operation_aborted) {
                throw boost::system::system_error(conn_result.value(),
                                                  local_name_ + " --> " + remote_name_ + " connection timeout");
            } else {
                throw boost::system::system_error(conn_result.value(),
                                                  local_name_ + " --> " + remote_name_ + " connection internal error");
            }
        }
    }

    void HandleConnect(boost::optional<boost::system::error_code> &conn_result, const boost::system::error_code &error)
    {
        conn_result.reset(error);
        try {
            if (!error) {
                std::cout << "Connected to server!" << std::endl;
            } else {
                std::cerr << "Error during connect: " << error.message() << std::endl;
                this->StartConnect();
            }
        }
        catch (const boost::system::system_error &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void SetKeepAliveParam(bool on)
    {
        boost::asio::socket_base::keep_alive keep_alive_option(on);
        boost::asio::socket_base::keep_alive error_option;
        socket_.set_option(keep_alive_option);
        socket_.get_option(error_option);

        if (error_option.value()) {
            std::cout << "Keep-alive is enabled." << std::endl;
        } else {
            std::cout << "Keep-alive is disabled." << std::endl;
        }
    }

    bool StartWrite(const std::string &msg, const short timeout)
    {
        std::cout << "clint start write..." << std::endl;

        boost::optional<boost::system::error_code> timer_result;
        deadline_.expires_after(boost::asio::chrono::milliseconds(timeout));
        deadline_.async_wait([&timer_result](const boost::system::error_code &error) { timer_result.reset(error); });

        boost::optional<boost::system::error_code> write_result;
        async_write(socket_, boost::asio::buffer(msg.c_str(), msg.size()), boost::bind(&TcpClient::HandleWrite, this, write_result, boost::placeholders::_1));

        io_service_.restart();
        while (io_service_.run_one()) {
            if (write_result.has_value()) {
                deadline_.cancel();
            } else if (timer_result.has_value()) {
                socket_.cancel();
            }
        }

        if (write_result.has_value()) {
            boost::system::error_code endpoint_error;
            std::string local_ip = socket_.local_endpoint(endpoint_error).address().to_string();
            std::string local_port = std::to_string(socket_.local_endpoint(endpoint_error).port());

            boost::system::error_code close_error;
            socket_.close(close_error);

            if (endpoint_error) {
                throw boost::system::system_error(endpoint_error,
                                                  local_name_ + " --> " + remote_name_ + " connection closure endpoint_error");
            } else if (close_error) {
                throw boost::system::system_error(close_error,
                                                  local_name_ + " --> " + remote_name_ + " connection closure close_error");
            }

            if (write_result.value() == boost::asio::error::operation_aborted) {
                throw boost::system::system_error(write_result.value(),
                                                  local_name_ + " --> " + remote_name_ + " connection timeout");
            } else {
                throw boost::system::system_error(write_result.value(),
                                                  local_name_ + " --> " + remote_name_ + " connection internal error");
            }
        }

        if (!write_result.has_value()) {
            return true;
        } else {
            return false;
        }
    }

    void HandleWrite(boost::optional<boost::system::error_code> &write_result, const boost::system::error_code &error)
    {
        write_result.reset(error);
        if (!error) {
            std::cout << "Message sent to server!" << std::endl;
        } else {
            std::cerr << "Error during write: " << error.message() << std::endl;
        }
    }

    bool StartRead(std::string &msg, const short timeout)
    {
        std::cout << "clint start read..." << std::endl;

        boost::optional<boost::system::error_code> timer_result;
        deadline_.expires_after(boost::asio::chrono::milliseconds(timeout));
        deadline_.async_wait([&timer_result](const boost::system::error_code &error) { timer_result.reset(error); });

        boost::optional<boost::system::error_code> read_result;

        size_t msg_length{};
        socket_.async_read_some(
            boost::asio::buffer(data_, kMaxLength),
            boost::bind(&TcpClient::HandleRead, this, read_result, msg_length, boost::placeholders::_1, boost::placeholders::_2));

        io_service_.restart();
        while (io_service_.run_one()) {
            if (read_result.has_value()) {
                deadline_.cancel();
                msg = std::string(data_, msg_length);
            } else if (timer_result.has_value()) {
                socket_.cancel();
            }
        }

        if (read_result.has_value()) {
            boost::system::error_code endpoint_error;
            std::string local_ip = socket_.local_endpoint(endpoint_error).address().to_string();
            std::string local_port = std::to_string(socket_.local_endpoint(endpoint_error).port());

            boost::system::error_code close_error;
            socket_.close(close_error);

            if (endpoint_error) {
                throw boost::system::system_error(endpoint_error,
                                                  local_name_ + " --> " + remote_name_ + " connection closure endpoint_error");
            } else if (close_error) {
                throw boost::system::system_error(close_error,
                                                  local_name_ + " --> " + remote_name_ + " connection closure close_error");
            }

            if (read_result.value() == boost::asio::error::operation_aborted) {
                throw boost::system::system_error(read_result.value(),
                                                  local_name_ + " --> " + remote_name_ + " connection timeout");
            } else {
                throw boost::system::system_error(read_result.value(),
                                                  local_name_ + " --> " + remote_name_ + " connection internal error");
            }
        }

        if (!read_result.has_value()) {
            return true;
        } else {
            return false;
        }
    }

    void HandleRead(boost::optional<boost::system::error_code> &read_result, size_t &msg_length, const boost::system::error_code &error, const size_t length)
    {
        read_result.reset(error);
        if (!error) {
            std::cout << "Received from server: " << std::string(data_, length) << std::endl;
            msg_length = length;
        } else {
            std::cerr << "Error during read: " << error.message() << std::endl;
        }
    }

private:
    boost::asio::io_service io_service_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::steady_timer deadline_;
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator_;

    short timeout_;
    std::string local_name_;
    std::string remote_name_;

    enum { kMaxLength = 1024 };
    char data_[kMaxLength];
};

int main()
{
    try {
        TcpClient client("localhost", 12345, 2000, "local", "remote"); // 连接到本地服务端12345端口
        while (true) {
            auto write_res = client.StartWrite("hello world", 200);
            if (write_res) {
                std::cout << "client, write message successed." << std::endl;

                std::string msg{};
                auto read_res = client.StartRead(msg, 200);
                if (read_res) {
                    std::cout << "client, receive message successed." << std::endl;
                }
            }
        }
    }
    catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
