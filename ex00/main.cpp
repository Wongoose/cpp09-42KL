#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
    (void)argc;
    BitcoinExchange instance = BitcoinExchange();
    // instance.printExchangeRateMap();
    std::cout << YELLOW << "Loading..." << std::endl << RESET;
    instance.readCSV();
    std::cout << GREEN << "DONE & CONVERTED!" << std::endl << RESET;
    instance.calculateValueFromInput(argv[1]);
    return (0);
}