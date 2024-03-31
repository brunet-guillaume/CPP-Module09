/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 04:56:47 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/31 06:15:18 by gbrunet          ###   ########.fr       */
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

void	PmergeMe::sortPairVector() {
	int	odd = this->_vector.size() % 2;

	this->_pairVector.reserve(this->_vector.size() / 2);
	vec_ui::iterator it;
	for (it = this->_vector.begin(); it != this->_vector.end() - odd; it += 2) {
		if (*it < *(it + 1))
			this->_pairVector.push_back(std::pair<ui, ui>(*it, *(it + 1)));
		else
			this->_pairVector.push_back(std::pair<ui, ui>(*(it + 1), *it));
	}
}

void	PmergeMe::sortVector(const vec_ui &vec) {
	this->_vector = vec;
	this->sortPairVector();
}
