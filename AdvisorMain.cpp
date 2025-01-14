#include "AdvisorMain.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "CSVReader.h"
#include "OrderBookEntry.h"

AdvisorMain::AdvisorMain() {

}

void AdvisorMain::init() {
    std::string input;
    std::cout << "Command 'help' to list all available commands." << std::endl;
    currentTime = orderBook.getEarliestTime();

    // prompt user for command input
    while(true) {
        input = getUserOption();
        processUserOption(input);
    }
}

/** list all available commands */
void AdvisorMain::help() {
    std::cout << "The available commands are: "
    "\n help"
    "\n help cmd"
    "\n prod"
    "\n min"
    "\n max"
    "\n avg"
    "\n predict"
    "\n time"
    "\n step"
    "\n log"
    "\n exit \n"
    << std::endl;

    log.push_back("help");
}
/** output help for the specified command */
void AdvisorMain::helpcmd(std::string cmd) {
    if (cmd.compare("prod") == 0) {
        std::cout << "list available products" << std::endl;
        std::cout << "\n" << std::endl;
        log.push_back("help prod");

    }
    else if (cmd.compare("min") == 0) {
        std::cout << "min ETH/BTC ask -> min ETH/BTC ask in the current time step" << std::endl;
        std::cout << "\n" << std::endl;
        log.push_back("help min");

    }
    else if (cmd.compare("max") == 0) {
        std::cout << "max ETH/BTC ask -> max ETH/BTC ask in the current time step" << std::endl;
        std::cout << "\n" << std::endl;
        log.push_back("help max");

    }
    else if (cmd.compare("avg") == 0) {
        std::cout << "avg ETH/BTC bid 10 -> average ETH/BTC bid over last 10 timesteps" << std::endl;
        std::cout << "\n" << std::endl;
        log.push_back("help avg");

    }
    else if (cmd.compare("predict") == 0) {
        std::cout << "predict max ETH/BTC bid ->  The average ETH/BTC ask price over all previous timesteps" << std::endl;
        std::cout << "\n" << std::endl;
        log.push_back("help predict");
    }
    else if (cmd.compare("time") == 0) {
        std::cout << "state current time in dataset, i.e. which timeframe are we looking at" << std::endl;
        std::cout << "\n" << std::endl;
        log.push_back("help time");
    }
    else if (cmd.compare("step") == 0) {
        std::cout << "move to next time step" << std::endl;
        std::cout << "\n" << std::endl;
        log.push_back("help step");
    }
    else if (cmd.compare("log") == 0) {
        std::cout << "print out all entered commands" << std::endl;
        std::cout << "\n" << std::endl;
        log.push_back("help log");
    }
    else if (cmd.compare("exit") == 0) {
        std::cout << "exit the program" << std::endl;
        std::cout << "\n" << std::endl;
        log.push_back("help exit");
    }
    // if command is not in the list
    else {
        std::cout << "wrong command, type 'help' to see the list of available commands." << std::endl;
        std::cout << "\n" << std::endl;
    }

}

/** list available products */
void AdvisorMain::prod() {
    std::cout << "Avaliable products in the current timestamp are: " << std::endl;
    for (std::string const& product : orderBook.getKnownProducts()) {
        std::cout << product << std::endl;
    }
    // print new line  
    std::cout << "\n" << std::endl;

    log.push_back("prod");
}

/** find minimum bid or ask for product in current time step */
double AdvisorMain::min(std::vector<std::string> tokens) {

    /*

    Fix the segmentation fault when entering wrong orderbooktype!!!

    */

    std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(tokens[2]), 
                                                                tokens[1], 
                                                                currentTime);
    
    // check for correct currency pair
    std::vector<std::string> prod = orderBook.getKnownProducts();
    if (std::find(prod.begin(), prod.end(), tokens[1]) == prod.end() 
        || entries[0].orderType == OrderBookType::unknown) {
        std::cout << "Wrong product" << std::endl;
        exit(0);
    }

    log.push_back("min");
    return orderBook.getLowPrice(entries);
}

/** find maximum bid or ask for product in current time step */
double AdvisorMain::max(std::vector<std::string> tokens) {

    std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(tokens[2]), 
                                                                tokens[1], 
                                                                currentTime);
    
    // check for correct currency pair
    std::vector<std::string> prod = orderBook.getKnownProducts();
    if (std::find(prod.begin(), prod.end(), tokens[1]) == prod.end() 
        || entries[0].orderType == OrderBookType::unknown) {
        std::cout << "Wrong product" << std::endl;
        exit(0);
    } 

    log.push_back("max");
    return orderBook.getHighPrice(entries);
}


/** compute average ask or bid for the sent product 
 * over the sent number of time steps */
void AdvisorMain::avg(std::vector<std::string> tokens) {

    // check for correct currency pair
    std::vector<std::string> prod = orderBook.getKnownProducts();
    if (std::find(prod.begin(), prod.end(), tokens[1]) == prod.end()) {
        std::cout << "Wrong product" << std::endl;
        exit(0);
    } 

    int steps;
    try {
        steps = stoi(tokens[3]);
        } catch (const std::exception& e) {
            std::cout << "Bad input!" << std::endl;
            exit(0);
        }
    std::string timeTemp = currentTime;
    double average = 0;

    // check how many steps back are available
    if (steps > stepCount) {
        steps = stepCount;
    }

    // iterate throught entries and calculate average
    for (int i = 0; i < steps; i++) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(tokens[2]), 
                                                                    tokens[1], 
                                                                    timeTemp);
        average = average + orderBook.calculateAverage(entries);
        timeTemp = orderBook.getPreviousTime(timeTemp);
    }
    average = average / steps;
    std::cout << "the average " << tokens[1] << " " << tokens[2] << " price over the last " 
                << tokens[3] << " timesteps was " << average << std::endl;
    std::cout << "\n" << std::endl;

    log.push_back("avg");
}

/** predict max or min ask or bid for the sent product for the next time step */
void AdvisorMain::predict(std::vector<std::string> tokens) {

    // check for correct currency pair
    std::vector<std::string> prod = orderBook.getKnownProducts();
    if (std::find(prod.begin(), prod.end(), tokens[2]) == prod.end()) {
        std::cout << "Bad input!" << std::endl;
        exit(0);
    } 

    double average = 0;
    std::string timeTemp = currentTime;

    // slice tokens vector, so it is suitable for min/max functions
    std::vector<std::string> newTokens = std::vector<std::string>(tokens.begin() + 1, tokens.end());
    // compute the average
    for (int i = 0; i < stepCount; i++) {
        if (tokens[1] == "max") {
            average = average + max(newTokens);
        } else if (tokens[1] == "min") {
            average = average + min(newTokens);
        }
        timeTemp = orderBook.getPreviousTime(timeTemp);
    }
    average = average / stepCount;
    std::cout << "predict " << tokens[1] << " for " << tokens[2] << " is " << average << std::endl;
    std::cout << "\n" << std::endl;

    log.push_back("predict");
}

/** state current time in dataset, i.e. which timeframe are we looking at */
void AdvisorMain::time() {
    // trim currentTime string and print it
    std::vector<std::string> time = CSVReader::tokenise(currentTime,'.');
    std::cout << time[0] << std::endl;
    std::cout << "\n" << std::endl;
    log.push_back("time");
}

/** move to next time step */
void AdvisorMain::step() {
    currentTime = orderBook.getNextTime(currentTime);
    stepCount += 1;
     // trim currentTime string and print it
    std::vector<std::string> time = CSVReader::tokenise(currentTime,'.');
    std::cout << "now at " << time[0] << std::endl;
    std::cout << "\n" << std::endl;
    log.push_back("step");
}


std::string AdvisorMain::getUserOption() {
    std::string userOption;
    // prompt user for a command
    std::cout << "Type in command: " << std::endl;
    std::getline(std::cin, userOption);
    // print the chosen option
    std::cout << "You typed " << userOption << std::endl;
    std::cout << "\n" << std::endl;
    return userOption;
}

void AdvisorMain::processUserOption(std::string userOption) {
    // create vector to compare user input
    std::vector<std::string> tokens = CSVReader::tokenise(userOption, ' ');

    if (userOption.compare("help") == 0) {
        help();
    }
    if (tokens.size() == 2 && tokens[0].compare("help") == 0) {
        helpcmd(tokens[1]);
    }
    if (userOption.compare("prod") == 0) {
        prod();
    }
    if (tokens[0].compare("min") == 0) {
        std::cout << "The min " << tokens[2] << " for " << tokens[1] 
                    << " is " << min(tokens) << std::endl;
        std::cout << "\n" << std::endl;
    }
    if (tokens[0].compare("max") == 0) {
        std::cout << "The max " << tokens[2] << " for " << tokens[1] 
                    << " is " << max(tokens) << std::endl;
        std::cout << "\n" << std::endl;
    }
    if (tokens[0].compare("avg") == 0) {
        avg(tokens);
    }
    if (tokens[0].compare("predict") == 0) {
        predict(tokens);
    }
    if (userOption.compare("time") == 0) {
        time();
    }
    if (userOption.compare("step") == 0) {
        step();
    }
    if (userOption.compare("log") == 0) {
        std::cout << "commands previously chosen: " << std::endl;
        for (std::string& l : log) {
            std::cout << l << std::endl;
        }
        std::cout << "\n" << std::endl;
    }
    
    if (userOption.compare("exit") == 0) {
        exit(3);
    }
}
