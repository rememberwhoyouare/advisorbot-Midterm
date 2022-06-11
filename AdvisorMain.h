#pragma once
#include <iostream>
#include <string>

class AdvisorMain {
    public:
        AdvisorMain();
        void init();
    private:
        /** list all available commands */
        void help();
        /** output help for the specified command */
        void helpcmd();
        /** list available products */
        void prod();
        /** find minimum bid or ask for product in current time step */
        void min();
        /** find maximum bid or ask for product in current time step */
        void max();
        /** compute average ask or bid for the sent product 
         * over the sent number of time steps */
        void avg();
        /** predict max or min ask or bid for the sent product for the next time step */
        void predict();
        /** state current time in dataset, i.e. which timeframe are we looking at */
        void time();
        /** move to next time step */
        void step();
        /** HERE IMPLEMENT YOUR OWN COMMAND */

        std::string getUserOption();
        void processUserOption(std::string userOption);
};