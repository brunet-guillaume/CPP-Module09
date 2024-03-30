/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:52:42 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/30 16:51:20 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "style.h"

static bool isLeapYear(int year) {
	return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

static void getDateParts(std::string date, int &year, int &month, int &day) {
	int end = date.find("-");
	year = std::atoi(date.substr(0, end).c_str());
	date.erase(date.begin(), date.begin() + end + 1);
	end = date.find("-");
	month = std::atoi(date.substr(0, end).c_str());
	date.erase(date.begin(), date.begin() + end + 1);
	end = date.find("-");
	day = std::atoi(date.substr(0, end).c_str());
}

static long getEpochTime(std::string date) {
	std::tm		tm;
	std::time_t	t;
	int			year;
	int			month;
	int			day;

	getDateParts(date, year, month, day);
	if (!strptime((date + " 12:00:00").c_str(), "%Y-%m-%d %H:%M:%S", &tm))
		return (-1);
	if (year != tm.tm_year + 1900 || month != tm.tm_mon + 1 || day != tm.tm_mday)
		return (-1);
	if (year > 3000 || year < 1900)
		return (-1);
	if (month  == 2 && isLeapYear(year) && day > 29)
		return (-1);
	else if (month == 2 && !isLeapYear(year) && day > 28)
		return (-1);
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return (-1);
	t = std::mktime(&tm);
	return(t);
}

static int parseDbLine(std::string line, std::map<long, double> *db) {
	long	epoch;
	double	price;

	if (line.length() < 12)
		return (0);
	epoch = getEpochTime(line.substr(0, line.find(",")));
	if (epoch == -1)
		return (0);
	price = std::atof(line.substr(11, line.length()).c_str());
	db->insert(std::pair<long, double>(epoch, price));
	return (1);
}

BitcoinExchange::BitcoinExchange(): _valid_db(false) {
	std::ifstream	db_stream;
	std::string		line;

	db_stream.open("assets/data.csv");
	if (db_stream.good()) {
		this->_valid_db = true;
		for (std::string line; std::getline(db_stream, line) && this->_valid_db;) {
			if (line == "date,exchange_rate")
				continue ;
			if (!parseDbLine(line, &this->_db))
				this->_valid_db = false;
		}
	}
	db_stream.close();

//	std::map<long, double>::iterator it;
//	for (it = this->_db.begin(); it != this->_db.end(); it++)
//		std::cout << it->first << ": " << it->second << std::endl;
};

BitcoinExchange::BitcoinExchange(const BitcoinExchange &cpy) {
	*this = cpy;
};

BitcoinExchange::~BitcoinExchange() {};

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &rhs) {
	this->_db = rhs._db;
	return (*this);
}

bool	BitcoinExchange::isValidDb() {
	return (this->_valid_db);
}
