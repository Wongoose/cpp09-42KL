#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>

#define RESET "\033[39m"
#define BLACK "\033[30m"
#define GREY "\033[90m"
#define RED "\033[31m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[94m"
#define MAGENTA "\033[35m"

// 2 files
// 1. csv file has date & exchange rate
// 2. input file has input date | amount
// What do I need to do?
// - Parsing (longest step, read, convert, get into map container)
// - Calculations (find closes date, multiply exchange rate)
// - Output (Print results, error handling)
class BitcoinExchange {
	public:
		// Constructors
		BitcoinExchange();
		BitcoinExchange(std::string str);
		BitcoinExchange(const BitcoinExchange &copy);

		// Destructor
		~BitcoinExchange();

		// Operators
		BitcoinExchange &operator=(BitcoinExchange other);

		// Getters

		// Setters

		// Functions
		void readCSV();
		void calculateValueFromInput(std::string filename);
		void printExchangeRateMap();

	private:
		std::map<time_t, float> _exchangeRateMap;
};

#endif
