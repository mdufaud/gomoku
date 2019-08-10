/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_image.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 14:54:39 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/17 19:07:24 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"
#include "SDL2/SDL2_rotozoom.h"

SDL_Surface		*resize_image(SDL_Surface *src, int new_w, int new_h)
{
	double	w;
	double	h;
	int		is_smooth;

	is_smooth = 0;
	w = new_w / src->w;
	h = new_h / src->h;
	return (rotozoomSurface(src, 0.5, 0.5, is_smooth));
}
