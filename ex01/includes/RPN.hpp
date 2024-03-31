/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:11:54 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/31 01:34:21 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <string>

class RPN {
	private:
		typedef std::string (RPN::*func)(int, int);

		std::stack<std::string>	_stack;
		std::stack<std::string>	_rpn;
		func					_calc[4];
		std::string				_rpn_exp;

		void	reverseStack();
		std::string	add(int a, int b);
		std::string	sub(int a, int b);
		std::string	mult(int a, int b);
		std::string	div(int a, int b);

	public:
		RPN();
		RPN(const RPN &cpy);
		~RPN();

		RPN	&operator=(const RPN &rhs);

		bool	addToStack(std::string str);
		void	calc();

		class InvalidRPNException: public std::exception {
			public:
				const char *what() const throw();
		};
		class DivByZeroException: public std::exception {
			public:
				const char *what() const throw();
		};
};

#endif
