/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:20:01 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/30 18:36:57 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "style.h"
#include "BitcoinExchange.hpp"
#include <iostream>
#include <cstdlib>

int	main(int ac, char **av) {
	BitcoinExchange	be;

	if (ac != 2) {
		std::cerr << RED << BOLD << "Error: " << END_STYLE;
		std::cerr << RED << "Argument needed" << END_STYLE << std::endl;
		std::cerr << RED << THIN << "./btc path/to/input_db" << END_STYLE;
		return (1);
	}
	if (!be.isValidDb()) {
		std::cerr << RED << BOLD << "Error: " << END_STYLE;
		std::cerr << RED << "Unable to parse correctly the database";
		std::cerr << END_STYLE << std::endl;
		return (1);
	}
	if (!be.convert(av[1])) {
		return (1);
	}
	return (0);
}
