/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange_utils.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 22:53:45 by gbrunet           #+#    #+#             */
/*   Updated: 2024/03/30 22:55:44 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_UTILS_HPP
# define BITCOINEXCHANGE_UTILS_HPP

std::string					dtoa(double nb);
std::string					epochtoa(long epoch);
void						ltrim(std::string &s);
void						rtrim(std::string &s);
std::map<int, std::string>	split_trim(std::string str, std::string needle);
bool						isLeapYear(int year);
void						getDateParts(std::string date, int &year,
								int &month, int &day);
long						getEpochTime(std::string date);

#endif
