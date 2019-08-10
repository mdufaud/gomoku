/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 20:28:19 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/17 20:30:00 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"

void	draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel)
{
	// if the first pixel in the screen is represented by (0,0) (which is in sdl)
	// remember that the beginning of the circle is not in the middle of the pixel
	// but to the left-top from it:
 
	double error = (double)-radius;
	double x = (double)radius -0.5;
	double y = (double)0.5;
	double cx = n_cx - 0.5;
	double cy = n_cy - 0.5;
 
	while (x >= y)
	{
		set_pixel(surface, (int)(cx + x), (int)(cy + y), pixel);
		set_pixel(surface, (int)(cx + y), (int)(cy + x), pixel);
 
		if (x != 0)
		{
			set_pixel(surface, (int)(cx - x), (int)(cy + y), pixel);
			set_pixel(surface, (int)(cx + y), (int)(cy - x), pixel);
		}
 
		if (y != 0)
		{
			set_pixel(surface, (int)(cx + x), (int)(cy - y), pixel);
			set_pixel(surface, (int)(cx - y), (int)(cy + x), pixel);
		}
 
		if (x != 0 && y != 0)
		{
			set_pixel(surface, (int)(cx - x), (int)(cy - y), pixel);
			set_pixel(surface, (int)(cx - y), (int)(cy - x), pixel);
		}
 
		error += y;
		++y;
		error += y;
 
		if (error >= 0)
		{
			--x;
			error -= x;
			error -= x;
		}
	}
}
