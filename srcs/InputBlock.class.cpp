/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputBlock.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2016/07/01 11:24:31 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InputBlock.class.hpp"
#include "Graph.class.hpp"

InputBlock::InputBlock(Graph *graph,
					SDL_Rect & blockDef): ABlock(graph, blockDef)
{
	_selectable = true;
	_inputTextTexture = NULL;
	_type = INPUTBLOCK_TYPE;
	SDL_SetTextInputRect(&blockDef);
}

InputBlock::InputBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string background): ABlock(graph, blockDef, background)
{
	_selectable = true;
	_inputTextTexture = NULL;
	_type = INPUTBLOCK_TYPE;
	SDL_SetTextInputRect(&blockDef);
}

InputBlock::~InputBlock()
{
}

bool		InputBlock::action(int x, int y)
{
	(void)x;
	(void)y;
	return (false);
}

void		InputBlock::addText(std::string text)
{
	if (text.find_first_not_of(' ') == std::string::npos
		|| text.find_first_not_of('\t') == std::string::npos)
		return ;
	if (_inputText.length() + text.length() > MAX_INPUTS)
		return ;
	_inputText += text;
	if ((TTF_SizeText(_font, _inputText.c_str(), &_inputRect.w, &_inputRect.h) < 0))
		sdl_error("Size Text");
	this->setMessage(&_inputTextTexture, _inputText, &_inputRect);
}

void		InputBlock::backDel(void)
{
	if (_inputText.length() > 0)
	{
		_inputText = _inputText.substr(0, _inputText.length() - 1);
		if (_inputText.empty())
			_inputText = " ";
		this->setMessage(&_inputTextTexture, _inputText, &_inputRect);
	}
}

std::string	InputBlock::getInput(void)
{
	if (_inputText.find_first_not_of(' ') == std::string::npos)
		_inputText = "";
	else if (_inputText.find_first_not_of('\t') == std::string::npos)
		_inputText = "";
	return (_inputText);
}

void		InputBlock::draw()
{
	if (_background)
		SDL_RenderCopy(_graph->getRenderer(), _backgroundTexture, NULL, &_backgroundRect);
	if (!_background || (_background && (_selected || _hoovered)))
	{
		SDL_Rect tmp = {_backgroundRect.x - 1,
						_backgroundRect.y - 1,
						_backgroundRect.w + 2,
						_backgroundRect.h + 2};
		SDL_SetRenderDrawColor(_graph->getRenderer(), 0xFF, 0xFF, 0xFF, 0x00);
		SDL_RenderDrawRect(_graph->getRenderer(), &tmp);
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
	SDL_RenderCopy(_graph->getRenderer(), _inputTextTexture, NULL, &_inputRect);
}

int			InputBlock::selected(void)
{
	SDL_StartTextInput();
	return (ABlock::selected());
}

void		InputBlock::unselect(void)
{
	SDL_StopTextInput();
	ABlock::unselect();
}
