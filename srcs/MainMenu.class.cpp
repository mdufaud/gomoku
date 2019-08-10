/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainMenu.class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:26:05 by mdufaud           #+#    #+#             */
/*   Updated: 2016/04/28 18:42:06 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MainMenu.class.hpp"
#include "MenuBlock.class.hpp"
#include "TextBlock.class.hpp"
#include "GameInterface.class.hpp"
#include "Graph.class.hpp"

MainMenu::MainMenu(Graph *graph) : AInterface(graph, GOMOKU_MAIN_MENU)
{
	generateBlocks();
}

MainMenu::~MainMenu()
{
}

void	MainMenu::generateBlocks(void)
{
	SDL_Rect		tmpRect;
	std::string		name;
	int				y;
	int				x;
	int				w;
	int				h;

	if (_blocks)
		this->deleteBlocks();
	_blocks = new Blocklist();

	y = 10;
	x = 10;
	w = _graph->getW() - 2 * x;

	name = "Gomoku";
	h = _graph->getH() / 3;
	tmpRect = make_rect(x, y, w, h);
	ABlock	*header= new TextBlock(_graph, tmpRect, name, BACKGROUND_BMP);
	header->setFontID(HEADER_FONT);
	header->setFontStyle(TTF_STYLE_BOLD);
	_blocks->push_back(header);

	w = _graph->getW() / 4;
	x = _graph->getW() / 2 - w / 2;
	y += _graph->getH() / 3 + _graph->getH() / 10 + 20;

	name = "Play";
	h = _graph->getH() / 10;
	tmpRect = make_rect(x, y, w, h);
	ABlock *play = new MenuBlock(_graph, tmpRect, name, BACKGROUND_BMP, GOMOKU_PLAYER_SELECT);
	_blocks->push_back(play);

	y += 20 + h;

	name = "Hotseat";
	h = _graph->getH() / 10;
	tmpRect = make_rect(x, y, w, h);
	ABlock *hotseat = new MenuBlock(_graph, tmpRect, name, BACKGROUND_BMP, GOMOKU_HOTSEAT);
	_blocks->push_back(hotseat);

	y += 20 + h;

	name = "Configuration";
	h = _graph->getH() / 10;
	tmpRect = make_rect(x, y, w, h);
	ABlock *config = new MenuBlock(_graph, tmpRect, name, BACKGROUND_BMP, GOMOKU_CONFIG_MENU);
	_blocks->push_back(config);

	y += 20 + h;

	name = "Exit";
	h = _graph->getH() / 10;
	tmpRect = make_rect(x, y, w, h);
	ABlock *exit = new MenuBlock(_graph, tmpRect, name, BACKGROUND_BMP, GOMOKU_NO_MENU);
	_blocks->push_back(exit);

	exit->setClockBlock(config, NULL, play, NULL);
	config->setClockBlock(hotseat, NULL, exit, NULL);
	hotseat->setClockBlock(play, NULL, config, NULL);
	play->setClockBlock(exit, NULL, hotseat, NULL);
}

void	MainMenu::recalc_draw(void)
{
	generateBlocks();
}
