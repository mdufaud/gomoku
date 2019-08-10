/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 19:09:38 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/10 15:38:07 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"

std::vector<std::string> &	split(const std::string & s, char delim, std::vector<std::string> & elems)
{
	std::stringstream	ss(s);
	std::string			item;

	while (std::getline(ss, item, delim))
		elems.push_back(item);
	return (elems);
}

std::vector<std::string>	split(const std::string & s, char delim)
{
	std::vector<std::string>	elems;

	split(s, delim, elems);
	return (elems);
}
