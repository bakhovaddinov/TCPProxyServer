#include "DatabaseServer.h"
#include <boost/asio.hpp>
#include <iostream>
#include <thread>

using namespace boost::asio;
DatabaseServer::DatabaseServer(io_service &io_service, short port)
    : acceptor_(io_service, ip::tcp::endpoint(ip::tcp::v4(), port))
    , socket_(io_service)
{
    startAccept();
}

void DatabaseServer::startAccept()
{
    if (!acceptor_.is_open()) {
        return;
    }

    acceptor_.async_accept(socket_, [this](const boost::system::error_code &error) {
        if (!error) {
            std::cout << "Client connected" << std::endl;
            startRead();
        } else {
            std::cerr << "Error accepting connection: " << error.message() << std::endl;
        }
        acceptor_.close();
        startAccept();
    });
}

void DatabaseServer::startRead()
{
    async_read_until(socket_, buffer_, '\n',
                     [this](const boost::system::error_code &error, std::size_t /*bytes_transferred*/) {
                         if (!error) {
                             std::istream is(&buffer_);
                             std::string message;
                             std::getline(is, message);
                             std::cout << "Received message: " << message << std::endl;

                             startWrite(message);
                         } else {
                             std::cerr << "Error reading from client: " << error.message() << std::endl;
                             socket_.close();
                         }
                     });
}

void DatabaseServer::startWrite(const std::string &message)
{
    async_write(socket_, buffer(message + "\n"),
                [this](const boost::system::error_code &error, std::size_t /*bytes_transferred*/) {
                    if (!error) {
                        std::cout << "Sent message back to client" << std::endl;
                        startRead();
                    } else {
                        std::cerr << "Error writing to client: " << error.message() << std::endl;
                        socket_.close();
                    }
                });
}