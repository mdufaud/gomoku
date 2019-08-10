/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 17:29:32 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/15 19:25:00 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"

bool	init(SDL_Window **window)
{
	bool	success = true;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		sdl_error("SDL could not initialize !");
		success = false;
	}
	else
	{
		*window = SDL_CreateWindow("Gomoku",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				W_WIDTH,
				W_HEIGHT,
				SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (*window == NULL)
		{
			sdl_error("Window could not be created !");
			success = false;
		}
	}
	return (success);
}
