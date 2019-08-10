/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_surface.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 17:31:48 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/15 16:57:51 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"
#include "Graph.class.hpp"

void	apply_surface(int x, int y, int x2, int y2, SDL_Surface *src, SDL_Surface *dest)
{
	SDL_Rect	offset;
	SDL_Rect	offset_src;

	offset.x = x;
	offset.y = y;
	offset_src.w = x2;
	offset_src.h = y2;
	SDL_BlitSurface(src, &offset_src, dest, &offset);
}

void	apply_surface(int x, int y, SDL_Surface *src, SDL_Surface *dest)
{
	SDL_Rect	offset;

	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, dest, &offset);
}


void	apply_surface(Graph *graph, SDL_Texture *text, SDL_Rect *src, SDL_Rect *dst)
{
	if (!text)
		SDL_RenderCopy(graph->getRenderer(), graph->getTexture(), src, dst);
	else
		SDL_RenderCopy(graph->getRenderer(), text, src, dst);
}
