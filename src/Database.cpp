#include "Database.hpp"

Database::Database(const std::string &name) : _connection("dbname=" + name + " user=" + std::getenv("DATABASE_USER") + " password=" + std::getenv("DATABASE_PASSWORD") + " hostaddr=127.0.0.1"),
                                              _transaction(this->_connection)
{
}

Database::~Database()
{
}

/* PUBLIC */

bool Database::isOpen()
{
    return (this->_connection.is_open());
}

pqxx::result Database::query(const std::string &query)
{
    pqxx::result result = this->_transaction.exec(query);

    return (result);
}

pqxx::stream_from Database::queryStream(const std::string &query)
{
    return (pqxx::stream_from::query(this->_transaction, query));
}
