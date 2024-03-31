/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 04:54:51 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/31 17:11:44 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>

typedef unsigned int ui;
typedef std::pair<ui, ui> pair_ui_ui;
typedef std::vector<unsigned int> vec_ui;
typedef std::vector<pair_ui_ui> vec_pair_ui_ui;

class PmergeMe {
	private:
		vec_ui					_vector;
		std::vector<pair_ui_ui>	_pairVector;
		vec_ui					_pendVector;

		void			sortPairVector();
		vec_pair_ui_ui	mergeSortPairVector(vec_pair_ui_ui vec);
		void			prepareForBinarySearchVector();
		void			jacobGroupVector();
		void			binarySearchVector(ui item, int x_max);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &cpy);
		~PmergeMe();

		PmergeMe	&operator=(const PmergeMe &rhs);

		void	sortVector(const vec_ui &vec);
};

#endif
