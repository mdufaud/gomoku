/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printPuzzle.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 19:49:28 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/17 15:18:47 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"

static int			numsize(int number)
{
	int		size;

	size = 1;
	while (number >= 10)
	{
		number = number / 10;
		size++;
	}
	return (size);
}
/*
void				printPuzzle(t_matrix container)
{
	t_matrix::iterator		it = container.begin();
	int						i;
	int						size;

	size = numsize(container.size() * container.size());
	while (it != container.end())
	{
		t_matrixLine::iterator		it2 = (*it).begin();
		while (it2 != (*it).end())
		{
			std::cout << (*it2) << " ";
			i = 0;
			while (i < size - numsize(*it2))
			{
				std::cout << " ";
				i++;
			}
			it2++;
		}
		std::cout << std::endl;
		it++;
	}
	std::cout << std::endl;
}
*/
void				printPuzzle(t_matrix container)
{
	t_matrix::iterator		it = container.begin();
	int						i;
	int						size;
	int						y;

	y = 0;
	std::cout << "\033[1;33m" << "   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18" << "\033[0m" << std::endl;
	size = numsize(container.size() * container.size());
	while (it != container.end())
	{
		std::cout << "\033[1;33m" << y << "\033[0m";
		y < 10 ? std::cout << "  " : std::cout << " ";
		y++;
		t_matrixLine::iterator		it2 = (*it).begin();
		while (it2 != (*it).end())
		{
			if ((*it2) == 1)
				std::cout << "\033[1;31m";
			if ((*it2) == 2)
				std::cout << "\033[1;32m";
			std::cout << (*it2) << " " << "\033[0m";
			i = 0;
			while (i < size - numsize(*it2))
			{
				std::cout << " ";
				i++;
			}
			it2++;
		}
		std::cout << std::endl;
		it++;
	}
	std::cout << std::endl;
}
