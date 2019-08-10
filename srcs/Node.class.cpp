/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Node.class.hpp"
#include "gomoku.hpp"

Node::Node()
{
	_x = -1;
	_y = -1;
	_xPlay = -1;
	_yPlay = -1;
	_p1 = NULL;
	_p2 = NULL;
	_depth = 1;
	_totalDepth = 1;
	_playerTurn = 0;
	_playerNode = 0;
	_value = 0;
	_max = true;
	_alpha = ALPHA_VALUE;
	_beta = BETA_VALUE;
}

Node::Node(int x, int y, Board & board, Player *p1, Player *p2, int playerNum, int depth)
{
	_x = x;
	_y = y;
	_xPlay = x;
	_yPlay = y;
	_board = Board(board);
	_p1 = new Player(p1);
	_p2 = new Player(p2);
	_depth = depth;
	_totalDepth = depth;
	_playerTurn = playerNum == 1 ? 2 : 1;
	_playerNode = playerNum;
	_value = 0;
	_max = true;
	_alpha = ALPHA_VALUE;
	_beta = BETA_VALUE;
}

Node::Node(Node & node)
{
	_board = Board(node._board);
	_p1 = new Player(node._p1);
	_p2 = new Player(node._p2);
	_depth = node._depth - 1;
	_totalDepth = node._totalDepth;
	_playerTurn = node._playerTurn == 1 ? 2 : 1;
	_playerNode = node._playerNode;
	_pTurn = _playerTurn == 1 ? _p1 : _p2;
	_value = 0;
	_max = node._max == true ? false : true;
	_alpha = node._alpha;
	_beta = node._beta;
	_x = -1;
	_y = -1;
	_xPlay = -1;
	_yPlay = -1;
}

Node::~Node()
{
}

bool		Node::isRoot(void)
{
	if (_depth == _totalDepth)
		return (true);
	return (false);
}

void		Node::printDepthTab(int actualDepth, int depth)
{
	int		i;

	i = 0;
	while (actualDepth + i < depth - 1)
	{
		std::cout << "\t";
		i++;
	}
}

std::ostream  &	operator<<(std::ostream  & o, Node *rhs)
{
	o << "Node: "
		<< (void *)rhs
		<< " P1: "
		<< rhs->_p1
		<< " P2: "
		<< rhs->_p2
		<< " DEPTH: "
		<< rhs->_depth
		<< " PTURN: "
		<< rhs->_playerTurn
		<< " BOARD: "
		<< &rhs->_board
		;
	return o;
}
