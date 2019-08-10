/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_string.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"

std::string		to_string(double d)
{
	std::stringstream	ss;
	std::string			s;

	ss << d;
	s = ss.str();
	return (s);
}

std::string		to_string(int i)
{
	std::stringstream	ss;
	std::string			s;

	ss << i;
	s = ss.str();
	return (s);
}
