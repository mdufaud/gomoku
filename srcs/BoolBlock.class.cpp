/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BoolBlock.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BoolBlock.class.hpp"
#include "Graph.class.hpp"

BoolBlock::BoolBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string & text): ABlock(graph, blockDef, text)
{
	_selectable = true;
	_bool = true;
	_boolTexture = NULL;
	_boolRect = make_rect(0, 0, 0, 0);
	this->setBool();
	_type = BOOLBLOCK_TYPE;
}

BoolBlock::BoolBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string & text,
					std::string background): ABlock(graph, blockDef, text, background)
{
	_selectable = true;
	_bool = true;
	_boolTexture = NULL;
	_boolRect = make_rect(0, 0, 0, 0);
	this->setBool();
	_type = BOOLBLOCK_TYPE;
}

BoolBlock::~BoolBlock()
{
}

void		BoolBlock::setBool()
{
	std::string	s;

	_bool = _bool == false ? true : false;
	if (_bool)
		s = std::string("[X] ") + _text;
	else
		s = std::string("[ ] ") + _text;
	this->setMessage(&_boolTexture, s, &_boolRect);
}

void		BoolBlock::setBool(bool b)
{
	std::string	s;

	_bool = b;
	if (b)
		s = std::string("[X] ") + _text;
	else
		s = std::string("[ ] ") + _text;
	this->setMessage(&_boolTexture, s, &_boolRect);
}

bool		BoolBlock::action(int x, int y)
{
	this->setBool();
	(void)x;
	(void)y;
	return (false);
}

bool		BoolBlock::getBool(void)
{
	return (_bool);
}

void		BoolBlock::draw()
{
	if (_background)
		SDL_RenderCopy(_graph->getRenderer(), _backgroundTexture, NULL, &_backgroundRect);
	if (!_background || (_background && (_selected || _hoovered)))
	{
		if (_selected || _hoovered)
		{
			SDL_Rect tmp = {_backgroundRect.x - 2,
							_backgroundRect.y - 2,
							_backgroundRect.w + 4,
							_backgroundRect.h + 4};
			SDL_SetRenderDrawColor(_graph->getRenderer(), 0xFF, 0xFF, 0xFF, 0x00);
			SDL_RenderDrawRect(_graph->getRenderer(), &tmp);
		}
		if (_selected && _hoovered)
		{
			SDL_Rect tmp = {_backgroundRect.x - 3,
							_backgroundRect.y - 3,
							_backgroundRect.w + 6,
							_backgroundRect.h + 6};
			SDL_SetRenderDrawColor(_graph->getRenderer(), 0xFF, 0xFF, 0xFF, 0x00);
			SDL_RenderDrawRect(_graph->getRenderer(), &tmp);
		}
	}
	SDL_RenderCopy(_graph->getRenderer(), _boolTexture, NULL, &_boolRect);
}

int			BoolBlock::selected(void)
{
	return (ABlock::selected());
}

void		BoolBlock::unselect(void)
{
	ABlock::unselect();
}
