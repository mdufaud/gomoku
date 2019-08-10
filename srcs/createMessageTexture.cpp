/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createMessageTexture                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"

SDL_Texture	*createMessageTexture(std::string text,
									SDL_Renderer *renderer,
									TTF_Font *font,
									SDL_Color color)
{
	SDL_Surface	*tmpSurface;
	SDL_Texture	*retTexture;

	if (text.empty())
		return (NULL);
	if (!(tmpSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color)))
	{
		sdl_error("Could not load surface");
		return (NULL);
	}
	if (!(retTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface)))
	{
		sdl_error("Could not load texture");
		SDL_FreeSurface(tmpSurface);
		return (NULL);
	}
	SDL_FreeSurface(tmpSurface);
	return (retTexture);
}
