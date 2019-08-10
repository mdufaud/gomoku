/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_media.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 17:30:13 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/17 16:28:08 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"

bool	load_media(SDL_Surface **media, std::string filename)
{
	if (!(*media = SDL_LoadBMP(filename.c_str())))
	{
		sdl_error("Media could not be loaded !");
		return (false);
	}
	return (true);
}

SDL_Surface		*load_media(std::string filename)
{
	SDL_Surface		*media;

	media = NULL;
	if (!(media = SDL_LoadBMP(filename.c_str())))
	{
		sdl_error("Media could not be loaded !");
		return (NULL);
	}
	return (media);
}
