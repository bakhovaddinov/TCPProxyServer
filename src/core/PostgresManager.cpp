#include "PostgresManager.h"
#include <iostream>

void PostgresManager::initialize(const std::string &connectionString)
{
    connection = PQconnectdb(connectionString.c_str());

    if (PQstatus(connection) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(connection) << std::endl;
        PQfinish(connection);
    } else {
        std::cout << "Connection to database successful!" << std::endl;
    }
}

void PostgresManager::executeQuery(const std::string &query)
{
    PGresult *result = PQexec(connection, query.c_str());

    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        std::cerr << "Query execution failed: " << PQresultErrorMessage(result) << std::endl;
        PQclear(result);
    } else {
        std::cout << "Query executed successfully!" << std::endl;
    }

    PQclear(result);
}

void PostgresManager::closeConnection()
{
    PQfinish(connection);
    std::cout << "Database connection closed." << std::endl;
}