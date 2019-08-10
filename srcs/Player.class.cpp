/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 17:50:54 by rcherik           #+#    #+#             */
/*   Updated: 2016/04/28 16:59:45 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.class.hpp"

Player::Player(void)
{
	_num = 0;
	_cap = 0;
	_nbCoups = 0;
}

Player::~Player(void)
{
}

Player::Player(int num, std::string name) : _num(num), _name(name)
{
	_cap = 0;
	_nbCoups = 0;
}

Player::Player(Player *player)
{
	_num = player->getNum();
	_cap = player->getCap();
	_nbCoups = player->getNbCoups();
}

void		Player::setName(std::string name)
{
	_name = name;
}

void		Player::setCap(int cap)
{
	_cap = cap;
}

std::string &	Player::getName(void)
{
	return (this->_name);
}

int		Player::getNum(void)
{
	return (this->_num);
}

int		Player::getNbCoups(void)
{
	return (this->_nbCoups);
}

void	Player::incNbCoups(void)
{
	this->_nbCoups += 1;
}

int		Player::getCap(void)
{
	return (this->_cap);
}
void	Player::incCap(void)
{
	this->_cap = this->_cap + 1;
}
