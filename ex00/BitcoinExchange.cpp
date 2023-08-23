#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(std::string str) { (void)str; }

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) {
	this->_exchangeRateMap = copy._exchangeRateMap;
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange other) {
	this->_exchangeRateMap = other._exchangeRateMap;
	return (*this);
}

void BitcoinExchange::_readCSV() {
	std::ifstream file;
	std::string buffer;

	file.open("data.csv");
	if (file.fail()) {
		std::cout << "Failed to open file! Exiting program." << std::endl;
		exit (EXIT_FAILURE);
	}
	// still need to skip the first header
	std::getline(file, buffer);
	while(std::getline(file, buffer)) {
		std::stringstream line(buffer);
		std::string temp;
		time_t dateTime;
		float exchangeRate;
		int i = 1;

		while (std::getline(line, temp, ',')) {
			switch (i) {
				case 1:
					dateTime = _convertDateFormat(temp);
					break;
				case 2:
					exchangeRate = _convertExchangeRateToFloat(temp);
					break;
				default:
					break;
			}
			i++;
		}
		_exchangeRateMap.insert(std::make_pair((time_t)dateTime, (float)exchangeRate)); // time_t, exchange rate
	}
}

time_t BitcoinExchange::_convertDateFormat(std::string date) {
	struct tm timeSet;
	std::string temp;
	std::stringstream sdate(date);

	int i = 1;

	while (std::getline(sdate, temp, '-')) {
		switch (i) {
			case 1:
				timeSet.tm_year = std::stoi(temp) - 1900;
				break;
			case 2:
				timeSet.tm_mon = std::stoi(temp);
				break;
			case 3:
				timeSet.tm_mday = std::stoi(temp);
				break;

			default:
				break;
		}
		i++;
	}

	time_t timeSinceEpoch = mktime(&timeSet);
	return (timeSinceEpoch);
}

float BitcoinExchange::_convertExchangeRateToFloat(std::string exchangeRate) {
	return (std::stof(exchangeRate));
}

// Functions
void BitcoinExchange::printExchangeRateMap() {
	_readCSV();
	std::map<time_t, float>::iterator head = _exchangeRateMap.begin();
	std::map<time_t, float>::iterator end = _exchangeRateMap.end();
	for (; head != end; head++) {
		std::cout << CYAN << head->first << " | " << head->second << std::endl << RESET;
	}
}