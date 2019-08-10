/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 17:19:19 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/17 17:39:55 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"
#include <SDL2/SDL_image.h>

SDL_Surface		*load_image(std::string filename)
{
	SDL_Surface	*image;

	image = NULL;
	if (!(image = IMG_Load(filename.c_str())))
		sdl_error("Could not load image " + filename);
	return (image);
}
