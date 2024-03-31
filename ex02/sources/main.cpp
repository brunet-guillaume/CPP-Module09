/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:20:01 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/31 06:05:26 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "style.h"
#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>

static void	ltrim(std::string &s) {
	int	i = 0;

	while (std::isspace(s[i]))
		i++;
    s = s.substr(i, s.length());
}

static void	rtrim(std::string &s) {
	int	i = s.length() - 1;

	while (std::isspace(s[i]))
		i--;
    s = s.substr(0, i + 1);
}

static bool	unsIntOverflow(std::string str) {
	if (str[0] == '+') {
		if (str.length() > 11)
			return (true);
		else if (str.length() == 11 && str.compare("+4294967295") > 0)
			return (true);
	} else {
		if (str.length() > 10)
			return (true);
		else if (str.length() == 10 && str.compare("4294967295") > 0)
			return (true);
	}
	return (false);
}

static bool	isUnsInt(std::string str) {
	size_t	i = 0;

	ltrim(str);
	rtrim(str);
	if (str[0] == '+')
		i++;
	for (; i < str.length(); i++) {
		if (isdigit(str[i])) {
			continue ;
		} else {
			return (false);
		}
	}
	return (!unsIntOverflow(str));
}

static bool	hasDuplicates(vec_ui &vec) {
	vec_ui::iterator it1;
	vec_ui::iterator it2;

	for (it1 = vec.begin(); it1 != vec.end() - 1; it1++) {
		for (it2 = it1 + 1; it2 != vec.end(); it2++) {
			if (*it1 == *it2)
				return (true);
		}
	}
	return (false);
}

int	main(int ac, char **av) {
	PmergeMe	pmm;
	vec_ui		entries;
	int							i = 0;

	if (ac == 1) {
		std::cerr << RED BOLD "Error: " END_STYLE;
		std::cerr << RED "Arguments needed" END_STYLE << std::endl;
		std::cerr << RED THIN "./PmergeMe `shuf -i 1-100000 -n 3000 | tr \"\\n\" \" \"`";
		std::cerr << END_STYLE << std::endl;
		return (1);
	}
	while (av[++i]) {
		if (!isUnsInt(av[i])) {
			std::cerr << RED BOLD "Error: " END_STYLE;
			std::cerr << RED << av[i] << " is not an unsigned integer";
			std::cerr << END_STYLE << std::endl;
			return (1);
		}
		entries.push_back(std::atol(av[i]));
	}
	if (hasDuplicates(entries)) {
		std::cerr << RED BOLD "Error: " END_STYLE;
		std::cerr << RED "There are some duplicates" END_STYLE << std::endl;
		return (1);
	}
	pmm.sortVector(entries);

	return (0);
}
