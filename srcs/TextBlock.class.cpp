/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextBlock.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:57:26 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/17 19:13:43 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TextBlock.class.hpp"
#include "Graph.class.hpp"

TextBlock::TextBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string text): ABlock(graph, blockDef, text)
{
	_type = TEXTBLOCK_TYPE;
}


TextBlock::TextBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string text,
					SDL_Rect & messageDef): ABlock(graph, blockDef, text, messageDef)
{
	_type = TEXTBLOCK_TYPE;
}

TextBlock::TextBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string text,
					std::string background): ABlock(graph, blockDef, text, background)
{
	_type = TEXTBLOCK_TYPE;
}

TextBlock::~TextBlock()
{
}

bool	TextBlock::action(int x, int y)
{
	(void)x;
	(void)y;
	return (false);
}

TextBlock		*TextBlock::operator=(TextBlock *rhs)
{
	ABlock::operator=(rhs);
	if (this != rhs)
	{
	}
	return (this);
}

void	TextBlock::draw()
{
	if (_background)
		SDL_RenderCopy(_graph->getRenderer(), _backgroundTexture, NULL, &_backgroundRect);
	if (!_text.empty())
		SDL_RenderCopy(_graph->getRenderer(), _messageTexture, NULL, &_messageRect);
}
