/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange_print.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:39:12 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/30 22:57:28 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include "style.h"
#include <iostream>
#include <cstdlib>

void	BitcoinExchange::printTop() {
	std::cout << CYAN <<\
		"╔════════════════╦═════════════════╦═══════════════════╦══════════════════════════╗" \
		<< std::endl;
	std::cout << "║" WHITE BOLD "      DATE      " CYAN "║" WHITE BOLD "   AMOUNT(BTC)   " \
		<< CYAN "║" WHITE BOLD"     AMOUNT($)     " CYAN "║" WHITE BOLD "         DB ENTRY" \
		<< CYAN "         ║" END_STYLE CYAN << std::endl;
	std::cout << \
		"╠════════════════╬═════════════════╬═══════════════════╬══════════════════════════╣" \
		<< std::endl;
}

void	BitcoinExchange::printBottom() {
	std::cout << CYAN <<\
		"╚════════════════╩═════════════════╩═══════════════════╩══════════════════════════╝" \
		<< END_STYLE << std::endl;
}

void	BitcoinExchange::printLine(std::string date, std::string btc,
		long db_date, double rate) {
	std::cout << "║ " GREEN << date << CYAN "     ║ " YELLOW;
	std::cout.width(17);
	std::cout <<  "₿ " + btc << CYAN " ║ " PURPLE BOLD;
	std::cout.width(17);
	std::cout << "$ " + dtoa(rate * std::atof(btc.c_str())) << CYAN " ║ " WHITE THIN;
	std::cout << epochtoa(db_date);
	std::cout.width(14);
	std::cout << "$ " + dtoa(rate) << END_STYLE CYAN " ║" << std::endl;	
}

void	BitcoinExchange::printLineError(int line) {
	std::cout << "║                ║                 ║ " BOLD RED;
	std::cout << "Error: line ";
	std::cout.width(5);
	std::cout << std::left << line << std::right << END_STYLE CYAN " ║ " RED;
	std::cout << "Wrong format            " CYAN " ║" << std::endl;
}

void	BitcoinExchange::printLineDateError(std::string date,
		std::string btc, int type) {
	std::cout << "║ " RED;
	std::cout.width(14);
	std::cout << std::left << date << std::right << CYAN " ║ " WHITE THIN;
	std::cout.width(17);
	std::cout <<  "₿ " + btc << END_STYLE CYAN " ║ " BOLD RED;
	std::cout << "Error: date      " END_STYLE CYAN " ║ " RED;
	if (type == 1)
		std::cout << "Bitcoin did not exist   " CYAN " ║" << std::endl;
	else
		std::cout << "                        " CYAN " ║" << std::endl;
}

void	BitcoinExchange::printLineDateBtcError(std::string date,
		std::string btc, int type) {
	std::cout << "║ " RED;
	std::cout.width(14);
	std::cout << std::left << date << std::right << CYAN " ║ " RED;
	std::cout.width(17);
	std::cout << "₿ " + btc << END_STYLE CYAN " ║ " BOLD RED;
	std::cout << "Error: both      " END_STYLE CYAN " ║ " RED;
	if (type == 1)
		std::cout << "Invalide number         " CYAN " ║" << std::endl;
	else if (type == 2)
		std::cout << "Negative number         " CYAN " ║" << std::endl;
	else
		std::cout << "Too large number        " CYAN " ║" << std::endl;
}

void	BitcoinExchange::printLineBtcError(std::string date,
		std::string btc, int type) {
	std::cout << "║ " WHITE THIN;
	std::cout.width(14);
	std::cout << std::left << date << std::right << CYAN " ║ " RED;
	std::cout.width(17);
	std::cout <<  "₿ " + btc << END_STYLE CYAN " ║ " BOLD RED;
	std::cout << "Error: amount    " END_STYLE CYAN " ║ " RED;
	if (type == 1)
		std::cout << "Invalide number         " CYAN " ║" << std::endl;
	else if (type == 2)
		std::cout << "Negative number         " CYAN " ║" << std::endl;
	else
		std::cout << "Too large number        " CYAN " ║" << std::endl;
}
