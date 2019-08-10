/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassicRule.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 16:01:10 by rcherik           #+#    #+#             */
/*   Updated: 2016/07/01 16:56:37 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClassicRule.class.hpp"
#include "Player.class.hpp"
#include "Board.class.hpp"
#include "Coup.class.hpp"
#include "gomoku.hpp"

ClassicRule::ClassicRule(void) : Rules() {}

ClassicRule::~ClassicRule(void) {}

void			ClassicRule::infoCap(int y1, int x1, int y2, int x2, Player *player)
{
	std::ostringstream	stream;
	std::string			s;

	stream << player->getName()
		<< " captured pawns at x: "
		<< x1
		<< ", y: "
		<< y1
		<< " and x: "
		<< x2
		<< ", y: "
		<< y2;
	s = stream.str();
	this->setInfo(s);
}

int				ClassicRule::_checkVCapture(int x, int y, Player *player, t_matrix & board)
{
	int		n;

	n = 0;
	if (y < 16)
	{
		if (board[y + 1][x] == _otherPlayerNum &&
				board[y + 2][x] == _otherPlayerNum &&
				board[y + 3][x] == _playerNum)
		{
			board[y + 1][x] = 0;
			board[y + 2][x] = 0;
			player->incCap();
			infoCap(y + 1, x, y + 2, x, player);
			n += 2;
		}
	}
	if (y > 2)
	{
		if (board[y - 1][x] == _otherPlayerNum &&
				board[y - 2][x] == _otherPlayerNum &&
				board[y - 3][x] == _playerNum)
		{
			board[y - 1][x] = 0;
			board[y - 2][x] = 0;
			player->incCap();
			infoCap(y - 1, x, y - 2, x, player);
			n += 2;
		}
	}
	return (n);
}

int				ClassicRule::_checkHCapture(int x, int y, Player *player, t_matrix & board)
{
	int		n;

	n = 0;
	if (x < 16)
	{
		if (board[y][x + 1] == _otherPlayerNum &&
				board[y][x + 2] == _otherPlayerNum &&
				board[y][x + 3] == _playerNum)
		{
			board[y][x + 1] = 0;
			board[y][x + 2] = 0;
			player->incCap();
			infoCap(y, x + 1, y, x + 2, player);
			n += 2;
		}
	}
	if (x > 2)
	{
		if (board[y][x - 1] == _otherPlayerNum &&
				board[y][x - 2] == _otherPlayerNum &&
				board[y][x - 3] == _playerNum)
		{
			board[y][x - 1] = 0;
			board[y][x - 2] = 0;
			player->incCap();
			infoCap(y, x - 1, y, x - 2, player);
			n += 2;
		}
	}
	return (n);
}

int				ClassicRule::_checkDCapture(int x, int y, Player *player, t_matrix & board)
{
	int		n;

	n = 0;
	if (y < 16 && x < 16)
	{
		if (board[y + 1][x + 1] == _otherPlayerNum &&
				board[y + 2][x + 2] == _otherPlayerNum &&
				board[y + 3][x + 3] == _playerNum)
		{
			board[y + 1][x + 1] = 0;
			board[y + 2][x + 2] = 0;
			player->incCap();
			infoCap(y + 1, x + 1, y + 2, x + 2, player);
			n += 2;
		}
	}
	if (x > 2 && y > 2)
	{
		if (board[y - 1][x - 1] == _otherPlayerNum &&
				board[y - 2][x - 2] == _otherPlayerNum &&
				board[y - 3][x - 3] == _playerNum)
		{
			board[y - 1][x - 1] = 0;
			board[y - 2][x - 2] = 0;
			player->incCap();
			infoCap(y - 1, x - 1, y - 2, x - 2, player);
			n += 2;
		}
	}
	if (y < 16 && x > 2)
	{
		if (board[y + 1][x - 1] == _otherPlayerNum &&
				board[y + 2][x - 2] == _otherPlayerNum &&
				board[y + 3][x - 3] == _playerNum)
		{
			board[y + 1][x - 1] = 0;
			board[y + 2][x - 2] = 0;
			player->incCap();
			infoCap(y + 1, x - 1, y + 2, x - 2, player);
			n += 2;
		}
	}
	if (y > 2 && x < 16)
	{
		if (board[y - 1][x + 1] == _otherPlayerNum &&
				board[y - 2][x + 2] == _otherPlayerNum &&
				board[y - 3][x + 3] == _playerNum)
		{
			board[y - 1][x + 1] = 0;
			board[y - 2][x + 2] = 0;
			player->incCap();
			infoCap(y - 1, x + 1, y - 2, x + 2, player);
			n += 2;
		}
	}
	return (n);
}

int			ClassicRule::checkCapture(int x, int y, Player *player, t_matrix & board)
{
	int		n;

	n = this->_checkHCapture(x, y, player, board);
	n += this->_checkVCapture(x, y, player, board);
	n += this->_checkDCapture(x, y, player, board);
	return (n);
}

int				ClassicRule::heuristic(Board *board, int xPlay, int yPlay, Player *player)
{
	Coup			coup;
	int				n;

	_playerNum = player->getNum();
	_otherPlayerNum = _playerNum == 1 ? 2 : 1;
	coup = Coup(xPlay, yPlay, board->getBoard(0), player);
	coup.tryAlign();
	coup.checkCapture();
	if (this->gameOver(player, board->getBoard(0), coup))
	{
		n = this->checkCapture(xPlay, yPlay, player, board->getBoard(0));
		board->removePawns(n);
		board->setWinner(_playerNum);
		return (VICTORY_VALUE);
	}
	n = this->checkCapture(xPlay, yPlay, player, board->getBoard(0));
	board->removePawns(n);
	coup.calcValue();
	//coup.printState();
	return (coup.getValue());
}

bool			ClassicRule::gameOver(Player *player, t_matrix & board, Coup & coup)
{
	bool	b;

	b = false;
	_canBeTakenImmuneX = -1;
	_canBeTakenImmuneY = -1;
	if (player->getCap() + coup._capV + coup._capH + coup._capD1 + coup._capD2 >= 5)
		return (true);
	_playerNum = player->getNum();
	_otherPlayerNum = _playerNum == 1 ? 2 : 1;
	//debugs("check cant be taken");
	if (coup._alignH >= 5 || coup._alignV >= 5 || coup._alignD1 >= 5 || coup._alignD2 >= 5)
		b = this->_checkIfCantBeTaken(board, coup);
	//debugs("check undo capture");
	if (!b && (coup._alignH == 3 || coup._alignV == 3 || coup._alignD1 == 3 || coup._alignD2 == 3))
		b = this->_checkIfUndoCapture(board, coup);
	//debugs("check capture win");
	if (!b)
		b = this->_checkIfCaptureWin(board, coup);
	//debugs("end");
	return (b);
}

bool			ClassicRule::_checkIfUndoCapture(t_matrix & board, Coup & coup)
{
	int		capX1;
	int		capX2;
	int		capY1;
	int		capY2;

	if (coup._alignH == 3)
	{
		capY1 = coup._y;
		capY2 = coup._y;
		if (!coup._spaceLeftH)
		{
			capX1 = coup._x - 1;
			capX2 = coup._x - 2;
			if (capX2 - 1 >= 0 && board[capY2][capX2 - 1] == _otherPlayerNum)
			{
				_canBeTakenImmuneX = capX2 - 1;
				_canBeTakenImmuneY = capY2;
				if (this->_checkWinAround(capX1, capY1, board))
					return (true);
				if (this->_checkWinAround(capX2, capY2, board))
					return (true);
				_canBeTakenImmuneX = -1;
				_canBeTakenImmuneY = -1;
			}
		}
		if (!coup._spaceRightH)
		{
			capX1 = coup._x + 1;
			capX2 = coup._x + 2;
			if (capX2 + 1 < 19 && board[capY2][capX2 + 1] == _otherPlayerNum)
			{
				_canBeTakenImmuneX = capX2 + 1;
				_canBeTakenImmuneY = capY2;
				if (this->_checkWinAround(capX1, capY1, board))
					return (true);
				if (this->_checkWinAround(capX2, capY2, board))
					return (true);
				_canBeTakenImmuneX = -1;
				_canBeTakenImmuneY = -1;
			}
		}
	}
	if (coup._alignV == 3)
	{
		capX1 = coup._x;
		capX2 = coup._x;
		if (!coup._spaceLeftV)
		{
			capY1 = coup._y - 1;
			capY2 = coup._y - 2;
			if (capY2 - 1 >= 0 && board[capY2 - 1][capX2] == _otherPlayerNum)
			{
				_canBeTakenImmuneX = capX2;
				_canBeTakenImmuneY = capY2 - 1;
				if (this->_checkWinAround(capX1, capY1, board))
					return (true);
				if (this->_checkWinAround(capX2, capY2, board))
					return (true);
				_canBeTakenImmuneX = -1;
				_canBeTakenImmuneY = -1;
			}
		}
		if (!coup._spaceRightV)
		{
			capY1 = coup._y + 1;
			capY2 = coup._y + 2;
			if (capY2 + 1 < 19 && board[capY2 + 1][capX2] == _otherPlayerNum)
			{
				_canBeTakenImmuneX = capX2;
				_canBeTakenImmuneY = capY2 + 1;
				if (this->_checkWinAround(capX1, capY1, board))
					return (true);
				if (this->_checkWinAround(capX2, capY2, board))
					return (true);
				_canBeTakenImmuneX = -1;
				_canBeTakenImmuneY = -1;
			}
		}
	}
	if (coup._alignD1 == 3)
	{
		if (!coup._spaceRightD1)
		{
			capX1 = coup._x + 1;
			capX2 = coup._x + 2;
			capY1 = coup._y - 1;
			capY2 = coup._y - 2;
			if (capY2 - 1 >= 0 && capX2 + 1 < 19 &&
				board[capY2 - 1][capX2 + 1] == _otherPlayerNum)
			{
				_canBeTakenImmuneX = capX2 + 1;
				_canBeTakenImmuneY = capY2 - 1;
				if (this->_checkWinAround(capX1, capY1, board))
					return (true);
				if (this->_checkWinAround(capX2, capY2, board))
					return (true);
				_canBeTakenImmuneX = -1;
				_canBeTakenImmuneY = -1;
			}
		}
		if (!coup._spaceLeftD1)
		{
			capX1 = coup._x - 1;
			capX2 = coup._x - 2;
			capY1 = coup._y + 1;
			capY2 = coup._y + 2;
			if (capY2 + 1 < 19 && capX2 - 1 >= 0 &&
				board[capY2 + 1][capX2 - 1] == _otherPlayerNum)
			{
				_canBeTakenImmuneX = capX2 - 1;
				_canBeTakenImmuneY = capY2 + 1;
				if (this->_checkWinAround(capX1, capY1, board))
					return (true);
				if (this->_checkWinAround(capX2, capY2, board))
					return (true);
				_canBeTakenImmuneX = -1;
				_canBeTakenImmuneY = -1;
			}
		}
	}
	if (coup._alignD2 == 3)
	{
		if (!coup._spaceLeftD2)
		{
			capX1 = coup._x + 1;
			capX2 = coup._x + 2;
			capY1 = coup._y + 1;
			capY2 = coup._y + 2;
			if (capY2 + 1 < 19 && capX2 + 1 < 19 &&
				board[capY2 + 1][capX2 + 1] == _otherPlayerNum)
			{
				_canBeTakenImmuneX = capX2 + 1;
				_canBeTakenImmuneY = capY2 + 1;
				if (this->_checkWinAround(capX1, capY1, board))
					return (true);
				if (this->_checkWinAround(capX2, capY2, board))
					return (true);
				_canBeTakenImmuneX = -1;
				_canBeTakenImmuneY = -1;
			}
		}
		if (!coup._spaceRightD2)
		{
			capX1 = coup._x - 1;
			capX2 = coup._x - 2;
			capY1 = coup._y - 1;
			capY2 = coup._y - 2;
			if (capY2 - 1 >= 0 && capX2 - 1 >= 0 &&
				board[capY2 - 1][capX2 - 1] == _otherPlayerNum)
			{
				_canBeTakenImmuneX = capX2 - 1;
				_canBeTakenImmuneY = capY2 - 1;
				if (this->_checkWinAround(capX1, capY1, board))
					return (true);
				if (this->_checkWinAround(capX2, capY2, board))
					return (true);
				_canBeTakenImmuneX = -1;
				_canBeTakenImmuneY = -1;
			}
		}
	}
	return (false);
}

bool			ClassicRule::_checkIfCaptureWin(t_matrix & board, Coup & coup)
{
	int		capX1;
	int		capX2;
	int		capY1;
	int		capY2;
	bool	b;

	b = false;
	if (coup._capH)
	{
		capY1 = coup._y;
		capY2 = coup._y;
		if (!coup._spaceLeftH)
		{
			capX1 = coup._x - 1;
			capX2 = coup._x - 2;
			b = this->_checkCaptureWin(capX1, capY1, capX2, capY2, board);
		}
		if (!b && !coup._spaceRightH)
		{
			capX1 = coup._x + 1;
			capX2 = coup._x + 2;
			b = this->_checkCaptureWin(capX1, capY1, capX2, capY2, board);
		}
	}
	if (coup._capV)
	{
		capX1 = coup._x;
		capX2 = coup._x;
		if (!b && !coup._spaceLeftV)
		{
			capY1 = coup._y - 1;
			capY2 = coup._y - 2;
			b = this->_checkCaptureWin(capX1, capY1, capX2, capY2, board);
		}
		if (!b && !coup._spaceRightV)
		{
			capY1 = coup._y + 1;
			capY2 = coup._y + 2;
			b = this->_checkCaptureWin(capX1, capY1, capX2, capY2, board);
		}
	}
	if (coup._capD1)
	{
		if (!b && !coup._spaceLeftD1)
		{
			capX1 = coup._x + 1;
			capX2 = coup._x + 2;
			capY1 = coup._y - 1;
			capY2 = coup._y - 2;
			b = this->_checkCaptureWin(capX1, capY1, capX2, capY2, board);
		}
		if (!b && !coup._spaceRightD1)
		{
			capX1 = coup._x - 1;
			capX2 = coup._x - 2;
			capY1 = coup._y + 1;
			capY2 = coup._y + 2;
			b = this->_checkCaptureWin(capX1, capY1, capX2, capY2, board);
		}
	}
	if (coup._capD2)
	{
		if (!b && !coup._spaceLeftD2)
		{
			capX1 = coup._x - 1;
			capX2 = coup._x - 2;
			capY1 = coup._y - 1;
			capY2 = coup._y - 2;
			b = this->_checkCaptureWin(capX1, capY1, capX2, capY2, board);
		}
		if (!b && !coup._spaceRightD2)
		{
			capX1 = coup._x + 1;
			capX2 = coup._x + 2;
			capY1 = coup._y - 1;
			capY2 = coup._y - 2;
			b = this->_checkCaptureWin(capX1, capY1, capX2, capY2, board);
		}
	}
	return (b);
}

bool			ClassicRule::_checkCaptureWin(int x1, int y1, int x2, int y2, t_matrix & board)
{
	if (this->_checkCapturable(x1, y1, board))
		return (true);
	if (this->_checkCapturable(x2, y2, board))
		return (true);
	return (false);
}

bool			ClassicRule::_checkCapturable(int x, int y, t_matrix & board)
{
	int		xAdd;
	int		yAdd;

	_canBeTakenImmuneX = x;
	_canBeTakenImmuneY = y;
	xAdd = 1;
	yAdd = 0;
	if (this->_checkCaptureDirection(x, y, xAdd, yAdd, board))
		return (true);
	xAdd = 0;
	yAdd = 1;
	if (this->_checkCaptureDirection(x, y, xAdd, yAdd, board))
		return (true);
	xAdd = 1;
	yAdd = 1;
	if (this->_checkCaptureDirection(x, y, xAdd, yAdd, board))
		return (true);
	xAdd = -1;
	yAdd = 0;
	if (this->_checkCaptureDirection(x, y, xAdd, yAdd, board))
		return (true);
	xAdd = 0;
	yAdd = -1;
	if (this->_checkCaptureDirection(x, y, xAdd, yAdd, board))
		return (true);
	xAdd = -1;
	yAdd = -1;
	if (this->_checkCaptureDirection(x, y, xAdd, yAdd, board))
		return (true);
	xAdd = 1;
	yAdd = -1;
	if (this->_checkCaptureDirection(x, y, xAdd, yAdd, board))
		return (true);
	xAdd = -1;
	yAdd = 1;
	if (this->_checkCaptureDirection(x, y, xAdd, yAdd, board))
		return (true);
	_canBeTakenImmuneX = -1;
	_canBeTakenImmuneY = -1;
	return (false);
}

bool			ClassicRule::_checkCaptureDirection(int x, int y, int xAdd, int yAdd, t_matrix & board)
{
	int	i;

	i = 0;
	x += xAdd;
	y += yAdd;
	//printf("Checking capture coord: x=%d, y=%d with direction: x=%d, y=%d\n", x, y, xAdd, yAdd);
	//printPuzzle(board);
	while (x >= 0 && y >= 0 && y < 19 && x < 19 && board[y][x] == _playerNum && i < 2)
	{
		i++;
		//printf("\tChecking cap x=%d, y=%d\n", x, y);
		x += xAdd;
		y += yAdd;
	}
	//printf("\tChecking blank @ x=%d, y=%d\n", x, y);
	if ((x >= 0 && y >= 0 && y < 19 && x < 19 && board[y][x] != 0) || i != 2)
		return (false);
	xAdd *= -1;
	yAdd *= -1;
	x += xAdd;
	y += yAdd;
	i = 0;
	while (i < 2)
	{
		//printf("\t\tChecking capture x:%d, y%d\n", x, y);
		if (this->_checkWinAround(x, y, board))
			return (true);
		i++;
		x += xAdd;
		y += yAdd;
	}
	return (false);
}

bool			ClassicRule::_checkWinAround(int x, int y, t_matrix & board)
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

bool			ClassicRule::_checkWinDirection(int x, int y, int xAdd, int yAdd, t_matrix & board)
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
	while (x >= 0 && y >= 0 && y < 19 && x < 19 && board[y][x] == _playerNum)
	{
		//printf("\t\t\t\tChecking win taken x:%d, y%d with immune x:%d, y:%d\n", x, y, _canBeTakenImmuneX, _canBeTakenImmuneY);
		if (this->_canBeTaken(x, y, board))
			i = 0;
		else
			i++;
		//printf("\t\t\t\t\ti = %d\n", i);
		x += xAdd;
		y += yAdd;
	}
	//printf("\t\t\t\ti = %d\n", i);
	if (i >= 5)
		return (true);
	return (false);
}

bool			ClassicRule::_checkIfCantBeTaken(t_matrix & board, Coup & coup)
{
	int		x;
	int		y;
	int		yAdd;
	int		xAdd;
	bool	b;

	y = coup._y;
	x = coup._x;
	yAdd = 0;
	xAdd = 0;
	b = false;
	if (coup._alignH >= 5)
	{
		xAdd = -1;
		b = this->_checkTaken(x, y, xAdd, yAdd, board);
	}
	if (coup._alignV >= 5 && !b)
	{
		yAdd = -1;
		b = this->_checkTaken(x, y, xAdd, yAdd, board);
	}
	if (coup._alignD1 >= 5 && !b)
	{
		xAdd = 1;
		yAdd = -1;
		b = this->_checkTaken(x, y, xAdd, yAdd, board);
	}
	if (coup._alignD2 >= 5 && !b)
	{
		xAdd = -1;
		yAdd = -1;
		b = this->_checkTaken(x, y, xAdd, yAdd, board);
	}
	return (b);
}

bool			ClassicRule::_checkTaken(int x, int y, int xAdd, int yAdd, t_matrix & board)
{
	int		n;

	_canBeTakenImmuneX = -1;
	_canBeTakenImmuneY = -1;
	//printf("Checking taken at x:%d, y%d with direction x:%d, y:%d for player %d\n", x, y, xAdd, yAdd, _playerNum);
	while (y >= 0 && x >= 0 && y < 19 && x < 19 && board[y][x] == _playerNum)
	{
		//printf("Rerolling taken x:%d, y%d\n", x, y);
		y += yAdd;
		x += xAdd;
	}
	xAdd *= -1;
	yAdd *= -1;
	n = 0;
	y += yAdd;
	x += xAdd;
	while (y >= 0 && x >= 0 && y < 19 && x < 19 && board[y][x] == _playerNum)
	{
		//printf("Checking taken x:%d, y%d\n", x, y);
		if (this->_canBeTaken(x, y, board))
			n = 0;
		else
			n++;
		//printf("n = %d\n", n);
		x += xAdd;
		y += yAdd;
	}
	if (n >= 5)
		return (true);
	return (false);
}

bool			ClassicRule::_checkDFeed(int x, int y, t_matrix & board, int playerNum)
{
	int		otherPlayerNum;

	otherPlayerNum = playerNum == 1 ? 2 : 1;
	if (y > 1 && y < 18 && x < 17 && x > 0)
	{
		if (board[y - 1][x + 1] == playerNum &&
				board[y - 2][x + 2] == otherPlayerNum &&
				board[y + 1][x - 1] == otherPlayerNum)
			return (true);
	}
	if (x > 1 && x < 18 && y < 17 && y > 0)
	{
		if (board[y + 1][x - 1] == playerNum &&
				board[y - 1][x + 1] == otherPlayerNum &&
				board[y + 2][x - 2] == otherPlayerNum)
			return (true);
	}
	if (y > 0 && y < 17 && x < 17 && x > 0)
	{
		if (board[y + 1][x + 1] == playerNum &&
				board[y + 2][x + 2] == otherPlayerNum &&
				board[y - 1][x - 1] == otherPlayerNum)
			return (true);
	}
	if (y > 1 && y < 18 && x < 18 && x > 1)
	{
		if (board[y - 1][x - 1] == playerNum &&
				board[y - 2][x - 2] == otherPlayerNum &&
				board[y + 1][x + 1] == otherPlayerNum)
			return (true);
	}
	return (false);
}

bool				ClassicRule::_checkVFeed(int x, int y, t_matrix & board, int playerNum)
{
	int		otherPlayerNum;

	otherPlayerNum = playerNum == 1 ? 2 : 1;
	if (y < 18 && y > 1)
	{
		if (board[y + 1][x] == otherPlayerNum &&
				board[y - 1][x] == playerNum &&
				board[y - 2][x] == otherPlayerNum)
			return (true);
	}
	if (y > 0 && y < 17)
	{
		if (board[y + 1][x] == playerNum &&
				board[y + 2][x] == otherPlayerNum &&
				board[y - 1][x] == otherPlayerNum)
			return (true);
	}
	return (false);
}

bool				ClassicRule::_checkHFeed(int x, int y, t_matrix & board, int playerNum)
{
	int		otherPlayerNum;

	otherPlayerNum = playerNum == 1 ? 2 : 1;
	if (x < 18 && x > 1)
	{
		if (board[y][x + 1] == otherPlayerNum &&
				board[y][x - 1] == playerNum &&
				board[y][x - 2] == otherPlayerNum)
			return (true);
	}
	if (x > 0 && x < 17)
	{
		if (board[y][x + 1] == playerNum &&
				board[y][x + 2] == otherPlayerNum &&
				board[y][x - 1] == otherPlayerNum)
			return (true);
	}
	return (false);
}

bool				ClassicRule::_feed(int x, int y, t_matrix & board, int playerNum)
{
	//debugs("checkHFeed");
	if (this->_checkHFeed(x, y, board, playerNum))
		return (true);
	//debugs("checkVFeed");
	if (this->_checkVFeed(x, y, board, playerNum))
		return (true);
	//debugs("checkDeed");
	if (this->_checkDFeed(x, y, board, playerNum))
		return (true);
	//debugs("Checked");
	return (false);
}

bool		ClassicRule::validPlay(int x, int y, t_matrix & board, int playerNum)
{
	if (this->_feed(x, y, board, playerNum))
		return (false);
	else if (this->_checkDFT(x, y, board, playerNum))
		return (false);
	return (true);
}

bool		ClassicRule::validPlay(int x, int y, t_matrix & board, Player *player)
{
	std::string		error;

	_playerNum = player->getNum();
	_otherPlayerNum = _playerNum == 1 ? 2 : 1;
	if (y < 0 || y > 18 || x < 0 || x > 18)
		error = "Bad play: out of the board";
	else if (board[y][x] == 1 || board[y][x] == 2)
		error = "Bad play";
	else if (this->_feed(x, y, board, _playerNum))
		error = "Feed";
	else if (this->_checkDFT(x, y, board, _playerNum))
		error = "Double Free Three";
	if (!error.empty())
	{
		this->setError(error);
		return (false);
	}
	return (true);
}

bool			ClassicRule::_canBeTakenMessage(int x, int y, int player, int err)
{
	std::string		str;

	(void)player;
	(void)err;
	str = "Pawn: x:" + to_string(x) + ", y:" + to_string(y) + " is not safe";
	this->setWarning(str);
	return (true);
}

bool			ClassicRule::_checkImmune(int y, int x, t_matrix & board)
{
	if (_canBeTakenImmuneX >= 0 && _canBeTakenImmuneY >= 0 &&
		x == _canBeTakenImmuneX && y == _canBeTakenImmuneY)
		return (false);
	if (board[y][x] != _otherPlayerNum)
		return (false);
	return (true);
}

bool			ClassicRule::_canBeTaken(int x, int y, t_matrix & board)
{
	//Check si en bas pote et en haut 0 et en 2 bas adv
	if (y < 17 && y > 0)
	{
		if (board[y + 1][x] == _playerNum &&
				_checkImmune(y + 2, x, board) &&
				board[y - 1][x] == 0 &&
				this->validPlay(x, y - 1, board, _otherPlayerNum))
			return (this->_canBeTakenMessage(x, y, _playerNum, 1));
	}
	//Check si en haut pote et en bas 0 et en 2 haut adv
	if (y < 18 && y > 1)
	{
		if (board[y - 1][x] == _playerNum &&
				_checkImmune(y - 2, x, board) &&
				board[y + 1][x] == 0 &&
				this->validPlay(x, y + 1, board, _otherPlayerNum))
			return (this->_canBeTakenMessage(x, y, _playerNum, 2));
	}
	//check si a gauche pote et a 2 gauche 0 et a droite adv
	if (x > 1 && x < 18)
	{
		if (board[y][x - 1] == _playerNum &&
				_checkImmune(y, x + 1, board) &&
				board[y][x - 2] == 0 &&
				this->validPlay(x - 2, y, board, _otherPlayerNum))
			return (this->_canBeTakenMessage(x, y, _playerNum, 3));
	}
	//check si a droite pote et a gauche 0 et deux a droite adv
	if (x < 17 && x > 0)
	{
		if (board[y][x + 1] == _playerNum &&
				_checkImmune(y, x + 2, board) &&
				board[y][x - 1] == 0 &&
				this->validPlay(x - 1, y, board, _otherPlayerNum))
			return (this->_canBeTakenMessage(x, y, _playerNum, 4));
	}
	//check si en bas droite pote et 2 bas droite 0 et haut gauche adv
	if (y < 17 && y > 0 && y && x < 17 && x > 0)
	{
		if (board[y + 1][x + 1] == _playerNum &&
				_checkImmune(y - 1, x - 1, board) &&
				board[y + 2][x + 2] == 0 &&
				this->validPlay(x + 2, y + 2, board, _otherPlayerNum))
			return (this->_canBeTakenMessage(x, y, _playerNum, 5));
	}
	//check si en haut gauche pote et 2 haut gauche 0 et bas droite adv
	if (y > 1 && y < 18 && x > 1 && x < 18)
	{
		if (board[y - 1][x - 1] == _playerNum &&
				_checkImmune(y + 1, x + 1, board) &&
				board[y - 2][x - 2] == 0 &&
				this->validPlay(x - 2, y - 2, board, _otherPlayerNum))
			return (this->_canBeTakenMessage(x, y, _playerNum, 6));
	}
	//check si en haut droite pote et bas gauche 0 et 2 bas gauche adv
	if (y < 17 && y > 0 && x > 1 && x < 18)
	{
		if (board[y - 1][x + 1] == _playerNum &&
				_checkImmune(y + 2, x - 2, board) &&
				board[y + 1][x - 1] == 0 &&
				this->validPlay(x - 1, y + 1, board, _otherPlayerNum))
			return (this->_canBeTakenMessage(x, y, _playerNum, 7));
	}
	if (y < 17 && y > 0 && x < 18 && x > 1)
	{
		if (board[y + 1][x - 1] == _playerNum &&
				_checkImmune(y - 1, x + 1, board) &&
				board[y + 2][x - 2] == 0 &&
				this->validPlay(x - 2, y + 2, board, _otherPlayerNum))
			return (this->_canBeTakenMessage(x, y, _playerNum, 8));
	}
	//	------------------------------------------------
	if (y < 17 && y > 0)
	{
		if (board[y + 1][x] == _playerNum &&
				_checkImmune(y - 1, x, board) &&
				board[y + 2][x] == 0 &&
				this->validPlay(x, y + 2, board, _otherPlayerNum))
			return (this->_canBeTakenMessage(x, y, _playerNum, 9));
	}
	if (y < 18 && y > 1)
	{
		if (board[y - 1][x] == _playerNum &&
				_checkImmune(y + 1, x, board) &&
				board[y - 2][x] == 0 &&
				this->validPlay(x, y - 2, board, _otherPlayerNum))
			return (this->_canBeTakenMessage(x, y, _playerNum, 10));
	}
	if (x > 1 && x < 19)
	{
		if (board[y][x - 1] == _playerNum &&
				_checkImmune(y, x - 2, board) &&
				board[y][x + 1] == 0 &&
				this->validPlay(x + 1, y, board, _otherPlayerNum))
			return (this->_canBeTakenMessage(x, y, _playerNum, 11));
	}
	if (x < 17 && x > 0)
	{
		if (board[y][x + 1] == _playerNum &&
				_checkImmune(y, x - 1, board) &&
				board[y][x + 2] == 0 &&
				this->validPlay(x + 2, y, board, _otherPlayerNum))
			return (this->_canBeTakenMessage(x, y, _playerNum, 12));
	}
	if (y < 17 && y > 0 && y && x < 17 && x > 0)
	{
		if (board[y + 1][x + 1] == _playerNum &&
				_checkImmune(y + 2, x + 2, board) &&
				board[y - 1][x - 1] == 0 &&
				this->validPlay(x - 1, y - 1, board, _otherPlayerNum))
			return (this->_canBeTakenMessage(x, y, _playerNum, 13));
	}
	if (y > 1 && y < 18 && x > 1 && x < 18)
	{
		if (board[y - 1][x - 1] == _playerNum &&
				_checkImmune(y - 2, x - 2, board) &&
				board[y + 1][x + 1] == 0 &&
				this->validPlay(x + 1, y + 1, board, _otherPlayerNum))
			return (this->_canBeTakenMessage(x, y, _playerNum, 14));
	}
	if (y < 17 && y > 1 && x > 0 && x < 17)
	{
		if (board[y - 1][x + 1] == _playerNum &&
				_checkImmune(y + 1, x - 1, board) &&
				board[y - 2][x + 2] == 0 &&
				this->validPlay(x + 2, y - 2, board, _otherPlayerNum))
			return (this->_canBeTakenMessage(x, y, _playerNum, 15));
	}
	if (y < 17 && y > 0 && x < 18 && x > 1)
	{
		if (board[y + 1][x - 1] == _playerNum &&
				_checkImmune(y + 2, x - 2, board) &&
				board[y - 1][x + 1] == 0 &&
				this->validPlay(x + 1, y - 1, board, _otherPlayerNum))
			return (this->_canBeTakenMessage(x, y, _playerNum, 16));
	}
	return (false);
}

void		ClassicRule::_checkHFT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems)
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

void		ClassicRule::_checkVFT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems)
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

void		ClassicRule::_checkD1FT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems)
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

void		ClassicRule::_checkD2FT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems)
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

void		ClassicRule::_checkFT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems)
{
	if (board[y][x])
		return ;
	//debugs("HFT");
	_checkHFT(x, y, board, playerNum, elems);
	//debugs("VFT");
	_checkVFT(x, y, board, playerNum, elems);
	//debugs("D1FT");
	_checkD1FT(x, y, board, playerNum, elems);
	//debugs("D2FT");
	_checkD2FT(x, y, board, playerNum, elems);
	//debugs("End");
}

void		printElems(std::map<std::pair<int, int>, int> & elems, t_matrix & board)
{
	std::map<std::pair<int, int>, int>::iterator it = elems.begin();

	for (it = elems.begin(); it != elems.end(); ++it)
	{
		std::cout << "(" <<  to_string(it->first.first) << "," << to_string(it->first.second) << ")";
		std::cout << " = " << to_string(it->second) << std::endl;
	}
	(void)board;
}

bool		ClassicRule::_checkDFT(int x, int y, t_matrix & board, int playerNum)
{
	int					maxX;
	int					maxY;
	int					minX;
	int					minY;
	int					tmpX;
	int					tmpY;
	std::map<std::pair<int, int>, int>				elems;
	std::map<std::pair<int, int>, int>::iterator	it;

	if (board[y][x])
		return (false);
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
