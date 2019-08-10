/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pixel.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 20:27:47 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/17 20:30:09 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"

void	set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
	*(Uint32 *)target_pixel = pixel;
}
