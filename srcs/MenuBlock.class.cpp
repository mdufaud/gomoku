/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MenuBlock.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:34:52 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/17 19:13:29 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MenuBlock.class.hpp"
#include "Graph.class.hpp"

MenuBlock::MenuBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string title,
					int interfaceNumChangeChange): ABlock(graph, blockDef, title)
{
	_interfaceNumChange = interfaceNumChangeChange;
	_selectable = true;
	_type = MENUBLOCK_TYPE;
}

MenuBlock::MenuBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string title,
					SDL_Rect & messageDef,
					int interfaceNumChangeChange): ABlock(graph, blockDef, title, messageDef)
{
	_selectable = true;
	_interfaceNumChange = interfaceNumChangeChange;
	_type = MENUBLOCK_TYPE;
}

MenuBlock::MenuBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string title,
					std::string background,
					int interfaceNumChangeChange): ABlock(graph, blockDef, title, background)
{
	_selectable = true;
	_interfaceNumChange = interfaceNumChangeChange;
	_type = MENUBLOCK_TYPE;
}

MenuBlock::MenuBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string title,
					SDL_Rect & messageDef,
					std::string background,
					int interfaceNumChangeChange): ABlock(graph, blockDef, title, messageDef, background)
{
	_selectable = true;
	_interfaceNumChange = interfaceNumChangeChange;
	_type = MENUBLOCK_TYPE;
}

MenuBlock::~MenuBlock()
{
}

MenuBlock		*MenuBlock::operator=(MenuBlock *rhs)
{
	ABlock::operator=(rhs);
	if (this != rhs)
	{
		_interfaceNumChange = rhs->getInterfaceNum();
	}
	return (this);
}

int				MenuBlock::getInterfaceNum(void) const
{
	return (this->_interfaceNumChange);
}

bool			MenuBlock::action(int x, int y)
{
	(void)x;
	(void)y;
	_graph->setInterface(_graph->getMenu(_interfaceNumChange));
	return (true);
}

void			MenuBlock::draw()
{
	if (_background)
	{
		SDL_RenderCopy(_graph->getRenderer(), _backgroundTexture, NULL, &_backgroundRect);
		if (_hoovered || _selected)
		{
			SDL_Rect tmp = {_backgroundRect.x - 1,
										_backgroundRect.y - 1,
										_backgroundRect.w + 2,
										_backgroundRect.h + 2};
			SDL_SetRenderDrawColor(_graph->getRenderer(), 0xFF, 0xFF, 0xFF, 0x00);
			SDL_RenderDrawRect(_graph->getRenderer(), &tmp); 
			if (_selected && _hoovered)
			{
				SDL_Rect tmp = {_backgroundRect.x - 2,
											_backgroundRect.y - 2,
											_backgroundRect.w + 4,
											_backgroundRect.h + 4};
				SDL_SetRenderDrawColor(_graph->getRenderer(), 0xFF, 0xFF, 0xFF, 0x00);
				SDL_RenderDrawRect(_graph->getRenderer(), &tmp); 
			}
		}
	}
	if (!_text.empty())
		SDL_RenderCopy(_graph->getRenderer(), _messageTexture, NULL, &_messageRect);
}
