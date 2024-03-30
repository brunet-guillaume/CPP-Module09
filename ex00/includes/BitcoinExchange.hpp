/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:46:19 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/30 22:56:17 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>
# include "BitcoinExchange_utils.hpp"

class BitcoinExchange {
	private:
		std::map<long, double>	_db;
		bool					_valid_db;

		void	printTop();
		void	printBottom();
		void	printLine(std::string date, std::string btc, long db_date, double rate);
		void	printLineError(int line);
		void	printLineDateError(std::string date, std::string btc, int type);
		void	printLineDateBtcError(std::string date, std::string btc, int type);
		void	printLineBtcError(std::string date, std::string btc, int type);
		void	parseInputLine(std::string line);

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &cpy);
		~BitcoinExchange();

		BitcoinExchange	&operator=(const BitcoinExchange &rhs);

		bool	isValidDb();
		bool	convert(const std::string input_db);
};

#endif
