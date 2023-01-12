#pragma once

#include <postgresql/libpq-fe.h>
#include <string>

class PostgresManager
{
  public:
    void initialize(const std::string &connectionString);
    void executeQuery(const std::string &query);
    void closeConnection();

  private:
    PGconn *connection;
};
