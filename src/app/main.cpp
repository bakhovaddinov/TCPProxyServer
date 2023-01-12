#include "../core/DatabaseServer.h"
#include "../core/PostgresManager.h"

#include <boost/asio.hpp>
#include <iostream>

int main()
{
    try {
        boost::asio::io_service io_service;
        DatabaseServer server(io_service, 12345);

        boost::asio::ip::tcp::socket client_socket(io_service);
        client_socket.connect(
            boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 12345));

        std::string message_to_send = "Hello, server!";
        boost::asio::write(client_socket, boost::asio::buffer(message_to_send + "\n"));

        // Initialize PostgresManager and execute a query
        PostgresManager postgresManager;
        postgresManager.initialize("postgresql://myuser:mypassword@localhost:5432/mydatabase");
        postgresManager.executeQuery("SELECT version();");

        // Close the Postgres connection
        postgresManager.closeConnection();

        // Wait for a while to receive the echoed message
        std::this_thread::sleep_for(std::chrono::seconds(1));

        io_service.run(); // Run the server

    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
