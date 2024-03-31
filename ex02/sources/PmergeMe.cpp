/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 04:56:47 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/31 18:20:31 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &cpy) {
	*this = cpy;
}

PmergeMe::~PmergeMe() {}

PmergeMe	&PmergeMe::operator=(const PmergeMe &rhs) {
	this->_vector = rhs._vector;
	this->_pairVector = rhs._pairVector;
	this->_pendVector = rhs._pendVector;
	this->_list = rhs._list;
	this->_pairList = rhs._pairList;
	this->_pendList = rhs._pendList;

	return (*this);
}
