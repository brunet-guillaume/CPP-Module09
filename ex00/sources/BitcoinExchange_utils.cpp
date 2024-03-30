/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange_utils.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:52:56 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/30 22:59:19 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

std::string	dtoa(double nb) {
	std::ostringstream	s;
	std::string			str;

	s << std::setprecision(2) << std::fixed << nb;
	str = s.str();
	str = str.erase(str.find_last_not_of('0') + 1);
	if (str[str.length() - 1] == '.')
		str += "0";
	return (str);
}

std::string	epochtoa(long epoch) {
	struct tm	ts;
    char		buf[20];

	ts = *localtime(&epoch);
	strftime(buf, sizeof(buf), "%Y-%m-%d", &ts);
	return (buf);
}

void	ltrim(std::string &s) {
	int	i = 0;

	while (std::isspace(s[i]))
		i++;
    s = s.substr(i, s.length());
}

void	rtrim(std::string &s) {
	int	i = s.length() - 1;

	while (std::isspace(s[i]))
		i--;
    s = s.substr(0, i + 1);
}

std::map<int, std::string> split_trim(std::string str, std::string needle) {
	std::map<int, std::string>	split;
	std::string					sub;
	int							i = 0;

	int end = str.find(needle);
	while (end != -1) {
		sub = str.substr(0, end);
		ltrim(sub);
		rtrim(sub);
		split.insert(std::pair<int, std::string>(i++, sub));
		str.erase(str.begin(), str.begin() + end + needle.length());
		end = str.find(needle);
	}
	ltrim(str);
	rtrim(str);
	split.insert(std::pair<int, std::string>(i++, str));	
	return (split);
}

bool isLeapYear(int year) {
	return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

void getDateParts(std::string date, int &year, int &month, int &day) {
	int end = date.find("-");
	year = std::atoi(date.substr(0, end).c_str());
	date.erase(date.begin(), date.begin() + end + 1);
	end = date.find("-");
	month = std::atoi(date.substr(0, end).c_str());
	date.erase(date.begin(), date.begin() + end + 1);
	end = date.find("-");
	day = std::atoi(date.substr(0, end).c_str());
}

long getEpochTime(std::string date) {
	std::tm		tm;
	std::time_t	t;
	int			year;
	int			month;
	int			day;

	getDateParts(date, year, month, day);
	if (!strptime((date + " 12:00:00").c_str(), "%Y-%m-%d %H:%M:%S", &tm))
		return (-1);
	if (year != tm.tm_year + 1900 || month != tm.tm_mon + 1 || day != tm.tm_mday)
		return (-1);
	if (year > 3000 || year < 1900)
		return (-1);
	if (month  == 2 && isLeapYear(year) && day > 29)
		return (-1);
	else if (month == 2 && !isLeapYear(year) && day > 28)
		return (-1);
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return (-1);
	tm.tm_isdst = 0;
	t = std::mktime(&tm);
	return(t);
}
