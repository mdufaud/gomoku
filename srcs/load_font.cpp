/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_font.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 16:20:09 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/17 16:27:41 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"

TTF_Font		*load_font(std::string path, int size)
{
	TTF_Font		*font;

	font = NULL;
	if (!(font = TTF_OpenFont(path.c_str(), size)))
	{
		sdl_error("Could not load font " + path);
		return (NULL);
	}
	return (font);
}
