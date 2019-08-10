/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_error.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 17:30:39 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/10 17:30:51 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"

void	sdl_error(std::string message)
{
	std::cout << message << " SDL_ERROR: " << SDL_GetError() << std::endl;
}
