/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 04:56:47 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/31 05:38:16 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <vector>
#include <iostream>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &cpy) {
	*this = cpy;
}

PmergeMe::~PmergeMe() {}

PmergeMe	&PmergeMe::operator=(const PmergeMe &rhs) {
	(void)rhs;
	return (*this);
}

void	PmergeMe::sortVector(const std::vector<unsigned int> &vec) {
	this->_vector = vec;

	std::vector<unsigned int>::iterator it;

	for (it = this->_vector.begin(); it != this->_vector.end(); it++)
		std::cout << *it << " ";
}
