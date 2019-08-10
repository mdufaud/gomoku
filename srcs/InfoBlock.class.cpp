/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InfoBlock.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:57:26 by mdufaud           #+#    #+#             */
/*   Updated: 2016/04/28 18:09:52 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InfoBlock.class.hpp"
#include "LogBlock.class.hpp"
#include "Graph.class.hpp"
#include "Player.class.hpp"
#include <ctime>

InfoBlock::InfoBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string name,
					std::string background
					): ABlock(graph, blockDef, name, background)
{
	_countTime = true;
	_type = INFOBLOCK_TYPE;
	_turnTexture = NULL;
	_timeTexture = NULL;
	_playerOneNameTexture = NULL;
	_playerTwoNameTexture = NULL;
	_playerOneCoupsTexture = NULL;
	_playerTwoCoupsTexture = NULL;
	_playerOneCapsTexture = NULL;
	_playerTwoCapsTexture = NULL;
	_playerTurn = NULL;
	_errorTexture = NULL;
	_warningTexture = NULL;
	_whitePawnTexture = SDL_CreateTextureFromSurface(_graph->getRenderer(),
										_graph->getSurface(INFO_WHITE_PAWN_BMP));
	_blackPawnTexture = SDL_CreateTextureFromSurface(_graph->getRenderer(),
										_graph->getSurface(INFO_BLACK_PAWN_BMP));
	_pawnRect.w = _graph->getSurface(GO_BLACK_PAWN_BMP)->w;
	_pawnRect.h = _graph->getSurface(GO_BLACK_PAWN_BMP)->h;
	_errorRect = make_rect(0, 0, 0, 0);
	_warningRect = make_rect(0, 0, 0, 0);
	_playerOneThinkingTexture = NULL;
	_playerOneThinkingRect = make_rect(0, 0, 0, 0);
	_playerTwoThinkingTexture = NULL;
	_playerTwoThinkingRect = make_rect(0, 0, 0, 0);
	_playerOneThinkTimeTexture = NULL;
	_playerOneThinkTimeRect = make_rect(0, 0, 0, 0);
	_playerTwoThinkTimeTexture = NULL;
	_playerTwoThinkTimeRect = make_rect(0, 0, 0, 0);
	_playerOneThinking = false;
	_playerTwoThinking = false;
	_playerThinkDot = -1;
	_scrollY = 0;
	_scrollX = 0;
	_backRect = _backgroundRect;
	_backgroundRect.x += 40;
	_backgroundRect.y += 40;
	_backgroundRect.w -= 80;
	_backgroundRect.h -= 80;
}

InfoBlock::~InfoBlock()
{
	//DESTROY TEXTURE PLOX
}

void			InfoBlock::startInfos(Player *player1, Player *player2, Player *playerTurn)
{
	this->setPlayer(player1);
	this->setPlayer(player2);
	this->setPlayerTurn(playerTurn);
	this->setBegin(time(0));
	this->setTime();
	this->setCoups(player1);
	this->setCoups(player2);
	this->setCaps(player1);
	this->setCaps(player2);
	this->setInfosPlace();
}

void			InfoBlock::setPlayerThinking(Player *player, bool b)
{
	if (player->getNum() == 1)
		_playerOneThinking = b;
	else
		_playerTwoThinking = b;
	_playerThinkDot = -1;
}

void			InfoBlock::playerThinkDot(void)
{
	int				t;
	std::string		s;

	if (_playerTwoThinking)
	{
		t = time(0) % 3;
		if (_playerThinkDot < 0)
			_playerThinkDot = t;
		s = std::string(" is thinking");
		while (t >= 0)
		{
			s += std::string(".");
			t--;
		}
		s = _player2->getName() + s;
		this->setMessage(&_playerTwoThinkingTexture, s, &_playerTwoThinkingRect);
	}
	if (_playerOneThinking)
	{
		t = time(0) % 3;
		if (_playerThinkDot < 0)
			_playerThinkDot = t;
		s = std::string(" is thinking");
		while (t >= 0)
		{
			s += std::string(".");
			t--;
		}
		s = _player1->getName() + s;
		this->setMessage(&_playerOneThinkingTexture, s, &_playerOneThinkingRect);
	}
}

void			InfoBlock::setPlayer(Player *player)
{
	if (player->getNum() == 1)
	{
		_player1 = player;
		this->setMessage(&_playerOneNameTexture, player->getName(), &_playerOneNameRect);
		if (_playerOneThinkTimeTexture)
			SDL_DestroyTexture(_playerOneThinkTimeTexture);
		_playerOneThinkTimeTexture = NULL;
	}
	if (player->getNum() == 2)
	{
		_player2 = player;
		this->setMessage(&_playerTwoNameTexture, player->getName(), &_playerTwoNameRect);
		if (_playerTwoThinkTimeTexture)
			SDL_DestroyTexture(_playerTwoThinkTimeTexture);
		_playerTwoThinkTimeTexture = NULL;
	}
	this->setInfosPlace();
}

void			InfoBlock::setPlayerTurn(Player *player)
{
	std::string		bTurn = "Black's turn";
	std::string		wTurn = "White's turn";

	_playerTurn = player;
	if (player->getNum() == 1)
		this->setMessage(&_turnTexture, bTurn, &_turnRect);
	if (player->getNum() == 2)
		this->setMessage(&_turnTexture, wTurn, &_turnRect);
	this->setCoups(_player1);
	this->setCaps(_player1);
	this->setCoups(_player2);
	this->setCaps(_player2);
	if (_playerOneThinkTimeTexture && _playerTurn == _player1)
	{
		SDL_DestroyTexture(_playerOneThinkTimeTexture);
		_playerOneThinkTimeTexture = NULL;
	}
	if (_playerTwoThinkTimeTexture && _playerTurn == _player2)
	{
		SDL_DestroyTexture(_playerTwoThinkTimeTexture);
		_playerTwoThinkTimeTexture = NULL;
	}
	_playerOneThinking = false;
	_playerTwoThinking = false;
	this->setInfosPlace();
}

void			InfoBlock::setCoups(Player *player)
{
	std::string		s = "Number of moves: " + to_string(player->getNbCoups());

	if (player->getNum() == 1)
		this->setMessage(&_playerOneCoupsTexture, s, &_playerOneCoupsRect);
	if (player->getNum() == 2)
		this->setMessage(&_playerTwoCoupsTexture, s, &_playerTwoCoupsRect);
	this->setInfosPlace();
}

void			InfoBlock::setCaps(Player *player)
{
	std::string		s = "Number of captures: " + to_string(player->getCap());

	if (player->getNum() == 1)
		this->setMessage(&_playerOneCapsTexture, s, &_playerOneCapsRect);
	if (player->getNum() == 2)
		this->setMessage(&_playerTwoCapsTexture, s, &_playerTwoCapsRect);
	this->setInfosPlace();
}

void			InfoBlock::setPlayerThinkTime(Player *player, double timeElapsed)
{
	if (!timeElapsed)
		timeElapsed = 0.001;
	std::string		s = player->getName() + std::string(": ") + to_string(timeElapsed) + std::string("s");

	if (player->getNum() == 1)
		this->setMessage(&_playerOneThinkTimeTexture, s, &_playerOneThinkTimeRect);
	else
		this->setMessage(&_playerTwoThinkTimeTexture, s, &_playerTwoThinkTimeRect);
}

void			InfoBlock::setBegin(time_t start)
{
	_start = start;
	_countTime = true;
}

void			InfoBlock::startTime()
{
	_countTime = true;
}

void			InfoBlock::stopTime()
{
	_countTime = false;
}

void			InfoBlock::setTime(void)
{
	double		secondsSinceStart;
	int			minutes;
	int			seconds;
	std::string	s = "Time : ";

	if (!_countTime)
		return ;
	secondsSinceStart = difftime(time(0), _start);
	seconds = (int)secondsSinceStart % 60;
	minutes = 0;
	if ((int)secondsSinceStart >= 60)
		minutes = (int)secondsSinceStart / 60;
	s += to_string(minutes) + "m, " + to_string(seconds) + "s";
	this->setMessage(&_timeTexture, s, &_timeRect);
	this->setInfosPlace();
}

void			InfoBlock::emptyWarning(void)
{
	if (_warningTexture)
	{
		_warningRect = make_rect(0, 0, 0, 0);
		SDL_DestroyTexture(_warningTexture);
		_warningTexture = NULL;
		this->setInfosPlace();
	}
}

void			InfoBlock::setWarning(std::string warning)
{
	std::string	s = std::string("Warning: ") + warning;

	this->setMessage(&_errorTexture, warning, &_errorRect);
	this->setInfosPlace();
}

void			InfoBlock::emptyError(void)
{
	if (_errorTexture)
	{
		_errorRect = make_rect(0, 0, 0, 0);
		SDL_DestroyTexture(_errorTexture);
		_errorTexture = NULL;
		this->setInfosPlace();
	}
}

void			InfoBlock::setError(std::string error)
{
	std::string	s = std::string("Error: ") + error;

	this->setMessage(&_errorTexture, s, &_errorRect);
	this->setInfosPlace();
}

void			InfoBlock::setInfosPlace(void)
{
	int			x;
	int			y;
	int			h;

	//Name
	//y += _playerOneRect.h + 10;
	y = 40 + _scrollY;
	x = _backgroundRect.x + _backgroundRect.w / 2 - _playerOneNameRect.w / 2;
	_playerOneNameRect.x = x;
	_playerOneNameRect.y = y;

	//Coups
	y += _playerOneNameRect.h + 10;
	x = _backgroundRect.x + _backgroundRect.w / 2 - _playerOneCoupsRect.w / 2;
	_playerOneCoupsRect.x = x;
	_playerOneCoupsRect.y = y;

	//Caps
	y += _playerOneCoupsRect.h + 10;
	x = _backgroundRect.x + _backgroundRect.w / 2 - _playerOneCapsRect.w / 2;
	_playerOneCapsRect.x = x;
	_playerOneCapsRect.y = y;

	//Player One Rect
	_playerOneRect.y = _playerOneNameRect.y - 10;
	_playerOneRect.h = y + _playerOneCapsRect.h + 20 - _scrollY;
	_playerOneRect.w = _playerOneNameRect.w > _playerOneCoupsRect.w ?
							_playerOneNameRect.w : _playerOneCoupsRect.w;
	_playerOneRect.x = _playerOneNameRect.x < _playerOneCoupsRect.x ?
							_playerOneNameRect.x : _playerOneCoupsRect.x;
	_playerOneRect.w = _playerOneNameRect.w > _playerOneCapsRect.w ?
							_playerOneNameRect.w : _playerOneCapsRect.w;
	_playerOneRect.x = _playerOneNameRect.x < _playerOneCapsRect.x ?
							_playerOneNameRect.x : _playerOneCapsRect.x;
	_playerOneRect.x -= 10;
	_playerOneRect.w += 20;

	//Name
	//y += _playerTwoRect.h + 10;
	y += _playerOneCapsRect.h + 50;
	x = _backgroundRect.x + _backgroundRect.w / 2 - _playerTwoNameRect.w / 2;
	_playerTwoNameRect.x = x;
	_playerTwoNameRect.y = y;

	//Coups
	y += _playerTwoNameRect.h + 10;
	x = _backgroundRect.x + _backgroundRect.w / 2 - _playerTwoCoupsRect.w / 2;
	_playerTwoCoupsRect.x = x;
	_playerTwoCoupsRect.y = y;

	//Caps
	y += _playerTwoCoupsRect.h + 10;
	x = _backgroundRect.x + _backgroundRect.w / 2 - _playerTwoCapsRect.w / 2;
	_playerTwoCapsRect.x = x;
	_playerTwoCapsRect.y = y;

	//Player 2 Rect
	_playerTwoRect.y = _playerTwoNameRect.y - 10;
	_playerTwoRect.h = _playerOneRect.h;
	_playerTwoRect.w = _playerTwoNameRect.w > _playerTwoCoupsRect.w ?
							_playerTwoNameRect.w : _playerTwoCoupsRect.w;
	_playerTwoRect.x = _playerTwoNameRect.x < _playerTwoCoupsRect.x ?
							_playerTwoNameRect.x : _playerTwoCoupsRect.x;
	_playerTwoRect.w = _playerTwoNameRect.w > _playerTwoCapsRect.w ?
							_playerTwoNameRect.w : _playerTwoCapsRect.w;
	_playerTwoRect.x = _playerTwoNameRect.x < _playerTwoCapsRect.x ?
							_playerTwoNameRect.x : _playerTwoCapsRect.x;
	_playerTwoRect.x -= 10;
	_playerTwoRect.w += 20;

	//Error
	y += _playerTwoCapsRect.h + 60;
	x = _backgroundRect.x + _backgroundRect.w / 2 - _errorRect.w / 2;
	_errorRect.x = x;
	_errorRect.y = y;

	h = _errorRect.h ? _errorRect.h : _playerTwoCapsRect.h;

	//Warning
	y += h + 60;
	x = _backgroundRect.x + _backgroundRect.w / 2 - _warningRect.w / 2;
	_warningRect.x = x;
	_warningRect.y = y;

	h = _warningRect.h ? _warningRect.h : h;

	//Player One Thinking
	y += h + 60;
	x = _backgroundRect.x + _backgroundRect.w / 2 - _playerOneThinkingRect.w / 2;
	_playerOneThinkingRect.x = x;
	_playerOneThinkingRect.y = y;

	h = _playerOneThinkingRect.h ? _playerOneThinkingRect.h : h;

	//Player One Think Time
	_playerOneThinkTimeRect.x = x;
	_playerOneThinkTimeRect.y = y;

	h = _playerOneThinkTimeRect.h ? _playerOneThinkTimeRect.h : h;

	//Player Two Thinking
	y += h + 60;
	x = _backgroundRect.x + _backgroundRect.w / 2 - _playerTwoThinkingRect.w / 2;
	_playerTwoThinkingRect.x = x;
	_playerTwoThinkingRect.y = y;

	h = _playerTwoThinkingRect.h ? _playerTwoThinkingRect.h : h;

	//Player Two Think Time
	_playerTwoThinkTimeRect.x = x;
	_playerTwoThinkTimeRect.y = y;

	h = _playerTwoThinkTimeRect.h ? _playerTwoThinkTimeRect.h : h;

	//Time
	y += h + 60;
	x = _backgroundRect.x + _backgroundRect.w / 2 - _timeRect.w / 2;
	_timeRect.x = x;
	_timeRect.y = y;

	//Turn
	y += _timeRect.h + 60;
	x = _backgroundRect.x + _backgroundRect.w / 2 - _turnRect.w / 2;
	_turnRect.x = x;
	_turnRect.y = y;

}

void			InfoBlock::draw()
{
	this->playerThinkDot();
	this->setTime();
	if (_backgroundTexture)
		SDL_RenderCopy(_graph->getRenderer(), _backgroundTexture, NULL, &_backRect);
	SDL_RenderCopy(_graph->getRenderer(), _playerOneNameTexture, NULL, &_playerOneNameRect);
	_pawnRect.y = _playerOneNameRect.y;
	_pawnRect.x = _playerOneNameRect.x - _pawnRect.w - 3;
	SDL_RenderCopy(_graph->getRenderer(), _blackPawnTexture, NULL, &_pawnRect);
	SDL_RenderCopy(_graph->getRenderer(), _playerOneCoupsTexture, NULL, &_playerOneCoupsRect);
	SDL_RenderCopy(_graph->getRenderer(), _playerOneCapsTexture, NULL, &_playerOneCapsRect);

	SDL_RenderCopy(_graph->getRenderer(), _playerTwoNameTexture, NULL, &_playerTwoNameRect);
	_pawnRect.y = _playerTwoNameRect.y;
	_pawnRect.x = _playerTwoNameRect.x - _pawnRect.w - 3;
	SDL_RenderCopy(_graph->getRenderer(), _whitePawnTexture, NULL, &_pawnRect);
	SDL_RenderCopy(_graph->getRenderer(), _playerTwoCoupsTexture, NULL, &_playerTwoCoupsRect);
	SDL_RenderCopy(_graph->getRenderer(), _playerTwoCapsTexture, NULL, &_playerTwoCapsRect);

	if (_errorTexture)
		SDL_RenderCopy(_graph->getRenderer(), _errorTexture, NULL, &_errorRect);

	if (_warningTexture)
		SDL_RenderCopy(_graph->getRenderer(), _warningTexture, NULL, &_warningRect);

	if (_playerOneThinking)
		SDL_RenderCopy(_graph->getRenderer(), _playerOneThinkingTexture, NULL, &_playerOneThinkingRect);
	else if (_playerOneThinkTimeTexture)
		SDL_RenderCopy(_graph->getRenderer(), _playerOneThinkTimeTexture, NULL, &_playerOneThinkTimeRect);

	if (_playerTwoThinking)
		SDL_RenderCopy(_graph->getRenderer(), _playerTwoThinkingTexture, NULL, &_playerTwoThinkingRect);
	else if (_playerTwoThinkTimeTexture)
		SDL_RenderCopy(_graph->getRenderer(), _playerTwoThinkTimeTexture, NULL, &_playerTwoThinkTimeRect);

	SDL_RenderCopy(_graph->getRenderer(), _timeTexture, NULL, &_timeRect);
	SDL_RenderCopy(_graph->getRenderer(), _turnTexture, NULL, &_turnRect);

	_pawnRect.y = _turnRect.y + _turnRect.h + 10; 
	_pawnRect.x = _backgroundRect.x + _backgroundRect.w / 2 - _pawnRect.w / 2; 
	if (_playerTurn->getNum() == 1)
		SDL_RenderCopy(_graph->getRenderer(), _blackPawnTexture, NULL, &_pawnRect);
	if (_playerTurn->getNum() == 2)
		SDL_RenderCopy(_graph->getRenderer(), _whitePawnTexture, NULL, &_pawnRect);
}

void		InfoBlock::scrollUp(void)
{
	int		y;

	y = 10;
	if (_scrollY < 0)
	{
		y = MIN(-_scrollY, y);
		_scrollY += y;
		_backgroundRect.y += y;
		_backRect.y += y;
		this->setInfosPlace();
	}
}

void		InfoBlock::scrollDown(void)
{
	int		y;

	y = 10;
	if (_logBlock->getBackgroundRect().y + _logBlock->getBackgroundRect().h > _graph->getH())
	{
		y = MIN(_logBlock->getBackgroundRect().y + _logBlock->getBackgroundRect().h - (_graph->getH()), y);
		_scrollY -= y;
		_backgroundRect.y -= y;
		_backRect.y -= y;
		this->setInfosPlace();
	}
}

void	InfoBlock::scrollLeft(void)
{
	int		x;

	x = 10;
	if (_scrollX < 0)
	{
		x = MIN(-_scrollX, x);
		_scrollX += x;
		_backgroundRect.x += x;
		_backRect.x += x;
		this->setInfosPlace();
	}
}

void	InfoBlock::scrollRight(void)
{
	int		x;

	x = 10;
	if (_backgroundRect.x + _backgroundRect.w > _graph->getW() - 40)
	{
		x = MIN(_backgroundRect.x + _backgroundRect.w - (_graph->getW() - 40), x);
		_scrollX -= x;
		_backgroundRect.x -= x;
		_backRect.x -= x;
		this->setInfosPlace();
	}
}

void			InfoBlock::setLogBlock(LogBlock *log)
{
	_logBlock = log;
}

bool			InfoBlock::action(int x, int y)
{
	(void)x;
	(void)y;
	return (false);
}
