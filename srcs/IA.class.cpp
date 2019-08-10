/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IA.class.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2016/07/01 16:02:25 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IA.class.hpp"
#include "Board.class.hpp"
#include "Player.class.hpp"
#include "Rules.class.hpp"
#include "Node.class.hpp"
#include "gomoku.hpp"
#include "Coup.class.hpp"
#include "LogBlock.class.hpp"
#include <unistd.h>

IA::IA(Rules *rule, Player *p1, Player *p2, int depth)
{
	_p1 = p1;
	_p2 = p2;
	_pTurn = 0;
	_rule = rule;
	_depth = depth;
	_maxRect = 6;
	_searchRect = _maxRect;
	_cutOffs = 0;
	_cuttedNodes = 0;
	_numberOfNodes = 0;
	_numberOfMoves = 0;
	_erasedMoves = 0;
	_timeOut = 0;
}

IA::~IA()
{
	_lock.unlock();
}

void		IA::setPlayers(Player *p1, Player *p2)
{
	_p1 = p1;
	_p2 = p2;
}

void		IA::startAlphaBeta(void)
{
	if (_tmpNode._board.getClear())
	{
		_numberOfMoves = 1;
		_tmpNode._x = (rand() % 6) + 6;
		_tmpNode._y = (rand() % 6) + 6;
		usleep(50000);
		return ;
	}
	_timeOut = time(0) + 30;
	_cutOffs = 0;
	_cuttedNodes = 0;
	_numberOfNodes = 0;
	_numberOfMoves = 0;
	_erasedMoves = 0;
	this->alphaBeta(_tmpNode, ALPHA_VALUE, BETA_VALUE);
}

void		IA::getStats(t_iaStats *s)
{
	s->nMoves = _numberOfMoves;
	s->erasedMoves = _erasedMoves;
	s->nNodes = _numberOfNodes;
	s->cutNodes = _cuttedNodes;
	s->cutOffs = _cutOffs;
	s->percentCutOffs = (((double)_cuttedNodes / _numberOfMoves) * 100);
}

void		IA::thinkDepth(Player *player, Board *b, int depth)
{
	_lock.lock();
	_tmpNode = Node(-1, -1, *b, _p1, _p2, player->getNum(), depth);
	this->startAlphaBeta();
	_lock.unlock();
}

void		IA::think(Player *player, Board *b)
{
	_lock.lock();
	_tmpNode = Node(-1, -1, *b, _p1, _p2, player->getNum(), _depth);
	this->startAlphaBeta();
	_lock.unlock();
}

void			printMoves(std::list<Coup> pList)
{
	int			i;
	std::list<Coup>::iterator	it;

	i = 0;
	for (it = pList.begin(); it != pList.end() ; ++it)
	{
		if (i % 4 == 0)
			printf("\n");
		printf("(x:%d, y:%d, v:%d) ", it->_x, it->_y, it->_value);
		i++;
	}
	printf("\n\n");
}

int			IA::alphaBeta(Node & node, int alpha, int beta)
{
	int								bestX;
	int								bestY;
	int								v;
	Node							newNode;
	std::list<Coup>					pList;
	Coup							currentCoup;
	std::list<Coup>::iterator			it;

	bestX = -1;
	bestY = -1;
	v = 0;
	if (!node._depth || node._board.getWinner() > 0)
	{
		_numberOfNodes++;
		if (node._playerNode == 1)
			v = node._board.getBoardValueP1() - node._board.getBoardValueP2();
 		else if (node._playerNode == 2)
			v = node._board.getBoardValueP2() - node._board.getBoardValueP1();
		return (v);
	}
	if (node._max)
	{
		pList = this->getAllMoveList(node);
		it = pList.begin();
		while (it != pList.end())
		{
			currentCoup = (*it);
			newNode = Node(node);
			if (newNode._board.play(currentCoup._x, currentCoup._y, newNode._pTurn))
			{
				v = this->alphaBeta(newNode, alpha, beta) - ((newNode._totalDepth - newNode._depth) * DEPTH_VALUE);
				if (v > alpha)
				{
					alpha = v;
					bestX = currentCoup._x;
					bestY = currentCoup._y;
				}
				if (beta <= alpha)
				{
					_cutOffs++;
					_cuttedNodes += pList.size();
					break ;
				}
			}
			it++;
			if (node.isRoot() && time(0) > _timeOut)
				break ;
		}
		node._value = alpha;
	}
	else
	{
		pList = this->getAllMoveList(node);
		it = pList.begin();
		while (it != pList.end())
		{
			currentCoup = (*it);
			newNode = Node(node);
			if (newNode._board.play(currentCoup._x, currentCoup._y, newNode._pTurn))
			{
				v = this->alphaBeta(newNode, alpha, beta) - ((newNode._totalDepth - newNode._depth) * DEPTH_VALUE);
				if (v < beta)
				{
					beta = v;
					bestX = currentCoup._x;
					bestY = currentCoup._y;
				}
				if (beta <= alpha)
				{
					_cutOffs++;
					_cuttedNodes += pList.size();
					break ;
				}
			}
			if (node.isRoot() && time(0) > _timeOut)
				break ;
			it++;
		}
		node._value = beta;
	}
	node._x = bestX;
	node._y = bestY;
	node._alpha = alpha;
	node._beta = beta;
	return (node._value);
}

bool		IA::isLocked()
{
	if (_lock.try_lock())
	{
		_lock.unlock();
		return (false);
	}
	return (true);
}

playPair		IA::getPlayerPlay()
{
	PlayPair	pair = PlayPair(_tmpNode._x, _tmpNode._y);

	pair.first = _tmpNode._x;
	pair.second = _tmpNode._y;
	_tmpNode = Node();
	return (pair);
}

bool			checkPoint(int x, int y, t_matrix & board)
{
	if (y < 19 && x < 19 && x >= 0 && y >= 0
		&& board[y][x] == 0)
		return (true);
	return (false);
}

void			checkAround(int x, int y, t_matrix & board, playPairList & pList)
{
	int		addX;
	int		addY;

	addY = 0;
	addX = 1;
	if (checkPoint(x + addX, y + addY, board))
		pList.insert(playPair(x + addX, y + addY));
	addX = -1;
	if (checkPoint(x + addX, y + addY, board))
		pList.insert(playPair(x + addX, y + addY));

	addY = 1;
	if (checkPoint(x + addX, y + addY, board))
		pList.insert(playPair(x + addX, y + addY));
	addX = 1;
	if (checkPoint(x + addX, y + addY, board))
		pList.insert(playPair(x + addX, y + addY));
	addX = 0;
	if (checkPoint(x + addX, y + addY, board))
		pList.insert(playPair(x + addX, y + addY));

	addY = -1;
	if (checkPoint(x + addX, y + addY, board))
		pList.insert(playPair(x + addX, y + addY));
	addX = -1;
	if (checkPoint(x + addX, y + addY, board))
		pList.insert(playPair(x + addX, y + addY));
	addX = 1;
	if (checkPoint(x + addX, y + addY, board))
		pList.insert(playPair(x + addX, y + addY));
}

void			IA::getMoves(t_matrix & board, playPairList & pList, playPair & lastPlay)
{
	int				y;
	int				x;
	int				maxY;
	int				maxX;

	y = lastPlay.second - _searchRect < 0 ? 0 : lastPlay.second - _searchRect;
	maxY = lastPlay.second + _searchRect > 19 ? 19 : lastPlay.second + _searchRect;
	maxX = lastPlay.first + _searchRect > 19 ? 19 : lastPlay.first + _searchRect;
	while (y < maxY)
	{
		x = lastPlay.first - _searchRect < 0 ? 0 : lastPlay.first - _searchRect;
		while (x < maxX)
		{
			if (board[y][x] > 0)
				checkAround(x, y, board, pList);
			x++;
		}
		y++;
	}
}

static bool		sorting(Coup & left, Coup & right)
{
	return (left.getValue() > right.getValue());
}

std::list<Coup>		IA::getAllMoveList(Node & node)
{
	int							playerNumber;
	int							otherPlayerNumber;
	int							avg;
	t_matrix					board = node._board.getBoard();
	playPair					lastPlay;
	playPairList				pList;
	std::list<Coup>				listCoup;
	playPairList::iterator		it;
	std::list<Coup>::iterator	it2;
	int							i;

	avg = 0;
	playerNumber = node._playerTurn;
	otherPlayerNumber = playerNumber == 1 ? 2 : 1;
	//Plays around your last play
	lastPlay = node._board.getLastPlayP(playerNumber);
	this->getMoves(board, pList, lastPlay);
	//Plays around other player's last play
	lastPlay = node._board.getLastPlayP(otherPlayerNumber);
	this->getMoves(board, pList, lastPlay);
	i = 0;
	for (it = pList.begin(); it != pList.end(); it++)
	{
		i++;
		_numberOfMoves++;
		listCoup.push_back(Coup(it->first, it->second, board));
		avg += listCoup.back()._value;
	}
	avg /= i;
	avg = avg + ((avg * 75) / 100);
	for (it2 = listCoup.begin(); it2 != listCoup.end(); it2++)
	{
		if (it2->_value <= avg)
		{
			_erasedMoves++;
			it2 = listCoup.erase(it2);
			_numberOfMoves--;
		}
	}
	listCoup.sort(sorting);
	return (listCoup);
}

Player		*IA::getPlayer(int number, Player *p1, Player *p2)
{
	if (number == 1)
		return (p1);
	else if (number == 2)
		return (p2);
	return (NULL);
}

void		IA::setDepth(int depth)
{
	_depth = depth;
}

void		IA::setSearchRect(int searchRect)
{
	_searchRect = searchRect;
}

void			IA::setLog(LogBlock *block)
{
	_logBlock = block;
}
