/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigMenu.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2016/07/01 13:57:03 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigMenu.class.hpp"
#include "MenuBlock.class.hpp"
#include "TextBlock.class.hpp"
#include "BoolBlock.class.hpp"
#include "LogBlock.class.hpp"
#include "Graph.class.hpp"

ConfigMenu::ConfigMenu(Graph *graph) : AInterface(graph, GOMOKU_CONFIG_MENU)
{
	_classicRule = NULL;
	_alignRule = NULL;
	generateBlocks();
}

ConfigMenu::~ConfigMenu()
{
}

int			ConfigMenu::getRule(void)
{
	int		ret;

	if (_classicRule && _classicRule->getBool())
		ret = 1;
	if (_alignRule && _alignRule->getBool())
		ret = 2;
	return (ret);
}

bool		ConfigMenu::click(int x, int y)
{
	bool	before = _classicRule->getBool();
	bool	b = AInterface::click(x, y);

	if (!_classicRule->getBool() && !_alignRule->getBool())
			_classicRule->setBool();
	else if (_classicRule->getBool() && _alignRule->getBool())
	{
		if (before)
			_classicRule->setBool();
		else
			_alignRule->setBool();
	}
	return (b);
}

void		ConfigMenu::keyReturn(SDL_Event e)
{
	bool	before = _classicRule->getBool();

	AInterface::keyReturn(e);
	if (!_classicRule->getBool() && !_alignRule->getBool())
			_classicRule->setBool();
	else if (_classicRule->getBool() && _alignRule->getBool())
	{
		if (before)
			_classicRule->setBool();
		else
			_alignRule->setBool();
	}
}

void	ConfigMenu::generateBlocks(void)
{
	SDL_Rect		tmpRect;
	std::string		name;
	int				y;
	int				x;
	int				w;
	int				h;
	bool			align;

	align = false;
	if (_alignRule)
		align = _alignRule->getBool();
	if (_blocks)
		this->deleteBlocks();
	_blocks = new Blocklist();

	y = 10;
	x = 10;

	name = "Configuration";
	h = _graph->getH() / 5;
	w = _graph->getW() - 20;
	tmpRect = make_rect(x, y, w, h);
	ABlock	*header = new TextBlock(_graph, tmpRect, name, BACKGROUND_BMP);
	header->setFontID(HEADER_FONT);
	header->setFontStyle(TTF_STYLE_BOLD);
	_blocks->push_back(header);

	y += h + _graph->getH() / 10;
	x = _graph->getW() - (_graph->getW() / 4) * 2 - (_graph->getW() / 6) * 2;

	name = "Classic Rule";
	h = _graph->getH() / 7;
	w = _graph->getW() / 4;
	tmpRect = make_rect(x, y, w, h);
	ABlock *classicRule = new BoolBlock(_graph, tmpRect, name);
	_classicRule = static_cast<BoolBlock *>(classicRule);
	if (!align)
		_classicRule->setBool();
	_blocks->push_back(classicRule);

	name = "RULE DESCRIPTION";
	tmpRect = make_rect(x + 50, y + h + 50, _graph->getW() / 3, h);
	ABlock	*classicRuleDescription = new LogBlock(_graph, tmpRect, name);
	static_cast<LogBlock *>(classicRuleDescription)->addLog("To win: ");
	static_cast<LogBlock *>(classicRuleDescription)->addLog("Align 5 safe pawns or make 5 captures");
	static_cast<LogBlock *>(classicRuleDescription)->addLog("No double free three");
	_blocks->push_back(classicRuleDescription);

	y += 0;
	x += w + _graph->getW() / 6;

	name = "Align Rule";
	h = _graph->getH() / 7;
	w = _graph->getW() / 4;
	tmpRect = make_rect(x, y, w, h);
	ABlock *alignRule = new BoolBlock(_graph, tmpRect, name);
	_alignRule = static_cast<BoolBlock *>(alignRule);
	if (align)
		_alignRule->setBool();
	_blocks->push_back(alignRule);

	y += h + 50;

	name = "RULE DESCRIPTION";
	tmpRect = make_rect(x + 50, y, _graph->getW() / 3, h);
	ABlock	*alignRuleDescription = new LogBlock(_graph, tmpRect, name);
	static_cast<LogBlock *>(alignRuleDescription)->addLog("To win: ");
	static_cast<LogBlock *>(alignRuleDescription)->addLog("Align 5 with spaces left and right");
	static_cast<LogBlock *>(alignRuleDescription)->addLog("No double free three");
	_blocks->push_back(alignRuleDescription);

	y += h + 50;
	x = _graph->getW() / 2 - (_graph->getW() / (5 * 2)) - _graph->getW() / 10;

	name = "Return to main menu";
	h = _graph->getH() / 8;
	w = _graph->getW() / 5 + _graph->getW() / 5;
	tmpRect = make_rect(x, y, w, h);
	ABlock	*mainMenu = new MenuBlock(_graph, tmpRect, name, BACKGROUND_BMP, GOMOKU_MAIN_MENU);
	_blocks->push_back(mainMenu);

	classicRule->setClockBlock(mainMenu, alignRule, mainMenu, alignRule);
	alignRule->setClockBlock(classicRule, classicRule, mainMenu, classicRule);
	mainMenu->setClockBlock(alignRule, NULL, classicRule, NULL);
}

void	ConfigMenu::recalc_draw(void)
{
	generateBlocks();
}
