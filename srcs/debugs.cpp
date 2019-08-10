/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugs.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 16:50:08 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/11 17:11:47 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"

void	debugs(std::string s)
{
	std::cout << s << std::endl;
}

void	debugi(int i)
{
	std::cout << "int = " << i << std::endl;
}

void	debugs(std::string s, std::string s1)
{
	std::cout << s << ": " << s1 << std::endl;
}
