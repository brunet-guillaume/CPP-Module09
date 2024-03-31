/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 04:54:51 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/31 20:11:42 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <list>

typedef unsigned int ui;
typedef std::pair<ui, ui> pair_ui_ui;
typedef std::vector<unsigned int> vec_ui;
typedef std::vector<pair_ui_ui> vec_pair_ui_ui;
typedef std::list<unsigned int> list_ui;
typedef std::list<pair_ui_ui> list_pair_ui_ui;
typedef list_ui::iterator list_it;
typedef list_pair_ui_ui::iterator list_pair_it;

class PmergeMe {
	private:
		vec_ui			_vector;
		vec_ui			_pendVector;
		vec_pair_ui_ui	_pairVector;

		void			sortPairVector();
		void			jacobGroupVector();
		void			prepareForBinarySearchVector();
		void			binarySearchVector(ui item, int x_max);
		vec_pair_ui_ui	mergeSortPairVector(vec_pair_ui_ui vec);
		
		list_ui			_list;
		list_ui			_pendList;
		list_pair_ui_ui	_pairList;

		void			sortPairList();
		void			jacobGroupList();
		void			prepareForBinarySearchList();
		void			binarySearchList(ui item, int x_max);
		list_pair_ui_ui	mergeSortPairList(list_pair_ui_ui list);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &cpy);
		~PmergeMe();

		PmergeMe	&operator=(const PmergeMe &rhs);

		void	printVector(ui maxLen);
		void	sortVector(const vec_ui &vec);

		void	printList(ui maxLen);
		void	sortList(const vec_ui &vec);
};

#endif
