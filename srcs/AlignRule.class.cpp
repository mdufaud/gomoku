/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlignRule.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 16:01:10 by rcherik           #+#    #+#             */
/*   Updated: 2016/04/28 17:30:17 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AlignRule.class.hpp"
#include "Player.class.hpp"
#include "Board.class.hpp"
#include "Coup.class.hpp"
#include "gomoku.hpp"

AlignRule::AlignRule(void) : Rules() {}

AlignRule::~AlignRule(void) {}

int				AlignRule::heuristic(Board *board, int xPlay, int yPlay, Player *player)
{
	Coup			coup;

	_playerNum = player->getNum();
	_otherPlayerNum = _playerNum == 1 ? 2 : 1;
	coup = Coup(xPlay, yPlay, board->getBoard(0), player);
	coup.tryAlign();
	if (this->gameOver(player, board->getBoard(0), coup))
	{
		board->setWinner(_playerNum);
		return (VICTORY_VALUE);
	}
	coup.calcAlignValue();
	//coup.printState();
	return (coup.getValue());
}

bool			AlignRule::gameOver(Player *player, t_matrix & board, Coup & coup)
{
	(void)board;
	_playerNum = player->getNum();
	_otherPlayerNum = _playerNum == 1 ? 2 : 1;
	if ((coup._alignH >= 5 && coup._spaceLeftH > 0 && coup._spaceRightH > 0) ||
		(coup._alignV >= 5  && coup._spaceLeftV > 0 && coup._spaceRightV > 0) ||
		(coup._alignD1 >= 5  && coup._spaceLeftD1 > 0 && coup._spaceRightD1 > 0) ||
		(coup._alignD2 >= 5 && coup._spaceLeftD2 > 0 && coup._spaceRightD2 > 0))
		return (true);
	return (false);
}

bool			AlignRule::_checkWinAround(int x, int y, t_matrix & board)
{
	int		xAdd;
	int		yAdd;

	xAdd = 1;
	yAdd = 0;
	if (this->_checkWinDirection(x, y, xAdd, yAdd, board))
		return (true);
	xAdd = 0;
	yAdd = 1;
	if (this->_checkWinDirection(x, y, xAdd, yAdd, board))
		return (true);
	xAdd = 1;
	yAdd = 1;
	if (this->_checkWinDirection(x, y, xAdd, yAdd, board))
		return (true);
	xAdd = -1;
	yAdd = 0;
	if (this->_checkWinDirection(x, y, xAdd, yAdd, board))
		return (true);
	xAdd = 0;
	yAdd = -1;
	if (this->_checkWinDirection(x, y, xAdd, yAdd, board))
		return (true);
	xAdd = -1;
	yAdd = -1;
	if (this->_checkWinDirection(x, y, xAdd, yAdd, board))
		return (true);
	xAdd = 1;
	yAdd = -1;
	if (this->_checkWinDirection(x, y, xAdd, yAdd, board))
		return (true);
	xAdd = -1;
	yAdd = 1;
	if (this->_checkWinDirection(x, y, xAdd, yAdd, board))
		return (true);
	return (false);
}

bool			AlignRule::_checkWinDirection(int x, int y, int xAdd, int yAdd, t_matrix & board)
{
	int	i;
	int	lowestX;
	int	lowestY;

	i = 0;
	//printf("\t\t\tChecking win coord: x=%d, y=%d with direction: x=%d, y=%d\n", x, y, xAdd, yAdd);
	while (x >= 0 && y >= 0 && y < 19 && x < 19 && board[y][x] == _playerNum)
	{
		x += xAdd;
		y += yAdd;
	}
	xAdd *= -1;
	yAdd *= -1;
	x += xAdd;
	y += yAdd;
	lowestX = x;
	lowestY = y;
	while (x >= 0 && y >= 0 && y < 19 && x < 19 && board[y][x] == _playerNum)
	{
		x += xAdd;
		y += yAdd;
		i++;
	}
	if (i < 5)
		return (false);
	i = 0;
	x = lowestX;
	y = lowestY;
	while (board[y][x] == _playerNum)
	{
		i++;
		x += xAdd;
		y += yAdd;
	}
	//printf("\t\t\t\tWON\n");
	if (i >= 5)
		return (true);
	return (false);
}

bool		AlignRule::validPlay(int x, int y, t_matrix & board)
{
	if (this->_checkDFT(x, y, board, _playerNum))
		return (false);
	return (true);
}

bool		AlignRule::validPlay(int x, int y, t_matrix & board, Player *player)
{
	std::string		error;

	_playerNum = player->getNum();
	_otherPlayerNum = _playerNum == 1 ? 2 : 1;
	if (y < 0 || y > 18 || x < 0 || x > 18)
		error = "Bad play: out of the board.";
	else if (board[y][x] == 1 || board[y][x] == 2)
		error = "Bad play.";
	else if (this->_checkDFT(x, y, board, _playerNum))
		error = "Double Free Three";
	if (!error.empty())
	{
		this->setError(error);
		return (false);
	}
	return (true);
}

void		AlignRule::_checkHFT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems)
{
	if (y < 14)
	{
		//_xxx_
		if (board[y][x + 1] == playerNum && board[y][x + 2] == playerNum && board[y][x + 3] == playerNum && !board[y][x + 4])
		{
		//	std::cout << "_xxx_" << std::endl;
			elems[std::pair<int, int>(y, x)] += 1;
			elems[std::pair<int, int>(y, x + 1)] += 1;
			elems[std::pair<int, int>(y, x + 2)] += 1;
			elems[std::pair<int, int>(y, x + 3)] += 1;
			elems[std::pair<int, int>(y, x + 4)] += 1;
		}
	}
	if (y < 13)
	{
		//_xx_x_
		if (board[y][x + 1] == playerNum && board[y][x + 2] == playerNum && !board[y][x + 3] && board[y][x + 4] == playerNum && !board[y][x + 5])
		{
	//		std::cout << "_xx_x_" << std::endl;
			elems[std::pair<int, int>(y, x)] += 1;
			elems[std::pair<int, int>(y, x + 1)] += 1;
			elems[std::pair<int, int>(y, x + 2)] += 1;
			elems[std::pair<int, int>(y, x + 3)] += 1;
			elems[std::pair<int, int>(y, x + 4)] += 1;
			elems[std::pair<int, int>(y, x + 5)] += 1;
		}
		//_x_xx_
		if (board[y][x + 1] == playerNum && !board[y][x + 2] && board[y][x + 3] == playerNum && board[y][x + 4] == playerNum && !board[y][x + 5])
		{
	//		std::cout << "_x_xx_" << std::endl;
			elems[std::pair<int, int>(y, x)] += 1;
			elems[std::pair<int, int>(y, x + 1)] += 1;
			elems[std::pair<int, int>(y, x + 2)] += 1;
			elems[std::pair<int, int>(y, x + 3)] += 1;
			elems[std::pair<int, int>(y, x + 4)] += 1;
			elems[std::pair<int, int>(y, x + 5)] += 1;
		}
	}
}

void		AlignRule::_checkVFT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems)
{
	if (y < 14)
	{
		//_xxx_
		if (board[y + 1][x] == playerNum && board[y + 2][x] == playerNum && board[y + 3][x] == playerNum && !board[y + 4][x])
		{
			elems[std::pair<int, int>(y, x)] += 1;
			elems[std::pair<int, int>(y + 1, x)] += 1;
			elems[std::pair<int, int>(y + 2, x)] += 1;
			elems[std::pair<int, int>(y + 3, x)] += 1;
			elems[std::pair<int, int>(y + 4, x)] += 1;
		}
	}
	if (y < 13)
	{
		//_xx_x_
		if (board[y + 1][x] == playerNum && board[y + 2][x] == playerNum && !board[y + 3][x] && board[y + 4][x] == playerNum && !board[y + 5][x])
		{
			elems[std::pair<int, int>(y, x)] += 1;
			elems[std::pair<int, int>(y + 1, x)] += 1;
			elems[std::pair<int, int>(y + 2, x)] += 1;
			elems[std::pair<int, int>(y + 3, x)] += 1;
			elems[std::pair<int, int>(y + 4, x)] += 1;
			elems[std::pair<int, int>(y + 5, x)] += 1;
		}
		//_x_xx_
		if (board[y + 1][x] == playerNum && !board[y + 2][x] && board[y + 3][x] == playerNum && board[y + 4][x] == playerNum && !board[y + 5][x])
		{
			elems[std::pair<int, int>(y, x)] += 1;
			elems[std::pair<int, int>(y + 1, x)] += 1;
			elems[std::pair<int, int>(y + 2, x)] += 1;
			elems[std::pair<int, int>(y + 3, x)] += 1;
			elems[std::pair<int, int>(y + 4, x)] += 1;
			elems[std::pair<int, int>(y + 5, x)] += 1;
		}
	}
}

void		AlignRule::_checkD1FT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems)
{
	if (y < 14 && x > 3)
	{
		//_xxx_
		if (board[y + 1][x - 1] == playerNum && board[y + 2][x - 2] == playerNum && board[y + 3][x - 3] == playerNum && !board[y + 4][x - 4])
		{
			elems[std::pair<int, int>(y, x)] += 1;
			elems[std::pair<int, int>(y + 1, x - 1)] += 1;
			elems[std::pair<int, int>(y + 2, x - 2)] += 1;
			elems[std::pair<int, int>(y + 3, x - 3)] += 1;
			elems[std::pair<int, int>(y + 4, x - 4)] += 1;
		}
	}
	if (y < 13 && x > 4)
	{
		//_xx_x_
		if (board[y + 1][x - 1] == playerNum && board[y + 2][x - 2] == playerNum && !board[y + 3][x - 3] && board[y + 4][x - 4] == playerNum && !board[y + 5][x - 5])
		{
			elems[std::pair<int, int>(y, x)] += 1;
			elems[std::pair<int, int>(y + 1, x - 1)] += 1;
			elems[std::pair<int, int>(y + 2, x - 2)] += 1;
			elems[std::pair<int, int>(y + 3, x - 3)] += 1;
			elems[std::pair<int, int>(y + 4, x - 4)] += 1;
			elems[std::pair<int, int>(y + 5, x - 5)] += 1;
		}
		//_x_xx_
		if (board[y + 1][x - 1] == playerNum && !board[y + 2][x - 2] && board[y + 3][x - 3] == playerNum && board[y + 4][x - 4] == playerNum && !board[y + 5][x - 5])
		{
			elems[std::pair<int, int>(y, x)] += 1;
			elems[std::pair<int, int>(y + 1, x - 1)] += 1;
			elems[std::pair<int, int>(y + 2, x - 2)] += 1;
			elems[std::pair<int, int>(y + 3, x - 3)] += 1;
			elems[std::pair<int, int>(y + 4, x - 4)] += 1;
			elems[std::pair<int, int>(y + 5, x - 5)] += 1;
		}
	}
}

void		AlignRule::_checkD2FT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems)
{
	if (y < 14 && x < 14)
	{
		//_xxx_
		if (board[y + 1][x + 1] == playerNum && board[y + 2][x + 2] == playerNum && board[y + 3][x + 3] == playerNum && !board[y + 4][x + 4])
		{
			elems[std::pair<int, int>(y, x)] += 1;
			elems[std::pair<int, int>(y + 1, x + 1)] += 1;
			elems[std::pair<int, int>(y + 2, x + 2)] += 1;
			elems[std::pair<int, int>(y + 3, x + 3)] += 1;
			elems[std::pair<int, int>(y + 4, x + 4)] += 1;
		}
	}
	if (y < 13 && x < 13)
	{
		//_xx_x_
		if (board[y + 1][x + 1] == playerNum && board[y + 2][x + 2] == playerNum && !board[y + 3][x + 3] && board[y + 4][x + 4] == playerNum && !board[y + 5][x + 5])
		{
			elems[std::pair<int, int>(y, x)] += 1;
			elems[std::pair<int, int>(y + 1, x + 1)] += 1;
			elems[std::pair<int, int>(y + 2, x + 2)] += 1;
			elems[std::pair<int, int>(y + 3, x + 3)] += 1;
			elems[std::pair<int, int>(y + 4, x + 4)] += 1;
			elems[std::pair<int, int>(y + 5, x + 5)] += 1;
		}
		//_x_xx_
		if (board[y + 1][x + 1] == playerNum && !board[y + 2][x + 2] && board[y + 3][x + 3] == playerNum && board[y + 4][x + 4] == playerNum && !board[y + 5][x + 5])
		{
			elems[std::pair<int, int>(y, x)] += 1;
			elems[std::pair<int, int>(y + 1, x + 1)] += 1;
			elems[std::pair<int, int>(y + 2, x + 2)] += 1;
			elems[std::pair<int, int>(y + 3, x + 3)] += 1;
			elems[std::pair<int, int>(y + 4, x + 4)] += 1;
			elems[std::pair<int, int>(y + 5, x + 5)] += 1;
		}
	}
}

void		AlignRule::_checkFT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems)
{
	if (board[y][x])
		return ;
	_checkHFT(x, y, board, playerNum, elems);
	_checkVFT(x, y, board, playerNum, elems);
	_checkD1FT(x, y, board, playerNum, elems);
	_checkD2FT(x, y, board, playerNum, elems);
}

bool		AlignRule::_checkDFT(int x, int y, t_matrix & board, int playerNum)
{
	int					maxX;
	int					maxY;
	int					minX;
	int					minY;
	int					tmpX;
	int					tmpY;
	std::map<std::pair<int, int>, int>				elems;
	std::map<std::pair<int, int>, int>::iterator	it;

	//debugs("checkDFT");
	board[y][x] = playerNum;
	maxX = x + 5 > 18 ? 18 : x + 5;
	maxY = y + 5 > 18 ? 18 : y + 5;
	minX = x - 5 < 0 ? 0 : x - 5;
	minY = y - 5 < 0 ? 0 : y - 5;
	tmpX = minX;
	while (tmpX < maxX)
	{
		tmpY = minY;
		while (tmpY < maxY)
		{
			_checkFT(tmpX, tmpY, board, playerNum, elems);
			tmpY++;
		}
		tmpX++;
	}
//	printElems(elems, board);
	board[y][x] = 0;
	it = elems.begin();
	for (it = elems.begin(); it != elems.end(); ++it)
	{
		if (it->second > 1)
			return (true);
	}
	return (false);
}
