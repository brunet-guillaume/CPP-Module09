/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:46:19 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/30 16:12:27 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

class BitcoinExchange {
	private:
		std::map<long, double>	_db;
		bool					_valid_db;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &cpy);
		~BitcoinExchange();

		BitcoinExchange	&operator=(const BitcoinExchange &rhs);

		bool	isValidDb();
};

#endif
