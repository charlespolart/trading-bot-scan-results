#include "Results.hpp"

Results::Results() : _database(std::getenv("DATABASE_RESULT_HISTORY_NAME"))
{
}

Results::~Results()
{
}

/* PRIVATE */

void Results::fetchPairs()
{
    const pqxx::result &result = this->_database.query("SELECT DISTINCT pair FROM transactions ORDER BY pair");

    for (int i = 0; i < result.size(); ++i)
    {
        this->_pairDataList.push_back(data_t{result.at(i).front().c_str(), std::list<transaction_t>{}});
    }
}

bool Results::transactionsValid(data_t &data)
{
    std::list<transaction_t>::iterator prevIt;

    if (data.transactions.empty())
        return (false);
    for (std::list<transaction_t>::iterator it = data.transactions.begin(); it != data.transactions.end(); ++it)
    {
        if (it != data.transactions.begin())
        {
            if (it->type == prevIt->type)
                return (false);
        }
        prevIt = it;
    }
    if (data.transactions.front().type == "sell")
        data.transactions.pop_front();
    if (!data.transactions.empty() && data.transactions.back().type == "buy")
        data.transactions.pop_back();
    return (true);
}

int Results::fetchTransactions()
{
    for (size_t i = 0; i < this->_pairDataList.size(); ++i)
    {
        pqxx::stream_from stream = this->_database.queryStream("SELECT type, close_price, close_time FROM transactions WHERE pair='" + this->_pairDataList[i].pair + "' ORDER BY open_time ASC");
        std::tuple<std::string, std::string, size_t> row;

        while (stream >> row)
        {
            std::string type = std::get<0>(row);
            double closePrice = 0.0;
            try
            {
                closePrice = std::stod(std::get<1>(row));
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
            size_t closeTime = std::get<2>(row);

            this->_pairDataList[i].transactions.push_back(transaction_t{type, closePrice, closeTime});
        }
        if (!this->transactionsValid(this->_pairDataList[i]))
        {
            std::cerr << this->_pairDataList[i].pair << ": Transactions invalid" << std::endl;
            return (EXIT_FAILURE);
        }
    }
    return (EXIT_SUCCESS);
}

void Results::computeStats()
{
    for (size_t i = 0; i < this->_pairDataList.size(); ++i)
    {
        std::cout << this->_pairDataList[i].pair << " " << this->_pairDataList[i].transactions.size() << std::endl;
    }
}

/* PUBLIC */

int Results::scan()
{
    if (!this->_database.isOpen())
    {
        std::cerr << "Can't open database" << std::endl;
        return (EXIT_FAILURE);
    }
    this->fetchPairs();
    if (this->_pairDataList.empty())
    {
        std::cerr << "No coins found" << std::endl;
        return (EXIT_FAILURE);
    }
    if (this->fetchTransactions())
        return (EXIT_FAILURE);
    this->computeStats();
    return (EXIT_SUCCESS);
}
