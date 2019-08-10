/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABlock.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 18:30:11 by mdufaud           #+#    #+#             */
/*   Updated: 2016/04/28 18:31:24 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABlock.class.hpp"
#include "Graph.class.hpp"

ABlock::ABlock(Graph *graph, SDL_Rect & blockDef)
{
	this->init(graph, blockDef);
}

ABlock::ABlock(Graph *graph, SDL_Rect & blockDef, std::string text)
{
	this->init(graph, blockDef);
	_text = text;
	this->setMessage();
}

ABlock::ABlock(Graph *graph, SDL_Rect & blockDef, std::string text, SDL_Rect & messageDef)
{
	this->init(graph, blockDef);
	_text = text;
	_messageRect = messageDef;
	this->setMessage();
}

ABlock::ABlock(Graph *graph, SDL_Rect & blockDef, std::string text, std::string background)
{
	this->init(graph, blockDef);
	_text = text;
	this->setMessage();
	this->setBackground(background);
}

ABlock::ABlock(Graph *graph, SDL_Rect & blockDef, std::string text, SDL_Rect & messageDef, std::string background)
{
	this->init(graph, blockDef);
	_text = text;
	_messageRect = messageDef;
	this->setMessage();
	this->setBackground(background);
}

ABlock::ABlock(ABlock *block)
{
	SDL_Rect	rect = block->getBackgroundRect();

	this->init(block->getGraph(), rect);
	_fontID = block->getFontID();
	_messageRect = block->getMessageRect();
	_text = block->getText();
	_color = block->getColor();
	this->setBackground(block->getBackgroundPath());
	this->setMessage();
}

ABlock::~ABlock(void)
{
	if (_messageTexture)
		SDL_DestroyTexture(_messageTexture);
	if (_backgroundTexture)
		SDL_DestroyTexture(_backgroundTexture);
}

void	ABlock::init(Graph *graph, SDL_Rect & blockDef)
{
	_id = _idKey;
	_idKey += 1;

	_graph = graph;
	_backgroundRect = blockDef;

	_selectable = false;
	_type = ABLOCK_TYPE;
	_selected = false;
	_hoovered = false;
	_hidden = false;
	_backgroundTexture = NULL;
	_background = NULL;

	_fontID = MENU_FONT;
	_fontSize = MENU_FONTSIZE;
	_fontStyle = TTF_STYLE_NORMAL;
	_font = NULL;
	_messageTexture = NULL;
	_color.r = 255;
	_color.g = 255;
	_color.b = 255;

	_left = NULL;
	_right = NULL;
	_up = NULL;
	_down = NULL;
}

void	ABlock::setMessageFontRect(std::string & text, TTF_Font *font, SDL_Rect *rect)
{
	if (text.empty())
	{
		rect->x = 0;
		rect->y = 0;
		rect->w = 0;
		rect->h = 0;
		return ;
	}
	if (!font)
		font = _graph->getFont(_fontID);
	if ((TTF_SizeUTF8(font, text.c_str(), &rect->w, &rect->h) < 0))
		sdl_error("Size Text");
	rect->w = rect->w > _backgroundRect.w ? _backgroundRect.w : rect->w;
	rect->h = rect->h > _backgroundRect.h ? _backgroundRect.h : rect->h;
	rect->x = _backgroundRect.x + _backgroundRect.w / 2 - rect->w / 2;
	rect->y = _backgroundRect.y + _backgroundRect.h / 2 - rect->h / 2;
}

void	ABlock::setMessage(SDL_Texture **texture, std::string & text, TTF_Font *font, SDL_Color color)
{
	if (text.empty())
		return ;
	if (!font)
		font = _font;
	if (!font)
		font = _graph->getFont(_fontID);
	if (*texture)
		SDL_DestroyTexture(*texture);
	*texture = createMessageTexture(text, _graph->getRenderer(), font, color);
}

void	ABlock::setMessage(SDL_Texture **texture, std::string & text)
{
	this->setMessage(texture, text, _font, _color);
}

void	ABlock::setMessage(SDL_Texture **texture, std::string & text, TTF_Font *font, SDL_Rect *rect)
{
	this->setMessageFontRect(text, font, rect);
	this->setMessage(texture, text, font, _color);
}

void	ABlock::setMessage(SDL_Texture **texture, std::string & text, SDL_Rect *rect)
{
	this->setMessageFontRect(text, _font, rect);
	this->setMessage(texture, text, _font, _color);
}

void	ABlock::setMessage()
{
	if (_text.empty())
		return ;
	if (!_font)
		_font = _graph->getFont(_fontID);
	if ((TTF_SizeUTF8(_font, _text.c_str(), &_messageRect.w, &_messageRect.h) < 0))
		sdl_error("Size Text");
	_messageRect.w = _messageRect.w > _backgroundRect.w ? _backgroundRect.w : _messageRect.w;
	_messageRect.h = _messageRect.h > _backgroundRect.h ? _backgroundRect.h : _messageRect.h;
	_messageRect.x = _backgroundRect.x + _backgroundRect.w / 2 - _messageRect.w / 2;
	_messageRect.y = _backgroundRect.y + _backgroundRect.h / 2 - _messageRect.h / 2;
	if (_messageTexture)
		SDL_DestroyTexture(_messageTexture);
	_messageTexture = createMessageTexture(_text, _graph->getRenderer(), _font, _color);
}

bool		ABlock::isInBlock(int x, int y)
{
	if (x >= 0 && y >= 0)
	{
		if (x >= _backgroundRect.x && y >= _backgroundRect.y
				&& x <= _backgroundRect.x + _backgroundRect.w
				&& y <= _backgroundRect.y + _backgroundRect.h
				&& _hidden == false)
			return (true);
	}
	return (false);
}

void		ABlock::setBackground(std::string filename)
{
	_backgroundPath = filename;
	if (_backgroundTexture)
	{
		SDL_DestroyTexture(_backgroundTexture);
		_backgroundTexture = NULL;
	}
	_background = _graph->getSurface(filename);
	if (_background)
	{
		if (!(_backgroundTexture = SDL_CreateTextureFromSurface(_graph->getRenderer(), _background)))
			sdl_error("Texture could not be loaded");
	}
}

void	ABlock::setFontID(int font)
{
	_fontID = font;
	_font = _graph->getFont(font);
	this->setMessage();
}

void	ABlock::setMessageRect(SDL_Rect & size)
{
	_messageRect = size;
}

void	ABlock::setMessageColor(int r, int g, int b)
{
	_color.r = r;
	_color.g = g;
	_color.b = b;
	this->setMessage();
}

void	ABlock::setText(std::string text)
{
	this->_text = text;
	this->setMessage();
}

int			ABlock::getID(void) const
{
	return (this->_id);
}

int			ABlock::getType(void) const
{
	return (this->_type);
}

std::string	ABlock::getText(void) const
{
	return (this->_text);
}

int			ABlock::getFontID(void) const
{
	return (this->_fontID);
}

bool		ABlock::isSelected(void) const
{
	return (this->_selected);
}

bool		ABlock::isSelectable(void) const
{
	return (this->_selectable);
}

void		ABlock::selectable(bool b)
{
	_selectable = b;
}

bool		ABlock::isHoovered(void) const
{
	return (this->_hoovered);
}

std::string	ABlock::getBackgroundPath(void) const
{
	return (this->_backgroundPath);
}

SDL_Rect	ABlock::getMessageRect(void) const
{
	return (this->_messageRect);
}

SDL_Color	ABlock::getColor(void) const
{
	return (this->_color);
}

SDL_Rect	ABlock::getBackgroundRect(void) const
{
	return (this->_backgroundRect);
}

Graph		*ABlock::getGraph(void) const
{
	return (this->_graph);
}

int			ABlock::hoovered(void)
{
	this->_hoovered = true;
	return (this->_id);
}

void		ABlock::unhoover(void)
{
	this->_hoovered = false;
}

int			ABlock::selected(void)
{
	if (!_selectable)
		return (-1);
	this->_selected = true;
	return (this->_id);
}

void		ABlock::unselect(void)
{
	this->_selected = false;
}

void		ABlock::setBackgroundRect(SDL_Rect rect)
{
	this->_backgroundRect.x = rect.x;
	this->_backgroundRect.y = rect.y;
	this->_backgroundRect.h = rect.h;
	this->_backgroundRect.w = rect.w;
}

void		ABlock::setFontSize(int size)
{
	this->_fontSize = size;
}

void		ABlock::setFontStyle(int style)
{
	this->_fontStyle = style;
}

void		ABlock::setRightBlock(ABlock *right)
{
	_right = right;
}

void		ABlock::setLeftBlock(ABlock *left)
{
	_left = left;
}

void		ABlock::setDownBlock(ABlock *down)
{
	_down = down;
}

void		ABlock::setUpBlock(ABlock *up)
{
	_up = up;
}

ABlock		*ABlock::getLeftBlock(void) const
{
	return (this->_left);
}

ABlock		*ABlock::getRightBlock(void) const
{
	return (this->_right);
}

ABlock		*ABlock::getDownBlock(void) const
{
	return (this->_down);
}

ABlock		*ABlock::getUpBlock(void) const
{
	return (this->_up);
}

void		ABlock::setClockBlock(ABlock *u, ABlock *r, ABlock *d, ABlock *l)
{
	_up = u;
	_right = r;
	_down = d;
	_left = l;
}

ABlock		*ABlock::operator=(ABlock *rhs)
{
	if (this != rhs)
	{
		SDL_Rect tmp = rhs->getBackgroundRect();
		this->init(rhs->getGraph(), tmp);
		_messageRect = rhs->getMessageRect();
		_text = rhs->getText();
		_fontID = rhs->getFontID();
		_color = rhs->getColor();
		_type = rhs->getType();
		this->setBackground(rhs->getBackgroundPath());
		this->setMessage();
	}
	return (this);
}

bool		ABlock::isHidden(void)
{
	return (_hidden);
}

void		ABlock::hide(bool b)
{
	_hidden = b;
}

std::ostream  &	operator<<(std::ostream  & o, ABlock *rhs)
{
	o << "Block name: "
		<< rhs->getText()
		<< ".";
	return o;
}

int			ABlock::_idKey = 0;
