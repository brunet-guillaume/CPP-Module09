/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe_list.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:19:35 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/31 20:13:07 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "style.h"
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

static void	move(list_it &it, long long n) {
    if (n >= 0) 
        while (n--) ++it;
    else 
        while (n++) --it;
}

static void	movePair(list_pair_it &it, long long n) {
    if (n >= 0) 
        while (n--) ++it;
    else 
        while (n++) --it;
}

static list_it	next(list_it const it) {
	list_it	new_it = it;

	return (++new_it);
}

static list_it	from(list_it const it, long long n) {
	list_it	new_it = it;

	move(new_it, n);
	return (new_it);
}

static list_pair_it	fromPair(list_pair_it const it, long long n) {
	list_pair_it	new_it = it;

	movePair(new_it, n);
	return (new_it);
}


void	PmergeMe::sortPairList() {
	int	odd = this->_list.size() % 2;
	
	list_it it;
	for (it = this->_list.begin(); it != from(this->_list.end(), -odd); move(it, 2)) {
		if (*it < *next(it))
			this->_pairList.push_back(std::pair<ui, ui>(*it, *next(it)));
		else
			this->_pairList.push_back(std::pair<ui, ui>(*next(it), *it));
	}
}

list_pair_ui_ui	PmergeMe::mergeSortPairList(list_pair_ui_ui list) {
	int mid = list.size() / 2;
	list_pair_ui_ui	newList;

	if (list.size() < 2) 
		return (list);
	list_pair_ui_ui left(list.begin(), fromPair(list.begin(), mid));
	list_pair_ui_ui right(fromPair(list.begin(), mid), list.end());
	left = this->mergeSortPairList(left);
	right = this->mergeSortPairList(right);
	list_pair_ui_ui::iterator leftIt = left.begin();
	list_pair_ui_ui::iterator rightIt = right.begin();
	list_pair_ui_ui::iterator leftEndIt = left.end();
	list_pair_ui_ui::iterator rightEndIt = right.end();
	while (leftIt != leftEndIt && rightIt != rightEndIt) {
		if (leftIt->second < rightIt->second) {
			newList.push_back(*leftIt);
			leftIt++;
		} else {
			newList.push_back(*rightIt);
			rightIt++;
		}
	}
	while (leftIt != leftEndIt) {
		newList.push_back(*leftIt);
		leftIt++;
	}
	while (rightIt != rightEndIt) {
		newList.push_back(*rightIt);
		rightIt++;
	}
	return (newList);
}

void	PmergeMe::prepareForBinarySearchList() {
	bool			odd = (this->_list.size() % 2) == 1;
	unsigned int	last = 0;

	if (odd)
		last = this->_list.back();
	this->_list.clear();
	this->_list.push_back(this->_pairList.front().first);
	this->_list.push_back(this->_pairList.front().second);
	this->_pairList.pop_front();

	while (this->_pairList.size()) {
		this->_list.push_back(this->_pairList.front().second);
		this->_pendList.push_back(this->_pairList.front().first);
		this->_pairList.pop_front();
    }
	if (odd)
		this->_pendList.push_back(last); 
}

void	PmergeMe::binarySearchList(ui item, int x_max) {
	int	start = 0;
	int	mid;
	
	list_it	it = this->_list.begin();
	while (start <= x_max) {
		mid = start + (x_max - start) / 2;
		if (*from(it, mid) < item)
			start = mid + 1;
		else
			x_max = mid - 1;
	}
	if (item > *from(it, start))
		this->_list.insert(from(this->_list.begin(), start - 1), item);
	else
		this->_list.insert(from(this->_list.begin(), start), item);
}

void	PmergeMe::jacobGroupList() {
	static unsigned long jacobsthal_diff[] = {
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

	int	x = 1, y = 0;
	int x_max, y_max;
	list_it	it;

	it = this->_pendList.begin();
	for (int i = 0; ; i++) {
		unsigned long dist = jacobsthal_diff[i];
		y_max = y + dist;
		x_max = x + dist;
		move(it, dist);
		if (static_cast<unsigned long>(y_max) > this->_pendList.size())
			break;
		while (y_max-- != y) {
			it--;
			this->binarySearchList(*it, x_max);
		}
		x += dist * 2;
		y += dist;
		move(it, dist);
	}
	y_max = this->_pendList.size();
	it = this->_pendList.end();
	while (y_max-- != y) {
		it--;
		this->binarySearchList(*it, this->_list.size() - 1);
	}
}

void	PmergeMe::printList(ui maxLen) {
	ui		size = this->_vector.size();
	ui		i = 0;
	list_it	it;

	for (it = this->_list.begin(); it != this->_list.end() && i < maxLen; it++) {
		std::cout << *it << " ";
		i++;
    }
	if (size > maxLen)
		std::cout << "[...]";
}

void	PmergeMe::sortList(const vec_ui &vec) {
	std::copy(vec.begin(), vec.end(), std::back_inserter(this->_list));
	this->sortPairList();
	this->_pairList = this->mergeSortPairList(this->_pairList);
	this->prepareForBinarySearchList();
	this->jacobGroupList();
}

