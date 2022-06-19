#include "OrderBook.h"
#include "CSVReader.h"
#include <iostream>
#include <map>

OrderBook::OrderBook(std::string filename) {
    orders = CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts() {
    std::vector<std::string> products;
    std::map<std::string, bool> prodMap;

    for (OrderBookEntry& e : orders) {
        prodMap[e.product] = true;
    }

    for (auto const& e: prodMap) {
        products.push_back(e.first);
    }

    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                                std::string product,
                                                std::string timestamp ) {
    std::vector<OrderBookEntry> orders_sub;
    for (OrderBookEntry& e : orders) {

        if (e.orderType == type && 
            e.product == product && 
            e.timestamp == timestamp) {
                orders_sub.push_back(e);
            } 
        //     else {
        //     std::cout << "OrderBook::someting went wrong" << std::endl;
        //     exit(0);
        // } 
    }
    return orders_sub;
}

std::string OrderBook::getEarliestTime() {
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp) {
    std::string next_timestamp = "";
    for (OrderBookEntry& e : orders) {
        if (e.timestamp > timestamp) {
            next_timestamp = e.timestamp;
            break;
        }
    }
    if (next_timestamp == "") {
        next_timestamp = getEarliestTime();
    }
    return next_timestamp;
}

std::string OrderBook::getPreviousTime(std::string timestamp) {
    std::string previous_timestamp = "";
    for (int i = orders.size() - 1; i >= 0; i--) {
        if (orders[i].timestamp < timestamp) {
            previous_timestamp = orders[i].timestamp;
            break;
        }
    }
    return previous_timestamp;
}
  
double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders) {
    double max = orders[0].price;
    for (OrderBookEntry& e : orders) {
        if (e.price > max) max = e.price;
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders) {
    double min = orders[0].price;
    for (OrderBookEntry& e : orders) {
        if (e.price < min) min = e.price;
    }
    return min;
}

double OrderBook::calculateAverage(std::vector<OrderBookEntry>& orders) {
    double average = 0;
    for (OrderBookEntry& e : orders) {
        average = average + e.price;
    }
    average = average / orders.size();
    return average;
}
