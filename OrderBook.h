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
        /** return vector of Orders according to send filters */   
        std::vector<OrderBookEntry> getOrders(  OrderBookType type,
                                                std::string product,
                                                std::string timestamp );
        /** return the price of the highest bid in the sent set */
        static double getHighPrice(std::vector<OrderBookEntry>& orders);
        /** return the price of the lowest bid in the sent set */
        static double getLowPrice(std::vector<OrderBookEntry>& orders);
        /** calculate average in the current time step */
        static double calculateAverage(std::vector<OrderBookEntry>& orders);
        /** returns the earliest time in the orderbook */
        std::string getEarliestTime();
        
        /** returns the next time after 
         * the sent time in the orderbook 
         * If there is no next timestamp, wraps around to start
        */
        std::string getNextTime(std::string timestamp);

        /** returns the time before the sent time in the orderbook
         * If there is not previous timestamp, it stops
        */
        std::string getPreviousTime(std::string timestamp);

    private:
        std::vector<OrderBookEntry> orders;
};