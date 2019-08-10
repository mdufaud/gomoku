/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_close.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 17:31:22 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/10 17:31:35 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gomoku.hpp"

void	sdl_close(SDL_Window *window)
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}
