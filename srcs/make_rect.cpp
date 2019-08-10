/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_rect.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 16:29:26 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/15 16:30:14 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"

SDL_Rect		make_rect(int x, int y, int w, int h)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}
