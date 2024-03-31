/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 04:56:47 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/31 10:07:11 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "style.h"
#include <vector>
#include <iostream>
#include <algorithm>

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

vec_pair_ui_ui	PmergeMe::mergeSortPairVector(vec_pair_ui_ui vec) {
	int mid = vec.size() / 2;
	unsigned int i = 0, j = 0, k = 0;

	if (vec.size() < 2) 
		return (vec);
	vec_pair_ui_ui left(vec.begin(), vec.begin() + mid);
	vec_pair_ui_ui right(vec.begin() + mid, vec.end());
	left = this->mergeSortPairVector(left);
	right = this->mergeSortPairVector(right);
	while (i < left.size() && j < right.size()) {
		if (left[i].second < right[j].second) {
			vec[k] = left[i];
			i++;
		} else {
			vec[k] = right[j];
			j++;
		}
		k++;
	}
	while (i < left.size()) {
		vec[k] = left[i];
		i++;
		k++;
	}
	while (j < right.size()) {
		vec[k] = right[j];
		j++;
		k++;
	}	
	return (vec);
}

void	PmergeMe::prepareForBinarySearchVector() {
	bool			odd = (this->_vector.size() % 2) == 1;
	unsigned int	last = 0;
	unsigned int	size;

	size = this->_vector.size();
	if (odd)
		last = this->_vector.back();
	this->_pendVector.reserve(size / 2 + static_cast<int>(odd));
	this->_vector.clear();
	this->_vector.reserve(size);
	this->_vector.push_back(this->_pairVector.begin()->first);
	for (unsigned int i = 0; i < this->_pairVector.size(); i++) {
		this->_vector.push_back(this->_pairVector[i].second);
		if (i != 0)
			this->_pendVector.push_back(this->_pairVector[i].first);
    }
	if (odd)
		this->_pendVector.push_back(last); 
}

void	PmergeMe::binarySearchVector() {
	static constexpr std::uint_fast64_t jacobsthal_diff[] = {
		2, 2, 6, 10, 22, 42, 86, 170, 342, 682, 1366, 2730, 5462, 10922, 21846,
		43690, 87382, 174762, 349526, 699050, 1398102, 2796202, 5592406, 11184810,
		22369622, 44739242, 89478486, 178956970, 357913942, 715827882, 1431655766,
		2863311530, 5726623062, 11453246122, 22906492246, 45812984490, 91625968982,
		183251937962, 366503875926, 733007751850, 1466015503702, 2932031007402,
		5864062014806, 11728124029610, 23456248059222, 46912496118442, 93824992236886,
		187649984473770, 375299968947542, 750599937895082, 1501199875790165,
		3002399751580331, 6004799503160661, 12009599006321322, 24019198012642644,
		48038396025285288, 96076792050570576, 192153584101141152, 384307168202282304,
		768614336404564608, 1537228672809129216, 3074457345618258432, 6148914691236516864
    };
	std::vector<ui>::iterator main_it;
	std::vector<ui>::iterator pend_it;

	main_it = this->_vector.begin() + 2;
	pend_it = this->_pendVector.begin();

	for (int j = 0; ; ++j) {
		
	}





    for (int k = 0 ; ; ++k)
    {
        // Should be safe: in this code, std::distance should always return
        // a positive number, so there is no risk of comparing funny values
        using size_type = std::common_type_t<
            std::uint_fast64_t,
            typename std::list<RandomAccessIterator>::difference_type
        >;

        // Find next index
        auto dist = jacobsthal_diff[k];
        if (dist > static_cast<size_type>(std::distance(current_pend, std::end(pend)))) break;

        auto it = std::next(current_it, dist * 2);
        auto pe = std::next(current_pend, dist);

        do
        {
            --pe;
            it -= 2;

            auto insertion_point = std::upper_bound(
                std::begin(chain), *pe, *it,
                [=](const auto& lhs, const auto& rhs) {
                    return compare(lhs, *rhs);
                }
            );
            chain.insert(insertion_point, it);
        } while (pe != current_pend);

        std::advance(current_it, dist * 2);
        std::advance(current_pend, dist);
    }

    // If there are pend elements left, insert them into
    // the main chain, the order of insertion does not
    // matter so forward traversal is ok
    while (current_pend != std::end(pend))
    {
        auto insertion_point = std::upper_bound(
            std::begin(chain), *current_pend, *current_it,
            [=](const auto& lhs, const auto& rhs) {
                return compare(lhs, *rhs);
            }
        );
        chain.insert(insertion_point, current_it);
        current_it += 2;
        ++current_pend;
    }

}

void	PmergeMe::sortVector(const vec_ui &vec) {
	this->_vector = vec;
	this->sortPairVector();
	this->_pairVector = this->mergeSortPairVector(this->_pairVector);
	this->prepareForBinarySearchVector();
    
	for (unsigned int i = 0; i < this->_vector.size(); i++) {
		std::cout << this->_vector[i] << "\n";
    }
	std::cout << std::endl;
	
}
