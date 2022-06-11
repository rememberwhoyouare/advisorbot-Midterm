#include "AdvisorMain.h"
#include <iostream>
#include <string>

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
    << std::endl;
}
/** output help for the specified command */
void AdvisorMain::helpcmd() {

}
/** list available products */
void AdvisorMain::prod() {

}
/** find minimum bid or ask for product in current time step */
void AdvisorMain::min() {

}
/** find maximum bid or ask for product in current time step */
void AdvisorMain::max() {

}
/** compute average ask or bid for the sent product 
 * over the sent number of time steps */
void AdvisorMain::avg() {

}
/** predict max or min ask or bid for the sent product for the next time step */
void AdvisorMain::predict() {

}
/** state current time in dataset, i.e. which timeframe are we looking at */
void AdvisorMain::time() {

}
/** move to next time step */
void AdvisorMain::step() {

}
/** HERE IMPLEMENT YOUR OWN COMMAND */

std::string AdvisorMain::getUserOption() {
    std::string userOption;
    // prompt user for a command
    std::cout << "Type in command: " << std::endl;
    std::getline(std::cin, userOption);
    
    std::cout << "You chose " << userOption << std::endl;
    return userOption;
}
void AdvisorMain::processUserOption(std::string userOption) {
    if (userOption.compare("help") == 0) {
        help();
    }
}
