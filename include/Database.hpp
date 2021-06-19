#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <pqxx/pqxx>

class Database
{
public:
    Database() = delete;
    Database(const std::string &name);
    ~Database();

public:
    bool isOpen();
    pqxx::result query(const std::string &query);
    pqxx::stream_from queryStream(const std::string &query);

private:
    pqxx::connection _connection;
    pqxx::transaction<> _transaction;
};

#endif // DATABASE_HPP
