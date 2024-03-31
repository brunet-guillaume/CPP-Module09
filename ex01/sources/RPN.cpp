/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:14:42 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/31 01:57:11 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include "style.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>

RPN::RPN(): _rpn_exp("") {
	this->_calc[0] = &RPN::add;
	this->_calc[1] = &RPN::sub;
	this->_calc[2] = &RPN::mult;
	this->_calc[3] = &RPN::div;
}

RPN::RPN(const RPN &cpy) {
	*this = cpy;
}

RPN::~RPN() {}

RPN	&RPN::operator=(const RPN &rhs) {
	this->_stack = rhs._stack;
	this->_rpn = rhs._rpn;
	this->_rpn_exp = rhs._rpn_exp;
	return (*this);
}

static bool	isSign(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return (true);
	return (false);
}

bool	RPN::addToStack(std::string str) {
	int	i = -1;
	while (str[++i]) {
		if (std::isdigit(str[i])) {
			this->_stack.push(std::string(1, str[i]));
			this->_rpn_exp += std::string(1, str[i]) + " ";
		} else if (isSign(str[i])) {
			this->_stack.push(std::string(1, str[i]));
			this->_rpn_exp += std::string(1, str[i]) + " ";
		} else if (std::isspace(str[i]))
			continue ;
		else
			return (false);
	}

	return (true);
}

void	RPN::reverseStack() {
	while (this->_stack.size()) {
		this->_rpn.push(this->_stack.top());
		this->_stack.pop();
	}
}

static std::string	dtoa(double nb) {
	std::ostringstream	s;
	std::string			str;

	s << std::setprecision(8) << std::fixed << nb;
	str = s.str();
	str = str.erase(str.find_last_not_of('0') + 1);
	if (str[str.length() - 1] == '.')
		str += "0";
	return (str);
}

std::string	RPN::add(double a, double b) {
	return (dtoa(a + b));
}

std::string	RPN::sub(double a, double b) {
	return (dtoa(a - b));
}

std::string	RPN::mult(double a, double b) {
	return (dtoa(a * b));
}

std::string	RPN::div(double a, double b) {
	if (b == 0)
		throw RPN::DivByZeroException();
	return (dtoa(a / b));
}

void	RPN::calc() {
	std::string	str;
	char		sign[] = {'+', '-', '*', '/'};
	double		a;
	double		b;

	this->reverseStack();
	while (this->_rpn.size()) {
		str = this->_rpn.top();
		this->_rpn.pop();
		if (isSign(str[0]) && this->_stack.size() >= 2) {
			b = std::atof(this->_stack.top().c_str());
			this->_stack.pop();
			a = std::atof(this->_stack.top().c_str());
			this->_stack.pop();
			for (int i = 0; i < 4; i++) {
				if (str[0] == sign[i])
					this->_stack.push((this->*_calc[i])(a, b));
			}
		} else if (isSign(str[0])) {
			throw RPN::InvalidRPNException();
		} else {
			this->_stack.push(str);
		}
	}
	if (this->_stack.size() == 1) {
		std::cout << CYAN "RPN: "<< this->_rpn_exp << std::endl;
		std::cout << GREEN " =>  " BOLD << this->_stack.top() << END_STYLE << std::endl;
	} else {
		throw RPN::InvalidRPNException();
	}
}

const char *RPN::InvalidRPNException::what() const throw() {
	return ("Invalid RPN expression");
}

const char *RPN::DivByZeroException::what() const throw() {
	return ("Division by zero is impossible");
}
