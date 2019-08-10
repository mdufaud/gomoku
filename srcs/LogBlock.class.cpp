/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogBlock.class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LogBlock.class.hpp"
#include "Graph.class.hpp"

LogBlock::LogBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string name): ABlock(graph, blockDef, name)
{
	_type = LOGBLOCK_TYPE;
	_scrollY = 0;
	_scrollX = 0;
	_textX = 0;
	_textY = 0;
	_scrollLog = 0;
}

LogBlock::LogBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string name,
					std::string background): ABlock(graph, blockDef, name, background)
{
	_type = LOGBLOCK_TYPE;
	_scrollY = 0;
	_scrollX = 0;
	_textX = 45;
	_textY = 45;
	_scrollLog = 0;
}

LogBlock::~LogBlock()
{
}

void	LogBlock::scrollLogUp(void)
{
	int		size = _tList.size();

	if (_scrollLog + 1 < size)
		_scrollLog += 1;
}

void	LogBlock::scrollLogDown(void)
{
	if (_scrollLog - 1 >= 0)
		_scrollLog -= 1;
}

void	LogBlock::endIt(void)
{
	textListIt	it = _tList.begin();
	SDL_Texture	*toDestroy;

	while (it != _tList.end())
	{
		toDestroy = *it;
		it++;
		SDL_DestroyTexture(toDestroy);
	}
	_tList.clear();
	_scrollLog = 0;
}

void	LogBlock::addLog(std::string s)
{
	SDL_Texture							*tx;
	SDL_Rect							r;
	std::vector<std::string>			v = split(s, '\n');
	std::vector<std::string>::iterator	it	= v.begin();

	while (it != v.end())
	{
		tx = NULL;
		if (!(*it).empty())
		{
			this->setMessage(&tx, (*it), &r);
			_tList.push_front(tx);
			_rList.push_front(r);
		}
		it++;
	}
}

bool	LogBlock::action(int x, int y)
{
	(void)x;
	(void)y;

	return (false);
}

void	LogBlock::draw()
{
	int			x;
	int			y;
	int			i;
	textListIt	tit = _tList.begin();
	rectListIt	rit = _rList.begin();

	if (_background)
		SDL_RenderCopy(_graph->getRenderer(), _backgroundTexture, NULL, &_backgroundRect);
	i = 0;
	while (i < _scrollLog && tit != _tList.end() && rit != _rList.end())
	{
		i++;
		tit++;
		rit++;
	}
	i = 1;
	while (i - 1 < NOL && tit != _tList.end() && rit != _rList.end())
	{
		y = (_backgroundRect.y + _backgroundRect.h - _textY) - ((rit->h + 3) * i);
		x = _backgroundRect.x + _textX;
		rit->x = x;
		rit->y = y;
		SDL_RenderCopy(_graph->getRenderer(), (*tit), NULL, &(*rit));
		tit++;
		rit++;
		i++;
	}
}

void		LogBlock::scrollUp(void)
{
	int		y;

	y = 10;
	if (_scrollY < 0)
	{
		y = MIN(-_scrollY, y);
		_scrollY += y;
		_backgroundRect.y += y;
	}
}

void		LogBlock::scrollDown(void)
{
	int		y;

	y = 10;
	if (_backgroundRect.y + _backgroundRect.h > _graph->getH())
	{
		y = MIN(_backgroundRect.y + _backgroundRect.h - (_graph->getH()), y);
		_scrollY -= y;
		_backgroundRect.y -= y;
	}
}

void	LogBlock::scrollLeft(void)
{
	int		x;

	x = 10;
	if (_scrollX < 0)
	{
		x = MIN(-_scrollX, x);
		_scrollX += x;
		_backgroundRect.x += x;
	}
}

void	LogBlock::scrollRight(void)
{
	int		x;

	x = 10;
	if (_backgroundRect.x + _backgroundRect.w > _graph->getW())
	{
		x = MIN(_backgroundRect.x + _backgroundRect.w - (_graph->getW()), x);
		_scrollX -= x;
		_backgroundRect.x -= x;
	}
}
