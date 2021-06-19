#ifndef RESULTS_HPP
#define RESULTS_HPP

#include <iostream>

#include "Database.hpp"

struct transaction_t
{
    std::string type = "";
    double closePrice = 0.0;
    size_t closeTime = 0;
};

struct data_t
{
    std::string pair = "";
    std::list<transaction_t> transactions;
};

class Results
{
public:
    Results();
    ~Results();

public:
    int scan();

private:
    void fetchPairs();
    bool transactionsValid(data_t &data);
    int fetchTransactions();
    void computeStats();

private:
    Database _database;
    std::vector<data_t> _pairDataList;
};

#endif // RESULTS_HPP
