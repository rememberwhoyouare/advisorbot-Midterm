#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
    public:
        /** construct, reading a csv data file */
        OrderBook(std::string filename);
        /** return vector of all known products in the dataset */
        std::vector<std::string> getKnownProducts();

    private:
        std::vector<OrderBookEntry> orders;
};