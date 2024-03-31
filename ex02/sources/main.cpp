/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:20:01 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/31 20:23:20 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "style.h"
#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <cstdlib>
#include <sys/time.h>
#include <iomanip>
#include <sstream>

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
	std::set<ui> s(vec.begin(), vec.end());

	return (s.size() != vec.size());
}

static std::string	dtoa(double nb) {
	std::ostringstream	s;
	std::string			str;

	s << std::setprecision(3) << std::fixed << nb;
	str = s.str();
	str = str.erase(str.find_last_not_of('0') + 1);
	if (str[str.length() - 1] == '.')
		str += "0";
	return (str);
}

static void	printEntries(vec_ui &vec, ui maxLen) {
	ui	size = vec.size();

	for (unsigned int i = 0; i < size && i < maxLen; i++) {
		std::cout << vec[i] << " ";
    }
	if (size > maxLen)
		std::cout << "[...]";
}

static unsigned long  getTime()
{
	struct timeval	time;

	gettimeofday (&time, NULL);
	return (time.tv_usec + time.tv_sec * 1000000);
}


static void sort(PmergeMe &pmm, vec_ui &entries) {
	unsigned long vecIn, vecOut;
	unsigned long listIn, listOut;

	std::cout << THIN "<vector>... " END_STYLE << std::endl;
	vecIn = getTime();
	pmm.sortVector(entries);
	vecOut = getTime();
	std::cout << "Done." END_STYLE << std::endl;

	std::cout << THIN "<list>... " END_STYLE << std::endl;
	listIn = getTime();
	pmm.sortList(entries);
	listOut = getTime();
	std::cout << "Done. \n\n" END_STYLE << std::endl;

	std::cout << YELLOW "Before : " BOLD;
	printEntries(entries, 20);
	std::cout << "\n\n" END_STYLE;

	std::cout << CYAN "Container : " BOLD "<vector> :\n" END_STYLE;
	std::cout << GREEN " After : " BOLD;
	pmm.printVector(20);
	std::cout << "\n" END_STYLE;
	std::cout << PURPLE "  Time to process a range of " BOLD << entries.size();
	std::cout << END_STYLE PURPLE " elements: " BOLD RED << vecOut - vecIn;
	std::cout << " µs " END_STYLE RED "(";
	std::cout << dtoa(static_cast<double>(vecOut - vecIn) / 1000000.0) << " s)\n\n";
	std::cout << END_STYLE;

	std::cout << CYAN "Container : " BOLD "<list> :\n" END_STYLE;
	std::cout << GREEN " After : " BOLD;
	pmm.printList(20);
	std::cout << "\n" END_STYLE;
	std::cout << PURPLE "  Time to process a range of " BOLD << entries.size();
	std::cout << END_STYLE PURPLE " elements: " BOLD RED << listOut - listIn;
	std::cout << " µs " END_STYLE RED "(";
	std::cout << dtoa(static_cast<double>(listOut - listIn) / 1000000.0) << " s)\n";
	std::cout << END_STYLE;
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
	std::cout << CYAN BOLD "\nVerifying the input array..." END_STYLE << std::endl;
	while (av[++i]) {
		if (!isUnsInt(av[i])) {
			std::cerr << RED " ❌ " << av[i] << " is not an unsigned integer";
			std::cerr << END_STYLE << std::endl;
			return (1);
		}
		entries.push_back(std::atol(av[i]));
	}
	std::cout << GREEN " ✅  All arguments are unsigned long" END_STYLE << std::endl;
	std::cout << CYAN BOLD "\nChecking for duplicates..." END_STYLE << std::endl;
	if (hasDuplicates(entries)) {
		std::cerr << RED " ❌ There are some duplicates" END_STYLE << std::endl;
		return (1);
	}
	std::cout << GREEN " ✅  No duplicates" END_STYLE << std::endl;
	std::cout << CYAN BOLD "\nStarting sortings..." END_STYLE << std::endl;
	sort(pmm, entries);
	return (0);
}
