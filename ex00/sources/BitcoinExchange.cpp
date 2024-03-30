/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:52:42 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/30 22:58:28 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "style.h"

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

static double checkPrice(std::string str, int &err_code) {
	int		point = 0;
	int		i = 0;
	double	price;

	err_code = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i]) {
		if (std::isdigit(str[i]))
			i++;
		else if (str[i] == '.') {
			if (point == 0) {
				point = 1;
				i++;
			}
			else {
				err_code = 1;
				break ;
			}
		} else {
			err_code = 1;
			break ;
		}
	}
	if (err_code != 0)
		return (0);
	price = std::atof(str.c_str());
	if (price < 0)
		err_code = 2;
	else if (price > 1000)
		err_code = 3;
	return (price);
}

void  BitcoinExchange::parseInputLine(std::string line) {
	long						epoch;
	std::map<int, std::string>	split;
	static int					line_num = 1;
	int							err_code;

	line_num++;
	split = split_trim(line, "|");
	if (split.size() != 2 && (split.size() == 1 && split[0] != "")) {
		this->printLineError(line_num);
		return ;
	}
	if (split.size() == 1 && split[0] == "")
		return ;
	epoch = getEpochTime(split[0]);
	checkPrice(split[1], err_code);
	if (epoch == -1 && err_code != 0)
		this->printLineDateBtcError(split[0], split[1], err_code);
	else if (epoch == -1)
		this->printLineDateError(split[0], split[1], 0);
	else if (err_code != 0)
		this->printLineBtcError(split[0], split[1], err_code);	
	else {

		std::map<long, double>::iterator low;
		low = this->_db.lower_bound(epoch);
    	if (low->first != epoch && low == this->_db.begin())
			this->printLineDateError(split[0], split[1], 1);
		else if (low->first != epoch){
			low--;
			this->printLine(split[0], split[1], low->first, low->second);
		} else
			this->printLine(split[0], split[1], low->first, low->second);
	}
}

BitcoinExchange::BitcoinExchange(): _valid_db(false) {
	std::ifstream	db_stream;
	std::string		line;

	db_stream.open("assets/data.csv");
	if (db_stream.good()) {
		this->_valid_db = true;
		for (; std::getline(db_stream, line) && this->_valid_db;) {
			if (line == "date,exchange_rate")
				continue ;
			if (!parseDbLine(line, &this->_db))
				this->_valid_db = false;
		}
	}
	db_stream.close();
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

bool	BitcoinExchange::convert(const std::string input_db) {
	std::ifstream				input_stream;
	std::string					line;
	std::map<int, std::string>	split;

	input_stream.open(input_db.c_str());
	if (!input_stream.good()) {
		input_stream.close();
		return (false);
	}
	std::getline(input_stream, line);
	split = split_trim(line, "|");
	if (!(split.size() == 2 && split[0] == "date" && split[1] == "value")) {
		std::cerr << RED << BOLD << "Error: " << END_STYLE;
		std::cerr << RED << "First line in input database is incorrect";
		std::cerr << END_STYLE << std::endl;
		return (false);
	}
	printTop();
	for (; std::getline(input_stream, line);)
		this->parseInputLine(line);
	this->printBottom();
	input_stream.close();
	return (true);
}
