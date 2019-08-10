/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Coup.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 16:01:10 by rcherik           #+#    #+#             */
/*   Updated: 2016/07/01 15:54:37 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Coup.class.hpp"
#include "gomoku.hpp"

Coup::Coup(void) {}

Coup::~Coup(void) {}

Coup::Coup(int x, int y, t_matrix & board, Player *player) : _x(x), _y(y)
{
	_player = player;
	_board = board;
	_alignV = 0;
	_spaceLeftH = 0;
	_spaceRightH = 0;

	_alignH = 0;
	_spaceLeftV = 0;
	_spaceRightV = 0;

	_alignD1 = 0;
	_spaceLeftD1 = 0;
	_spaceRightD1 = 0;

	_alignD2 = 0;
	_spaceLeftD2 = 0;
	_spaceRightD2 = 0;

	_capV = 0;
	_capH = 0;
	_capD1 = 0;
	_capD2 = 0;

	_value = 0;

	_playerNum = player->getNum();
	_otherPlayerNum = _playerNum == 1 ? 2 : 1;
}

Coup::Coup(int x, int y, t_matrix & board) : _x(x), _y(y)
{
	_player = NULL;
	_board = board;
	_alignV = 0;
	_spaceLeftH = 0;
	_spaceRightH = 0;

	_alignH = 0;
	_spaceLeftV = 0;
	_spaceRightV = 0;

	_alignD1 = 0;
	_spaceLeftD1 = 0;
	_spaceRightD1 = 0;

	_alignD2 = 0;
	_spaceLeftD2 = 0;
	_spaceRightD2 = 0;

	_capV = 0;
	_capH = 0;
	_capD1 = 0;
	_capD2 = 0;

	_value = 0;

	_otherPlayerNum = _playerNum == 1 ? 2 : 1;
	this->_calcPreValue();
}

bool		Coup::isValid(void)
{
	if (_board[_y][_x] == _playerNum)
		return (true);
	return (false);
}

void		Coup::_tryVAlign(void)
{
	_tmpY = _y;
	while (_tmpY >= 0 && _board[_tmpY][_x] == _playerNum)
		_tmpY--;
	while (_tmpY >= 0 && (!_board[_tmpY][_x])) //|| _board[_tmpY][_x] == _playerNum))
	{
		_tmpY--;
		_spaceLeftV++;
	}
	_tmpY += _spaceLeftV;
	_tmpY++;
	while (_tmpY < 19 && _board[_tmpY][_x] == _playerNum)
	{
		_tmpY++;
		_alignV++;
	}
	while (_tmpY < 19 && !_board[_tmpY][_x])
	{
		_tmpY++;
		_spaceRightV++;
	}
}

void		Coup::_tryHAlign(void)
{
	_tmpX = _x;
	while (_tmpX >= 0 && _board[_y][_tmpX] == _playerNum)
		_tmpX--;
	while (_tmpX >= 0 && !_board[_y][_tmpX])
	{
		_tmpX--;
		_spaceLeftH++;
	}
	_tmpX += _spaceLeftH;
	_tmpX++;
	while (_tmpX < 19 && _board[_y][_tmpX] == _playerNum)
	{
		_tmpX++;
		_alignH++;
	}
	while (_tmpX < 19 && !_board[_y][_tmpX])
	{
		_tmpX++;
		_spaceRightH++;
	}
}

void		Coup::_tryD1Align(void)
{
	_tmpY = _y;
	_tmpX = _x;
	while (_tmpY < 19 && _tmpX >= 0 && _board[_tmpY][_tmpX] == _playerNum)
	{
		_tmpX--;
		_tmpY++;
	}
	while (_tmpY < 19 && _tmpX >= 0 && !_board[_tmpY][_tmpX])
	{
		_tmpX--;
		_tmpY++;
		_spaceLeftD1++;
	}
	_tmpX += _spaceLeftD1;
	_tmpY -= _spaceLeftD1;
	_tmpX++;
	_tmpY--;
	while (_tmpX < 19 && _tmpY >= 0 && _board[_tmpY][_tmpX] == _playerNum)
	{
		_tmpX++;
		_tmpY--;
		_alignD1++;
	}
	while (_tmpX < 19 && _tmpY >= 0 && !_board[_tmpY][_tmpX])
	{
		_tmpX++;
		_tmpY--;
		_spaceRightD1++;
	}
}

void		Coup::_tryD2Align(void)
{
	_tmpY = _y;
	_tmpX = _x;
	while (_tmpY >= 0 && _tmpX >= 0 && _board[_tmpY][_tmpX] == _playerNum)
	{
		_tmpX--;
		_tmpY--;
	}
	while (_tmpY >= 0 && _tmpX >= 0 && !_board[_tmpY][_tmpX])
	{
		_tmpX--;
		_tmpY--;
		_spaceLeftD2++;
	}
	_tmpX += _spaceLeftD2;
	_tmpY += _spaceLeftD2;
	_tmpX++;
	_tmpY++;
	while (_tmpX < 19 && _tmpY < 19 && _board[_tmpY][_tmpX] == _playerNum)
	{
		_tmpX++;
		_tmpY++;
		_alignD2++;
	}
	while (_tmpX < 19 && _tmpY < 19 && !_board[_tmpY][_tmpX])
	{
		_tmpX++;
		_tmpY++;
		_spaceRightD2++;
	}
}

void		Coup::tryAlign(void)
{
	_tryVAlign();
	_tryHAlign();
	_tryD2Align();
	_tryD1Align();
}

void		Coup::_checkVCapture(void)
{
	if (_y < 16)
	{
		if (_board[_y + 1][_x]  == _otherPlayerNum &&
				_board[_y + 2][_x]  == _otherPlayerNum &&
				_board[_y + 3][_x] == _playerNum)
			_capV += 1;
	}
	if (_y > 2)
	{
		if (_board[_y - 1][_x]  == _otherPlayerNum &&
				_board[_y - 2][_x]  == _otherPlayerNum &&
				_board[_y - 3][_x] == _playerNum)
			_capV += 1;
	}
}

void		Coup::_checkHCapture(void)
{
	if (_x < 16)
	{
		if (_board[_y][_x + 1]  == _otherPlayerNum &&
				_board[_y][_x + 2]  == _otherPlayerNum &&
				_board[_y][_x + 3] == _playerNum)
			_capH += 1;
	}
	if (_x > 2)
	{
		if (_board[_y][_x - 1]  == _otherPlayerNum &&
				_board[_y][_x - 2]  == _otherPlayerNum &&
				_board[_y][_x - 3] == _playerNum)
			_capH += 1;
	}
}

void		Coup::_checkDCapture(void)
{
	if (_x < 16 && _y < 16)
	{
		if (_board[_y + 1][_x + 1]  == _otherPlayerNum &&
				_board[_y + 2][_x + 2]  == _otherPlayerNum &&
				_board[_y + 3][_x + 3] == _playerNum)
			_capD2 += 1;
	}
	if (_y > 2 && _x > 2)
	{
		if (_board[_y - 1][_x - 1]  == _otherPlayerNum &&
				_board[_y - 2][_x - 2]  == _otherPlayerNum &&
				_board[_y - 3][_x - 3] == _playerNum)
			_capD2 += 1;
	}
	if (_y < 16 && _x > 2)
	{
		if (_board[_y + 1][_x - 1]  == _otherPlayerNum &&
				_board[_y + 2][_x - 2] == _otherPlayerNum &&
				_board[_y + 3][_x - 3] == _playerNum)
			_capD1 += 1;
	}
	if (_y > 2 && _x < 16)
	{
		if (_board[_y - 1][_x + 1]  == _otherPlayerNum &&
				_board[_y - 2][_x + 2]  == _otherPlayerNum &&
				_board[_y - 3][_x + 3] == _playerNum)
			_capD1 += 1;
	}
}

void		Coup::checkCapture(void)
{
	_checkHCapture();
	_checkVCapture();
	_checkDCapture();
}

int		Coup::getValue(void)
{
	return (_value);
}

void		Coup::_preHAlign(void)
{
	_tmpX = _x + 1;
	if (_tmpX < 19)
		_p = _board[_y][_tmpX];
	while (_tmpX < 19 && _board[_y][_tmpX] == _p && _board[_y][_tmpX])
	{
		_spaceRightH++;
		_tmpX++;
	}
	_tmpX = _x - 1;
	if (_tmpX >= 0)
		_p = _board[_y][_tmpX];
	while (_tmpX >= 0 && _board[_y][_tmpX] == _p && _board[_y][_tmpX])
	{
		_spaceLeftH++;
		_tmpX--;
	}
}

void		Coup::_preVAlign(void)
{
	_tmpY = _y + 1;
	if (_tmpY < 19)
		_p = _board[_tmpY][_x];
	while (_tmpY < 19 && _board[_tmpY][_x] == _p && _board[_tmpY][_x])
	{
		_spaceRightV++;
		_tmpY++;
	}
	_tmpY = _y - 1;
	if (_tmpY >= 0)
		_p = _board[_tmpY][_x];
	while (_tmpY >= 0 && _board[_tmpY][_x] == _p && _board[_tmpY][_x])
	{
		_spaceLeftV++;
		_tmpY--;
	}
}

void		Coup::_preD1Align(void)
{
	_tmpX = _x + 1;
	_tmpY = _y - 1;
	if (_tmpX < 19 && _tmpY >= 0)
		_p = _board[_tmpY][_tmpX];
	while (_tmpX < 19 && _tmpY >= 0 && _board[_tmpY][_tmpX] == _p && _board[_tmpY][_tmpX])
	{
		_spaceRightD1++;
		_tmpX++;
		_tmpY--;
	}
	_tmpX = _x - 1;
	_tmpY = _y + 1;
	if (_tmpX >= 0 && _tmpY < 19)
		_p = _board[_tmpY][_tmpX];
	while (_tmpX >= 0 && _tmpY < 19 && _board[_tmpY][_tmpX] == _p && _board[_tmpY][_tmpX])
	{
		_spaceLeftD1++;
		_tmpX--;
		_tmpY++;
	}
}

void		Coup::_preD2Align(void)
{
	_tmpX = _x + 1;
	_tmpY = _y + 1;
	if (_tmpX < 19 && _tmpY < 19)
		_p = _board[_tmpY][_tmpX];
	while (_tmpX < 19 && _tmpY < 19 && _board[_tmpY][_tmpX] == _p && _board[_tmpY][_tmpX])
	{
		_spaceRightD2++;
		_tmpX++;
		_tmpY++;
	}
	_tmpX = _x - 1;
	_tmpY = _y - 1;
	if (_tmpX >= 0 && _tmpY >= 0)
		_p = _board[_tmpY][_tmpX];
	while (_tmpX >= 0 && _tmpY >= 0 && _board[_tmpY][_tmpX] == _p && _board[_tmpY][_tmpX])
	{
		_spaceLeftD2++;
		_tmpX--;
		_tmpY--;
	}
}

void		Coup::_preCap(void)
{
	if (_spaceRightH == 2)
	{
		if (_x + 3 < 19 && _board[_y][_x + 3] != _board[_y][_x + 1])
			_capH++;
	}
	if (_spaceLeftH == 2)
	{
		if (_x - 3 >= 0 && _board[_y][_x - 3] != _board[_y][_x - 1])
			_capH++;
	}
	if (_spaceRightV == 2)
	{
		if (_y + 3 < 19 && _board[_y + 3][_x] != _board[_y + 1][_x])
			_capV++;
	}
	if (_spaceLeftV == 2)
	{
		if (_y - 3 >= 0 && _board[_y - 3][_x] != _board[_y - 1][_x])
			_capH++;
	}
	if (_spaceRightD1 == 2)
	{
		if (_x - 3 >= 0 && _y + 3 < 19 && _board[_y + 3][_x - 3] != _board[_y + 1][_x - 1])
			_capD1++;
	}
	if (_spaceLeftD1 == 2)
	{
		if (_y - 3 >= 0 && _x + 3 < 19 && _board[_y - 3][_x + 3] != _board[_y - 1][_x + 1])
			_capD1++;
	}
	if (_spaceRightD2 == 2)
	{
		if (_x + 3 < 19 && _y + 3 < 19 && _board[_y + 3][_x + 3] != _board[_y + 1][_x + 1])
			_capD2++;
	}
	if (_spaceLeftD2 == 2)
	{
		if (_x - 3 >= 0 && _y - 3 >= 0 && _board[_y - 3][_x - 3] != _board[_y - 1][_x - 1])
			_capD2++;
	}
}

void		Coup::_calcPreValue(void)
{
	_preHAlign();
	_preVAlign();
	_preD1Align();
	_preD2Align();
	_preCap();
	_value = (_capH + _capV + _capD1 + _capD2) * MODIFIER_PRE_CAP;
	_value += pow(_spaceRightV + _spaceLeftV, 3) * MODIFIER_V;
	_value += pow(_spaceRightH + _spaceLeftH, 3) * MODIFIER_H;
	_value += pow(_spaceRightD1 + _spaceLeftD1, 3) * MODIFIER_D1;
	_value += pow(_spaceRightD2 + _spaceLeftD2, 3) * MODIFIER_D2;
}

bool		Coup::operator()(Coup left, Coup right)
{
	return (left.getValue() < right.getValue());
}

void		Coup::calcValue(void)
{
	int			v;

	_value += pow(_alignV, 3) * MODIFIER_V;
	_value += pow(_alignH, 3) * MODIFIER_H;
	_value += pow(_alignD1, 3) * MODIFIER_D1;
	_value += pow(_alignD2, 3) * MODIFIER_D2;
	_checkSpace(_spaceLeftV, _spaceRightV, _alignV);
	_checkSpace(_spaceLeftH, _spaceRightH, _alignH);
	_checkSpace(_spaceLeftD1, _spaceRightD1, _alignD1);
	_checkSpace(_spaceLeftD2, _spaceRightD2, _alignD2);
	v = _player->getCap() ? _player->getCap() : 1;
	_value += ((_capV + _capH + _capD1 + _capD2) * MODIFIER_CAP) * v;
}

void		Coup::calcAlignValue(void)
{
	int			v;

	_value += pow(_alignV, 3) * MODIFIER_V;
	_value += pow(_alignH, 3) * MODIFIER_H;
	_value += pow(_alignD1, 3) * MODIFIER_D1;
	_value += pow(_alignD2, 3) * MODIFIER_D2;
	_checkAlignSpace(_spaceLeftV, _spaceRightV, _alignV);
	_checkAlignSpace(_spaceLeftH, _spaceRightH, _alignH);
	_checkAlignSpace(_spaceLeftD1, _spaceRightD1, _alignD1);
	_checkAlignSpace(_spaceLeftD2, _spaceRightD2, _alignD2);
	v = _player->getCap() ? _player->getCap() : 1;
	_value += ((_capV + _capH + _capD1 + _capD2) * MODIFIER_CAP) * v;
}

void		Coup::_checkAlignSpace(int left, int right, int align)
{
	if (align + left + right >= 5)
		_value += _value / 2;
	else
		return ;
	if (left > 0 && right > 0)
		_value *= 4;
	else
		_value = 0;
}

void		Coup::_checkSpace(int left, int right, int align)
{
	if (align + left + right >= 5)
		_value += _value / 2;
	else
		return ;
	if (align == 3 && left > 0 && right > 0)
		_value *= 4;
}

void		Coup::printState(void)
{
	if (_player)
	{
		printf("Coup: (x:%d, y:%d) for player %d\n", _x, _y, _player->getNum());
		printf("\talignV:  %d - Left: %d | Right: %d\n \
\talignH:  %d - Left: %d | Right: %d\n \
\talignD1: %d - Left: %d | Right: %d\n \
\talignD2: %d - Left: %d | Right: %d\n\t",
						_alignV, _spaceLeftV, _spaceRightV,
						_alignH, _spaceLeftH, _spaceRightH,
						_alignD1, _spaceLeftD1, _spaceRightD1,
						_alignD2, _spaceLeftD2, _spaceRightD2);
		printf("captureV = %d - captureH = %d - captureD1 = %d - caputreD2 = %d\n", _capV, _capH, _capD1, _capD2);
		printf("Value = %d\n", _value);
	}
	else
	{
		printf("Coup: (x:%d, y:%d)\n", _x, _y);
		printf("\tAV : Left: %d | Right: %d && AH : Left: %d | Right: %d\n \
\tAD1: Left: %d | Right: %d && AD2: Left: %d | Right: %d\n",
				_spaceLeftV, _spaceRightV,
				_spaceLeftH, _spaceRightH,
				_spaceLeftD1, _spaceRightD1,
				_spaceLeftD2, _spaceRightD2);
		printf("CapV = %d - capH = %d - capD1 = %d - capD2 = %d\n", _capV, _capH, _capD1, _capD2);
		printf("Value = %d\n\n", _value);
	}
}
