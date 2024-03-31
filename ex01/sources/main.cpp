/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:20:01 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/31 01:40:10 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "style.h"
#include <iostream>
#include "RPN.hpp"

int	main(int ac, char **av) {
	RPN		rpn;
	int		i = 0;
	bool	no_err = true;

	if (ac == 1){
		std::cerr << RED << BOLD << "Error: " END_STYLE;
		std::cerr << RED << "Argument needed" END_STYLE << std::endl;
		std::cerr << RED << THIN << "./RPN \"3 5 6 + *\"" END_STYLE << std::endl;
		return (1);
	}
	while (av[++i] && no_err)
		no_err = rpn.addToStack(av[i]);
	if (!no_err) {
		std::cerr << RED BOLD "Error: " END_STYLE;
		std::cerr << RED "Wrong arguments format. " << std::endl;
		std::cerr << "Available characters: [0-9], +, -, '*', /" END_STYLE << std::endl;
		std::cerr << RED THIN "./RPN \"3 5 6 + *\"" END_STYLE << std::endl;
		std::cerr << RED THIN "./RPN 3 5 6 + \"*\"" END_STYLE << std::endl;
		std::cerr << RED THIN "./RPN 356+\'*\'" END_STYLE << std::endl;
		std::cerr << RED THIN "./RPN 3\"56\"+\"*\"" END_STYLE << std::endl;
		return (1);
	}
	try {
		rpn.calc();
	} catch (std::exception &e) {
		std::cerr << RED BOLD "Error: " END_STYLE;
		std::cerr << RED << e.what() << END_STYLE << std::endl;
	}
	return (0);
}
