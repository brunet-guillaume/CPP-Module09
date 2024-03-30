/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:20:01 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/30 16:15:14 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "style.h"
#include "BitcoinExchange.hpp"
#include <iostream>
#include <cstdlib>

void	help_msg(std::string msg) {
	std::cout << GREEN << TITLE << " 💬 " << msg << " " << END_STYLE << std::endl;
}

void	warning_msg(std::string msg) {
	std::cout << " ⚠️  " << GREEN << BOLD << UNDERLINE << msg << END_STYLE << std::endl;
}

int	main() {
	BitcoinExchange	be;

	if (!be.isValidDb()) {
		std::cerr << RED << "Error: Unable to parse correctly the database";
		std::cerr << END_STYLE << std::endl;
		return (1);
	}

	return (0);
}
