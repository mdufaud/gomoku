/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AInterface.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 18:28:16 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/17 19:14:20 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AInterface.class.hpp"
#include "Graph.class.hpp"
#include "InputBlock.class.hpp"

AInterface::AInterface(Graph *graph, int type)
{
	_type = type;
	_graph = graph;
	_blocks = NULL;
	_selectedBlockID = -1;
	_hooveredBlockID = -1;
}

AInterface::~AInterface(void)
{
	this->deleteBlocks();
}

void		AInterface::draw()
{
	Blocklist::iterator		it = _blocks->begin();

	while (it != _blocks->end())
	{
		if ((*it)->isHidden() == false)
			(*it)->draw();
		it++;
	}
}

bool		AInterface::hoover(int x, int y)
{
	Blocklist::iterator		it = _blocks->begin();

	it = _blocks->begin();
	if (_hooveredBlockID >= 0)
	{
		ABlock	*block = this->getBlockID(_hooveredBlockID);

		if (block)
			block->unhoover();
		_hooveredBlockID = -1;
	}
	while (it != _blocks->end())
	{
		if ((*it)->isInBlock(x, y) && (*it)->isSelectable())
		{
			_hooveredBlockID = (*it)->hoovered();
			break ;
		}
		it++;
	}
	return (false);
}

bool		AInterface::click(int x, int y)
{
	Blocklist::iterator		it = _blocks->begin();

	if (_selectedBlockID >= 0)
	{
		ABlock	*block = this->getBlockID(_selectedBlockID);

		if (block)
			block->unselect();
		_selectedBlockID = -1;
	}
	while (it != _blocks->end())
	{
		if ((*it)->isInBlock(x, y) && (*it)->isSelectable())
		{
			_selectedBlockID = (*it)->selected();
			//printf("Clicked on block id: %d with name: %s\n", _selectedBlockID, (*it)->getText().c_str());
			(*it)->action(x, y);
			break ;
		}
		it++;
	}
	return (false);
}

void		AInterface::resetSelectedBlocks(void)
{
	_selectedBlockID = -1;
	_hooveredBlockID = -1;
}

void		AInterface::deleteBlocks()
{
	if (!_blocks)
		return ;

	Blocklist::iterator		it = _blocks->begin();

	while (it != _blocks->end())
	{
		delete (*it);
		it++;
	}
	_blocks->clear();
	delete _blocks;
	_blocks = NULL;
}

ABlock			*AInterface::getBlockName(std::string name) const
{
	Blocklist::iterator	it = _blocks->begin();

	while (it != _blocks->end())
	{
		if ((*it)->getText() == name)
			return ((*it));
		it++;
	}
	return (NULL);
}

ABlock		*AInterface::getBlockID(int id) const
{
	Blocklist::iterator	it = _blocks->begin();

	while (it != _blocks->end())
	{
		if ((*it)->getID() == id)
			return ((*it));
		it++;
	}
	return (NULL);
}

Graph			*AInterface::getGraph(void) const
{
	return (this->_graph);
}

Blocklist		*AInterface::getBlocks(void) const
{
	return (this->_blocks);
}

int				AInterface::getType(void) const
{
	return (this->_type);
}

AInterface		*AInterface::operator=(AInterface *rhs)
{
	if (this != rhs)
	{
		this->_type = rhs->getType();
		this->_blocks = new Blocklist(rhs->getBlocks()->size());
		for (std::size_t i = 0; i < rhs->getBlocks()->size(); ++i)
			this->_blocks[i] = rhs->getBlocks()[i];
		this->_graph = rhs->getGraph();
	}
	return (this);
}

void		AInterface::parseKey(SDL_Event e)
{
	switch (e.type)
	{
		case SDL_TEXTINPUT:
		{
			Blocklist::iterator	it = _blocks->begin();

			while (it != _blocks->end())
			{
				if ((*it)->getID() == _selectedBlockID)
				{
					if ((*it)->getType() == INPUTBLOCK_TYPE)
					{
						InputBlock	*cast = static_cast<InputBlock *>((*it));
						cast->addText(e.text.text);
					}
					break ;
				}
				it++;
			}
			break ;
		}
		case SDL_TEXTEDITING:
		{
			/*
			printf("TEXT EDIT");
			int composition = event.edit.text;
			int cursor = event.edit.start;
			int selection_len = event.edit.length;
			*/
			break;
		}
		case SDL_KEYDOWN:
		{
			this->keyDownEvent(e);
			break ;
		}
		default:
			break ;
	}
}

void		AInterface::keyDownEvent(SDL_Event e)
{
	if (_selectedBlockID < 0 && _hooveredBlockID >= 0)
		_selectedBlockID = _hooveredBlockID;
	switch (e.key.keysym.sym)
	{
		case SDLK_DOWN:
			this->keyDown(e);
			break ;
		case SDLK_UP:
			this->keyUp(e);
			break ;
		case SDLK_LEFT:
			this->keyLeft(e);
			break ;
		case SDLK_RIGHT:
			this->keyRight(e);
			break ;
		case SDLK_RETURN:
			this->keyReturn(e);
			break ;
		case SDLK_BACKSPACE:
			this->keyBackspace(e);
			break ;
	}
}

void		AInterface::keyRight(SDL_Event e)
{
	(void)e;
	if (_selectedBlockID >= 0)
	{
		ABlock	*block = this->getBlockID(_selectedBlockID);

		if (block && block->getRightBlock())
		{
			block->unselect();
			_selectedBlockID = block->getRightBlock()->selected();
		}
	}
}

void		AInterface::keyLeft(SDL_Event e)
{
	(void)e;
	if (_selectedBlockID >= 0)
	{
		ABlock	*block = this->getBlockID(_selectedBlockID);

		if (block && block->getLeftBlock())
		{
			block->unselect();
			_selectedBlockID = block->getLeftBlock()->selected();
		}
	}
}

void		AInterface::keyUp(SDL_Event e)
{
	(void)e;
	if (_selectedBlockID >= 0)
	{
		ABlock	*block = this->getBlockID(_selectedBlockID);

		if (block && block->getUpBlock())
		{
			block->unselect();
			_selectedBlockID = block->getUpBlock()->selected();
		}
	}
	else
	{
		Blocklist::iterator	it = _blocks->end() - 1;

		while (it != _blocks->begin() && !(*it)->isSelectable())
			it--;
		if (it != _blocks->begin())
			_selectedBlockID = (*it)->selected();
	}
}

void		AInterface::keyDown(SDL_Event e)
{
	(void)e;
	if (_selectedBlockID >= 0)
	{
		ABlock	*block = this->getBlockID(_selectedBlockID);

		if (block && block->getDownBlock())
		{
			block->unselect();
			_selectedBlockID = block->getDownBlock()->selected();
		}
	}
	else
	{
		Blocklist::iterator	it = _blocks->begin();

		while (it != _blocks->end() && !(*it)->isSelectable())
			it++;
		if (it != _blocks->end())
			_selectedBlockID = (*it)->selected();
	}
}

void		AInterface::keyReturn(SDL_Event e)
{
	Blocklist::iterator	it = _blocks->begin();

	(void)e;
	while (it != _blocks->end())
	{
		if ((*it)->getID() == _selectedBlockID
			|| ((*it)->getID() == _hooveredBlockID
				&& _selectedBlockID < 0))
		{
			(*it)->unselect();
			_selectedBlockID = -1;
			(*it)->action((*it)->getBackgroundRect().x,
							(*it)->getBackgroundRect().y);
			break ;
		}
		it++;
	}
}

void		AInterface::keyBackspace(SDL_Event e)
{
	Blocklist::iterator	it = _blocks->begin();

	(void)e;
	while (it != _blocks->end())
	{
		if ((*it)->getID() == _selectedBlockID)
		{
			if ((*it)->getType() == INPUTBLOCK_TYPE)
			{
				InputBlock	*cast = static_cast<InputBlock *>((*it));
				cast->backDel();
			}
			break ;
		}
		it++;
	}
}
