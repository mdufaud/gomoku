/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rules.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 16:41:15 by rcherik           #+#    #+#             */
/*   Updated: 2016/04/28 17:34:49 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rules.class.hpp"

Rules::Rules(void)
{
	_isError = false;
	_isInfo = false;
	_isWarning = false;
}

Rules::~Rules(void) {}

void		Rules::setInfo(std::string info)
{
	_isInfo = true;
	if (!_info.empty())
		_info += std::string("\n") + info;
	else
		_info = info;
}
void		Rules::emptyInfo()
{
	if (_isInfo)
	{
		_isInfo = false;
		_info = std::string("");
	}
}

bool		Rules::isInfo()
{
	return (_isInfo);
}

std::string	Rules::getInfo()
{
	return (_info);
}

void	Rules::setError(std::string error)
{
	_isError = true;
	_error = error;
}

void	Rules::setWarning(std::string warning)
{
	_isWarning = true;
	_warning = warning;
}

void	Rules::emptyWarning()
{
	if (_isWarning)
	{
		_isWarning = false;
		_warning = std::string("");
	}
}

void	Rules::emptyError()
{
	if (_isError)
	{
		_isError = false;
		_error = std::string("");
	}
}

bool	Rules::isWarning()
{
	return (_isWarning);
}

bool	Rules::isError()
{
	return (_isError);
}

std::string	Rules::getError()
{
	return (_error);
}

std::string	Rules::getWarning()
{
	return (_warning);
}
