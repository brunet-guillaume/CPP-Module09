/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 04:54:51 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/31 05:34:46 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>

class PmergeMe {
	private:
		std::vector<unsigned int>	_vector;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &cpy);
		~PmergeMe();

		PmergeMe	&operator=(const PmergeMe &rhs);

		void	sortVector(const std::vector<unsigned int> &vec);
};

#endif
