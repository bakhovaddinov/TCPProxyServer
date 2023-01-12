#pragma once

#include <boost/asio.hpp>

class DatabaseServer
{
  public:
    DatabaseServer(boost::asio::io_service &io_service, short port);

  private:
    void startAccept();
    void startRead();
    void startWrite(const std::string &message);

  private:
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf buffer_;
};
