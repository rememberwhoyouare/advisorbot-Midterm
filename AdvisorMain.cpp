#include "AdvisorMain.h"
#include <iostream>
#include <string>
#include <vector>
#include "CSVReader.h"
#include "OrderBook.h"

AdvisorMain::AdvisorMain() {

}

void AdvisorMain::init() {
    std::string input;
    std::cout << "Command 'help' to list all available commands." << std::endl;

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
    "\n custom"
    "\n exit"
    << std::endl;
}
/** output help for the specified command */
void AdvisorMain::helpcmd(std::string cmd) {
    if (cmd.compare("prod") == 0) {
        std::cout << "list available products" << std::endl;
    }
    else if (cmd.compare("min") == 0) {
        std::cout << "min ETH/BTC ask -> min ETH/BTC ask in the current time step" << std::endl;
    }
    else if (cmd.compare("max") == 0) {
        std::cout << "max ETH/BTC ask -> max ETH/BTC ask in the current time step" << std::endl;
    }
    else if (cmd.compare("avg") == 0) {
        std::cout << "avg ETH/BTC bid 10 -> average ETH/BTC bid over last 10 timesteps" << std::endl;
    }
    else if (cmd.compare("predict") == 0) {
        std::cout << "predict max ETH/BTC bid ->  The average ETH/BTC ask price over the last 10 timesteps" << std::endl;
    }
    else if (cmd.compare("time") == 0) {
        std::cout << "state current time in dataset, i.e. which timeframe are we looking at" << std::endl;
    }
    else if (cmd.compare("step") == 0) {
        std::cout << "move to next time step" << std::endl;
    }
    else if (cmd.compare("exit") == 0) {
        std::cout << "exit the program" << std::endl;
    }
    else {
        std::cout << "wrong command, type 'help' to see the list of available commands." << std::endl;
    }
}
/** list available products */
void AdvisorMain::prod() {
    std::cout << "Avaliable products are: " << std::endl;
    for (std::string const& product : orderBook.getKnownProducts()) {
        std::cout << product << std::endl;
    }
    // print new line
    std::cout << "\n" << std::endl;

}
/** find minimum bid or ask for product in current time step */
void AdvisorMain::min() {
    std::cout << "The miminum is 0" << std::endl;
}
/** find maximum bid or ask for product in current time step */
void AdvisorMain::max() {
    std::cout << "The maximum is 0" << std::endl;
}
/** compute average ask or bid for the sent product 
 * over the sent number of time steps */
void AdvisorMain::avg() {
    std::cout << "The average is 0 so far" << std::endl;
}
/** predict max or min ask or bid for the sent product for the next time step */
void AdvisorMain::predict() {
    std::cout << "Cannot predict without data" << std::endl;
}
/** state current time in dataset, i.e. which timeframe are we looking at */
void AdvisorMain::time() {
    std::cout << "Current time is 000000" << std::endl;
}
/** move to next time step */
void AdvisorMain::step() {
    std::cout << "Moving to the next step..." << std::endl;
}
/** HERE IMPLEMENT YOUR OWN COMMAND */



std::string AdvisorMain::getUserOption() {
    std::string userOption;
    // prompt user for a command
    std::cout << "Type in command: " << std::endl;
    std::getline(std::cin, userOption);
    // print the chosen option
    std::cout << "You chose " << userOption << std::endl;
    return userOption;
}

void AdvisorMain::processUserOption(std::string userOption) {
    // create vector to get help cmd option
    std::vector<std::string> token = CSVReader::tokenise(userOption, ' ');

    if (userOption.compare("help") == 0) {
        help();
    }
    if (token.size() == 2 && token[0].compare("help") == 0) {
        helpcmd(token[1]);
    }
    if (userOption.compare("prod") == 0) {
        prod();
    }
    if (userOption.compare("min") == 0) {
        min();
    }
    if (userOption.compare("max") == 0) {
        max();
    }
    if (userOption.compare("avg") == 0) {
        avg();
    }
    if (userOption.compare("predict") == 0) {
        predict();
    }
    if (userOption.compare("time") == 0) {
        time();
    }
    if (userOption.compare("step") == 0) {
        step();
    }
    if (userOption.compare("exit") == 0) {
        exit(3);
    }
}
