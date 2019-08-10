/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Board.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:04:40 by rcherik           #+#    #+#             */
/*   Updated: 2016/04/28 18:07:51 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Board.class.hpp"
#include "gomoku.hpp"

Board::Board(void)
{
	_nPawns = 0;
	_win = 0;
}

Board::Board(Rules *rule) : _rule(rule)
{
	t_matrix		board(19, t_matrixLine(19));

	_board = board;
	_win = 0;
	_lastPlayP1 = playPair(-1, -1);
	_lastPlayP2 = playPair(-1, -1);
	_boardValueP1 = 0;
	_boardValueP2 = 0;
	_heuristic = 0;
	_clear = true;
	_nPawns = 0;
}

Board::Board(Board & rhs)
{
	this->_rule = rhs.getRule();
	this->_win = rhs.getWinner();
	this->_board = rhs.getBoard();
	this->_lastPlayP1 = rhs.getLastPlayP1();
	this->_lastPlayP2 = rhs.getLastPlayP2();
	this->_boardValueP1 = rhs.getBoardValueP1();
	this->_boardValueP2 = rhs.getBoardValueP2();
	this->_heuristic = rhs.getHeuristic();
	this->_clear = rhs.getClear();
	this->_nPawns = rhs.getPawns();
}

Board::~Board(void)
{
}

Board &		Board::operator=(Board & rhs)
{
	if (this != &rhs)
	{
		this->_rule = rhs.getRule();
		this->_win = rhs.getWinner();
		this->_board = rhs.getBoard();
		this->_lastPlayP1 = rhs.getLastPlayP1();
		this->_lastPlayP2 = rhs.getLastPlayP2();
		this->_boardValueP1 = rhs.getBoardValueP1();
		this->_boardValueP2 = rhs.getBoardValueP2();
		this->_heuristic = rhs.getHeuristic();
		this->_clear = rhs.getClear();
		this->_nPawns = rhs.getPawns();
	}
	return (*this);
}

Board &		Board::operator=(Board const & rhs)
{
	if (this != &rhs)
	{
		this->_rule = rhs.getRule();
		this->_win = rhs.getWinner();
		this->_board = rhs.getBoard();
		this->_lastPlayP1 = rhs.getLastPlayP1();
		this->_lastPlayP2 = rhs.getLastPlayP2();
		this->_boardValueP1 = rhs.getBoardValueP1();
		this->_boardValueP2 = rhs.getBoardValueP2();
		this->_heuristic = rhs.getHeuristic();
		this->_clear = rhs.getClear();
	}
	return (*this);
}

bool				Board::valid(int x, int y, Player *player)
{
	if (_win > 0)
		return (false);
	_playerNum = player->getNum();
	_otherPlayerNum = _playerNum == 1 ? 2 : 1;
	this->_rule->emptyInfo();
	this->_rule->emptyWarning();
	this->_rule->emptyError();
	if (!this->_rule->validPlay(x, y, this->_board, player))
		return (false);
	return (true);
}

bool				Board::playNoVerif(int x, int y, Player *player)
{
	this->_board[y][x] = player->getNum();
	_nPawns += 1;
	player->incNbCoups();
	if (_clear)
		_clear = false;
	if (player->getNum() == 1)
	{
		_lastPlayP1 = playPair(x, y);
		_boardValueP1 += this->_rule->heuristic(this, x, y, player);
	}
	else
	{
		_lastPlayP2 = playPair(x, y);
		_boardValueP2 += this->_rule->heuristic(this, x, y, player);
	}
	if (_nPawns >= 361)
		_win = 3;
	return (true);
}

bool				Board::play(int x, int y, Player *player)
{
	bool	b;

	b = this->valid(x, y, player);
	if (b)
		b = this->playNoVerif(x, y, player);
	return (b);
	/*
	if (_win > 0)
		return (false);
	_playerNum = player->getNum();
	_otherPlayerNum = _playerNum == 1 ? 2 : 1;
	this->_rule->emptyWarning();
	this->_rule->emptyError();
	//debugs("Valid Play");
	if (!this->_rule->validPlay(x, y, this->_board, player))
		return (false);
	this->_board[y][x] = player->getNum();
	player->incNbCoups();
	if (_clear)
		_clear = false;
	//debugs("Heur");
	if (player->getNum() == 1)
	{
		_lastPlayP1 = playPair(x, y);
		_boardValueP1 += this->_rule->heuristic(this, x, y, player);
	}
	else
	{
		_lastPlayP2 = playPair(x, y);
		_boardValueP2 += this->_rule->heuristic(this, x, y, player);
	}
	//debugs("Cap");
	return (true);
	*/
}

int					Board::calcHeur(int x, int y, Player *player)
{
	int		v;

	_board[y][x] = player->getNum();
	v = this->_rule->heuristic(this, y, x, player);
	_board[y][x] = 0;
	return (v);
}

void			Board::setWinner(int winner)
{
	_win = winner;
}

Board			Board::operator=(Board *rhs)
{
	if (this != rhs)
	{
		this->_rule = rhs->getRule();
		this->_win = rhs->getWinner();
		this->_board = rhs->getBoard();
		this->_lastPlayP1 = rhs->getLastPlayP1();
		this->_lastPlayP2 = rhs->getLastPlayP2();
		this->_boardValueP1 = rhs->getBoardValueP1();
		this->_boardValueP2 = rhs->getBoardValueP2();
		this->_heuristic = rhs->getHeuristic();
		this->_clear = rhs->getClear();
	}
	return (*this);
}

int					Board::calcHeuristic(int x, int y, Player *player)
{
	return (this->_rule->heuristic(this, x, y, player));
}

bool			Board::_checkFull(void)
{
	int		x;
	int		y;

	y = 0;
	while (y < 19)
	{
		x = 0;
		while (x < 19)
		{
			if (!this->_board[y][x])
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

int				Board::getHeuristic(void)
{
	return (_heuristic);
}

playPair		Board::getLastPlayP(int n)
{
	if (n == 1)
		return (_lastPlayP1);
	return (_lastPlayP2);
}

int			Board::getBoardValueP(int n)
{
	if (n == 1)
		return (_boardValueP1);
	return (_boardValueP2);
}

playPair		Board::getLastPlayP1(void)
{
	return (_lastPlayP1);
}

playPair		Board::getLastPlayP2(void)
{
	return (_lastPlayP2);
}

int				Board::getBoardValueP1(void)
{
	return (_boardValueP1);
}

int				Board::getBoardValueP2(void)
{
	return (_boardValueP2);
}

Rules			*Board::getRule()
{
	return (_rule);
}

int				Board::getWinner()
{
	return (_win);
}

void			Board::setRule(Rules *rule)
{
	this->_rule = rule;
}

t_matrix		Board::getBoard(void)
{
	return (this->_board);
}

t_matrix &		Board::getBoard(int i)
{
	(void)i;
	return (this->_board);
}

void			Board::setBoard(t_matrix & board)
{
	_board = board;
}

// const
int				Board::getHeuristic(void) const
{
	return (_heuristic);
}

playPair		Board::getLastPlayP(int n) const
{
	if (n == 1)
		return (_lastPlayP1);
	return (_lastPlayP2);
}

int			Board::getBoardValueP(int n) const
{
	if (n == 1)
		return (_boardValueP1);
	return (_boardValueP2);
}

playPair		Board::getLastPlayP1(void) const
{
	return (_lastPlayP1);
}

playPair		Board::getLastPlayP2(void) const
{
	return (_lastPlayP2);
}

int				Board::getBoardValueP1(void) const
{
	return (_boardValueP1);
}

int				Board::getBoardValueP2(void) const
{
	return (_boardValueP2);
}

Rules			*Board::getRule() const
{
	return (_rule);
}

int				Board::getWinner() const
{
	return (_win);
}

t_matrix		Board::getBoard(void) const
{
	return (this->_board);
}

bool			Board::getClear(void) const
{
	return (_clear);
}

void		Board::removePawns(int n)
{
	_nPawns -= n;
}

int		Board::getPawns(void)
{
	return (_nPawns);
}
