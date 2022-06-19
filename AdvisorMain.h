#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "OrderBook.h"

class AdvisorMain {
    public:
        AdvisorMain();
        void init();
    private:
        /** list all available commands */
        void help();
        /** output help for the specified command */
        void helpcmd(std::string cmd);
        /** list available products */
        void prod();
        /** find minimum bid or ask for product in current time step */
        double min(std::vector<std::string> tokens);
        /** find maximum bid or ask for product in current time step */
        double max(std::vector<std::string> tokens);
        /** compute average ask or bid for the sent product 
         * over the sent number of time steps */
        void avg(std::vector<std::string> tokens);
        /** predict max or min ask or bid for the sent product for the next time step */
        void predict(std::vector<std::string> tokens);
        /** state current time in dataset, i.e. which timeframe are we looking at */
        void time();
        /** move to next time step */
        void step();
        /** HERE IMPLEMENT YOUR OWN COMMAND */

        std::string getUserOption();
        void processUserOption(std::string userOption);

        std::string currentTime;
        // placeholder for step count
        int stepCount = 0;
        OrderBook orderBook{"20200601.csv"};
};