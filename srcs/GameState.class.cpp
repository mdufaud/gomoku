/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameState.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 17:31:15 by mdufaud           #+#    #+#             */
/*   Updated: 2016/04/28 17:58:27 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameState.class.hpp"
#include "Player.class.hpp"
#include "Board.class.hpp"

GameState::GameState(void)
{
	_p1 = NULL;
	_p2 = NULL;
	_pTurn = NULL;
}

GameState::GameState(Player *p1, Player *p2, Player *pTurn, Board & board)
{
	_p1 = new Player(p1);
	_p1->setName(p1->getName());
	_p2 = new Player(p2);
	_p2->setName(p2->getName());
	_pTurn = pTurn == p1 ? _p1 : _p2;
	_board = board;
}

GameState::GameState(GameState const & rhs)
{
	_p1 = new Player(rhs._p1);
	_p1->setName(rhs._p1->getName());
	_p2 = new Player(rhs._p2);
	_p2->setName(rhs._p2->getName());
	_pTurn = rhs._pTurn == rhs._p1 ? _p1 : _p2;
	_board = rhs._board;
}

GameState::~GameState()
{
	delete _p1;
	delete _p2;
}

GameState &		GameState::operator=(GameState const & rhs)
{
	if (this != &rhs)
	{
		_p1 = new Player(rhs._p1);
		_p1->setName(rhs._p1->getName());
		_p2 = new Player(rhs._p2);
		_p2->setName(rhs._p2->getName());
		_pTurn = rhs._pTurn == rhs._p1 ? _p1 : _p2;
		_board = rhs._board;
	}
	return (*this);
}
