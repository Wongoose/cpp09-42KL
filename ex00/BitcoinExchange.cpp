/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:33:52 by zwong             #+#    #+#             */
/*   Updated: 2023/10/24 13:33:52 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

// HELPER functions
void _printDateFromEpoch(const time_t &dateTime) {
	struct tm* nowStruct = std::gmtime(&dateTime);
	std::cout << nowStruct->tm_year + 1900
		<< "-" << ((nowStruct->tm_mon + 1 < 10) ? "0" : "") << nowStruct->tm_mon + 1
		<< "-" << ((nowStruct->tm_mday + 1 < 10) ? "0" : "") << nowStruct->tm_mday + 1;
}

void _printLineResult(time_t dateTime, float value, std::map<time_t, float> exchangeRateMap) {
	std::map<time_t, float>::iterator head = exchangeRateMap.begin();
	std::map<time_t, float>::iterator end = exchangeRateMap.end();
	std::map<time_t, float>::iterator current = head;
	long diff = -1;
	for (; head != end; head++) {
		if (dateTime - head->first < 0)
			break ;
		if (diff == -1 || (dateTime - head->first < diff)) {
			current = head;
			diff = dateTime - head->first;
		}
	}
	_printDateFromEpoch(dateTime);
	std::cout << " => " << value << " = " << value * current->second << std::endl;
}

int _isValidDate(int year, int month, int day)
{
    unsigned int leap;
    unsigned char mon_day[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (year < 1)
        return (0);
    if ((month < 1) || (month > 12))
        return (0);
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
        leap = (1);
    else
        leap = 0;
    mon_day[1] += leap;
    if ((day > mon_day[month - 1]) || (day < 1))
        return (0);
    return (1);
}

time_t _convertDateFormat(std::string date) {
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
				timeSet.tm_mon = std::stoi(temp) - 1;
				break;
			case 3:
				timeSet.tm_mday = std::stoi(temp);
				break;

			default:
				break;
		}
		i++;
	}
	timeSet.tm_hour = 0;
	timeSet.tm_min = 0;
	timeSet.tm_sec = 0;
	if (!_isValidDate(timeSet.tm_year, timeSet.tm_mon + 1, timeSet.tm_mday)) {
		std::cout << RED << "Error: Bad input => "
			<< timeSet.tm_year + 1900 << "-"
			<< timeSet.tm_mon + 1 << "-"
			<< timeSet.tm_mday
			<< std::endl << RESET;
		return (-1);
	}
	time_t timeSinceEpoch = std::mktime(&timeSet);
	return (timeSinceEpoch);
}

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

// PUBLIC functions
void BitcoinExchange::readCSV() {
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
					exchangeRate = std::stof(temp);
					break;
				default:
					break;
			}
			i++;
		}
		_exchangeRateMap.insert(std::make_pair((time_t)dateTime, (float)exchangeRate)); // time_t, exchange rate
	}
}

void BitcoinExchange::calculateValueFromInput(std::string filename) {
	std::ifstream file;
	std::string buffer;

	file.open(filename);
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
		float value;
		int i = 1;

		while (std::getline(line, temp, '|')) {
			switch (i) {
				case 1:
					dateTime = _convertDateFormat(temp);
					break;
				case 2:
					value = std::stof(temp);
					break;
				default:
					break;
			}
			i++;
		}
		// VALIDATION:
		if (dateTime == -1)
			continue;
		else if (value < 0)
			std::cout << RED << "Error: Not a positive number" << std::endl << RESET;
		else if (value > 1000)
			std::cout << RED << "Error: Number too large" << std::endl << RESET;
		else
			_printLineResult(dateTime, value, this->_exchangeRateMap);
	}
}


void BitcoinExchange::printExchangeRateMap() {
	std::map<time_t, float>::iterator head = _exchangeRateMap.begin();
	std::map<time_t, float>::iterator end = _exchangeRateMap.end();
	for (; head != end; head++) {
		std::cout << CYAN << head->first << " | " << head->second << std::endl << RESET;
	}
}
