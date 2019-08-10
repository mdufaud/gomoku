/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameInterface.class.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 16:15:07 by mdufaud           #+#    #+#             */
/*   Updated: 2016/07/01 16:00:58 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameInterface.class.hpp"
#include "MenuBlock.class.hpp"
#include "TextBlock.class.hpp"
#include "LogBlock.class.hpp"
#include "GameBlock.class.hpp"
#include "InfoBlock.class.hpp"
#include "Graph.class.hpp"
#include "MainMenu.class.hpp"
#include "ConfigMenu.class.hpp"

GameInterface::GameInterface(Graph *graph) : AInterface(graph, GOMOKU_GAME_INTERFACE)
{
	_winTimer = 0;
	generateBlocks();
}

GameInterface::~GameInterface()
{
}

GameBlock	*GameInterface::getGameBlock(void)
{
	Blocklist::iterator	it = _blocks->begin();

	while (it != _blocks->end())
	{
		if ((*it)->getType() == GAMEBLOCK_TYPE)
		{
			GameBlock	*block;

			block = static_cast<GameBlock *>((*it));
			return (block);
		}
		it++;
	}
	return (NULL);
}

void		GameInterface::keyLeft(SDL_Event e)
{
	(void)e;
	_gameBlock->scrollLeft();
	_infoBlock->scrollLeft();
	_logBlock->scrollLeft();
}

void		GameInterface::keyRight(SDL_Event e)
{
	(void)e;
	_gameBlock->scrollRight();
	_logBlock->scrollRight();
	_infoBlock->scrollRight();
}

void		GameInterface::keyDown(SDL_Event e)
{
	(void)e;
	_gameBlock->scrollDown();
	_infoBlock->scrollDown();
	_logBlock->scrollDown();
}

void		GameInterface::keyUp(SDL_Event e)
{
	(void)e;
	_gameBlock->scrollUp();
	_logBlock->scrollUp();
	_infoBlock->scrollUp();
}

void		GameInterface::hideWin(void)
{
	if (_winTimer + 1 < time(0))
	{
		_winBlock->hide(true);
		_retBlock->hide(true);
	}
}

bool		GameInterface::click(int x, int y)
{
	bool					b = AInterface::click(x, y);

	if (_retBlock->isHidden() == false && _retBlock->isInBlock(x, y))
		_retBlock->action(x, y);
	if (_winBlock->isHidden() == false && _winBlock->isInBlock(x, y))
		this->hideWin();
	return (b);
}

void		GameInterface::keyDownEvent(SDL_Event e)
{
	AInterface::keyDownEvent(e);
	switch (e.key.keysym.sym)
	{
		case SDLK_p:
		{
			_gameBlock->autoPlay();
			break ;
		}
		case SDLK_h:
		{
			_gameBlock->activateHelp(4);
			break ;
		}
		case SDLK_i:
		{
			_gameBlock->activateIA();
			break ;
		}
		case SDLK_b:
		{
			_gameBlock->loadPrevState();
			break ;
		}
		case SDLK_n:
		{
			_gameBlock->loadNextState();
			break ;
		}
		case SDLK_PAGEUP:
		{
			_logBlock->scrollLogUp();
			break ;
		}
		case SDLK_PAGEDOWN:
		{
			_logBlock->scrollLogDown();
			break ;
		}
		case SDLK_s:
		{
			_gameBlock->logIaStats();
			break ;
		}
	}
}

void		GameInterface::keyBackspace(SDL_Event e)
{
	(void)e;
	_retBlock->action(0, 0);
	this->hideWin();
}

void	GameInterface::setIA(bool easy, bool medium, bool hard)
{
	if (easy)
		_gameBlock->setIaDepth(3);
	if (medium)
		_gameBlock->setIaDepth(4);
	if (hard)
		_gameBlock->setIaDepth(5);
}

void	GameInterface::startGame(std::string playerOne, std::string playerTwo, bool ia)
{
	_gameBlock->setRule(static_cast<ConfigMenu *>(_graph->getMenu(GOMOKU_CONFIG_MENU))->getRule());
	_gameBlock->init(playerOne, playerTwo);
	_infoBlock->startInfos(_gameBlock->getPlayer(1), _gameBlock->getPlayer(2), _gameBlock->getPlayerTurn());
	_gameBlock->setInfoBlock(_infoBlock);
	_gameBlock->setLogBlock(_logBlock);
	_infoBlock->setLogBlock(_logBlock);
	_logBlock->endIt();
	_gameBlock->start(ia);
}

void	GameInterface::setWinner(int winner)
{
	std::string		s;
	SDL_Rect		rect;

	_winTimer = time(0);
	_infoBlock->stopTime();
	if (winner == 1)
		s = _gameBlock->getPlayer(winner)->getName() + std::string("'s Black Pawns Won !");
	else if (winner == 2)
		s = _gameBlock->getPlayer(winner)->getName() + std::string("'s White Pawns Won !");
	else
		s = std::string("Draw !");
	_gameBlock->selectable(false);
	_winBlock->hide(false);
	_retBlock->hide(false);
	_winBlock->setText(s);
	rect = _winBlock->getMessageRect();
	rect.y -= 30;
	_winBlock->setMessageRect(rect);
}

void	GameInterface::unsetWinner(void)
{
	_infoBlock->startTime();
	_winBlock->hide(true);
	_retBlock->hide(true);
	_gameBlock->selectable(true);
}

void	GameInterface::generateBlocks(void)
{
	SDL_Rect		tmpRect;
	std::string		name;
	int				h;
	int				w;
	int				y;
	int				x;

	if (_blocks)
		this->deleteBlocks();
	_blocks = new Blocklist();

	y = 0;
	x = 0;
	w = 0;
	h = 0;

	name = "Board";
	h = 1000;
	w = 1000;
	tmpRect = make_rect(x, y, w, h);
	ABlock	*board = new GameBlock(_graph, tmpRect, name, GO_BOARD_BMP);
	_gameBlock = static_cast<GameBlock *>(board);
	h = board->getBackgroundRect().h;
	w = board->getBackgroundRect().w;

	name = "Infos";
	x = board->getBackgroundRect().w + 10;
	w = 380;
	h = 1000;
	tmpRect = make_rect(x, y, w, h);
	ABlock	*infos = new InfoBlock(_graph, tmpRect, name, INFO_BLOCK_BMP);
	_infoBlock = static_cast<InfoBlock *>(infos);

	name = "Log";
	x = 0;
	y = h + 10;
	w = 1380;
	h = 350;
	tmpRect = make_rect(x, y, w, h);
	ABlock	*log = new LogBlock(_graph, tmpRect, name, LOG_BLOCK_BMP);
	_logBlock = static_cast<LogBlock *>(log);

	w = _graph->getW() / 3;
	x = _graph->getW() / 2 - w / 2;
	y = _graph->getH() / 2 - _graph->getH() / 5 - 20;
	h = _graph->getH() / 10 + 30;
	name = "Win Message";
	tmpRect = make_rect(x, y, w, h);
	ABlock	*win = new TextBlock(_graph, tmpRect, name, BACKGROUND_BMP);
	_winBlock = static_cast<TextBlock *>(win);
	_winBlock->hide(true);

	y += 80;
	w = _graph->getW() / 5;
	x = _graph->getW() / 2 - w / 2;
	h = 30;
	name = "Return to main menu";
	tmpRect = make_rect(x, y, w, h);
	ABlock	*main = new MenuBlock(_graph, tmpRect, name, tmpRect, GOMOKU_MAIN_MENU);
	_retBlock = static_cast<MenuBlock *>(main);
	_retBlock->hide(true);

	_blocks->push_back(board);
	_blocks->push_back(log);
	_blocks->push_back(infos);
	_blocks->push_back(win);
	_blocks->push_back(main);
}

void	GameInterface::recalc_draw(void)
{
	/*
	Blocklist::iterator	it = _blocks->begin();
	int					x;
	int					h;
	int					w;
	int					y;

	y = 0;
	x = 0;
	w = 0;
	h = 0;
	while (it != _blocks->end())
	{
		(*it)->setBackgroundRect(make_rect(x, y, w, h));
		h = (*it)->getBackgroundRect().h;
		w = (*it)->getBackgroundRect().w;
		x += w + 20;
		it++;
	}
	*/
}

void	GameInterface::loadScenario(int n)
{
	if (n == 1)
	{
		/* PLAY FOR CAPTURE WIN */
		_gameBlock->play(7, 3);
		_gameBlock->play(6, 3);
		_gameBlock->play(7, 4);
		_gameBlock->play(6, 4);
		_gameBlock->play(8, 3);
		_gameBlock->play(4, 3);
		_gameBlock->play(7, 5);
		_gameBlock->play(4, 4);
		_gameBlock->play(7, 6);
		_gameBlock->play(4, 5);
		_gameBlock->play(7, 7);
		_gameBlock->play(3, 2);
		_gameBlock->play(6, 2);
		_gameBlock->play(3, 6);
	}
	if (n == 2)
	{
		/* PLAY FOR UNDO CAPTURE WIN */
		_gameBlock->play(4, 3);
		_gameBlock->play(4, 2);
		_gameBlock->play(5, 4);
		_gameBlock->play(0, 0);
		_gameBlock->play(6, 5);
		_gameBlock->play(0, 1);
		_gameBlock->play(7, 6);
		_gameBlock->play(0, 2);
		_gameBlock->play(4, 4);
		_gameBlock->play(0, 5);
		_gameBlock->play(8, 7);
		_gameBlock->play(0, 6);
	}
	if (n == 3)
	{
		/* PLAY FOR UNDO CAPTURE WIN */
		_gameBlock->play(12, 6);
		_gameBlock->play(14, 7);
		_gameBlock->play(15, 7);
		_gameBlock->play(15, 6);
		_gameBlock->play(13, 8);
		_gameBlock->play(13, 7);
		_gameBlock->play(11, 8);
		_gameBlock->play(12, 7);
		_gameBlock->play(10, 9);
		_gameBlock->play(11, 7);
		_gameBlock->play(9, 7);
		_gameBlock->play(10, 8);
		_gameBlock->play(8, 6);
		_gameBlock->play(9, 9);
		_gameBlock->play(9, 11);
		_gameBlock->play(8, 10);
		_gameBlock->play(10, 11);
		_gameBlock->play(8, 9);
		_gameBlock->play(8, 11);
		_gameBlock->play(8, 8);
		_gameBlock->play(9, 7);
		_gameBlock->play(6, 12);
		_gameBlock->play(7, 11);
		_gameBlock->play(11, 5);
		_gameBlock->play(10, 10);
		_gameBlock->play(10, 4);
		_gameBlock->play(11, 11);
		_gameBlock->play(9, 3);
		_gameBlock->play(12, 12);
		_gameBlock->play(13, 13);
	}
}


