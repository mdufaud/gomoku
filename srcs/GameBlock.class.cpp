/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameBlock.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 17:31:17 by mdufaud           #+#    #+#             */
/*   Updated: 2016/07/01 16:00:38 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameBlock.class.hpp"
#include "Graph.class.hpp"
#include "ClassicRule.class.hpp"
#include "AlignRule.class.hpp"
#include "Player.class.hpp"
#include "Board.class.hpp"
#include "InfoBlock.class.hpp"
#include "LogBlock.class.hpp"
#include "PlayerSelect.class.hpp"
#include "IA.class.hpp"
#include "GameInterface.class.hpp"
#include "GameState.class.hpp"
#include <thread>
#include "Rules.class.hpp"
#include <unistd.h>

GameBlock::GameBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string text,
					std::string background): ABlock(graph, blockDef, text, background)
{
	_player1 = NULL;
	_player2 = NULL;
	_rule = NULL;
	_ia = NULL;
	_infoBlock = NULL;
	_iaPlay = false;
	this->init("Player One", "Player Two");
	_backgroundRect.w = _background->w;
	_backgroundRect.h = _background->h;
	_scrollY = 0;
	_scrollX = 0;
	_blockSize = 15;
	_interBlocks = 52;
	_start_x = 32;
	_start_y = 32;
	_end_x = 970;
	_end_y = 970;
	_type = GAMEBLOCK_TYPE;
	_font = _graph->getFont(BOARD_FONT);

	_whitePawnTexture = SDL_CreateTextureFromSurface(_graph->getRenderer(),
										_graph->getSurface(GO_WHITE_PAWN_BMP));
	_blackPawnTexture = SDL_CreateTextureFromSurface(_graph->getRenderer(),
										_graph->getSurface(GO_BLACK_PAWN_BMP));
	_pawnRect.w = _graph->getSurface(GO_BLACK_PAWN_BMP)->w;
	_pawnRect.h = _graph->getSurface(GO_BLACK_PAWN_BMP)->h;

	_suggestedWhitePawnTexture = SDL_CreateTextureFromSurface(_graph->getRenderer(),
										_graph->getSurface(SUGGESTED_WHITE_BMP));
	_suggestedBlackPawnTexture = SDL_CreateTextureFromSurface(_graph->getRenderer(),
										_graph->getSurface(SUGGESTED_BLACK_BMP));
	this->setBoardNums();
}

GameBlock::~GameBlock()
{
	SDL_DestroyTexture(_whitePawnTexture);
	SDL_DestroyTexture(_blackPawnTexture);
	delete _ia;
	delete _rule;
	delete _player1;
	delete _player2;
	_iaThread.join();
}

void	GameBlock::setIaDepth(int depth)
{
	_ia->setDepth(depth);
}

void	GameBlock::setRule(int rule)
{
	Rules	*r;

	r = NULL;
	delete _rule;
	if (rule == 1)
		r = new ClassicRule();
	else if (rule == 2)
		r = new AlignRule();
	_rule = r;
	_board.setRule(r);
}

void	GameBlock::init(std::string p1, std::string p2)
{
	_loggedStat = true;
	_selectable = true;
	_infoBlock = NULL;
	_logBlock = NULL;
	_timeToPlay = 0;
	_gameState.clear();
	_gameStateIndex = 0;
	_lastClock = time(0);
	_autoPlay = false;
	_activatedHelp = false;
	_suggestedPlay = playPair(-1, -1);
	_lastTime = time(0);
	if (_iaThread.joinable())
		_iaThread.join();
	_board = Board(_rule);
	delete _player1;
	if (p1.empty())
		p1 = "Player One";
	_player1 = new Player(1, p1);
	delete _player2;
	if (p2.empty())
		p2 = "Player Two";
	_player2 = new Player(2, p2);
	delete _ia;
	_ia = new IA(_rule, _player1, _player2, 4);
	_playerTurn = (rand() % 2) == 0 ? _player1 : _player2;
	this->addState();
}

void	GameBlock::start(bool ia)
{
	_iaPlay = ia;
	if (_iaPlay && _playerTurn == _player2)
		this->playIA();
}

void	GameBlock::addState(void)
{
	GameState		g(_player1, _player2, _playerTurn, _board);

	_gameState.push_front(g);
	_gameStateIndex = 0;
}

void	GameBlock::loadState(gameStateList::iterator it)
{
	if (_ia->isLocked())
	{
		if (_iaThread.joinable())
		{
			_iaThread.join();
			_ia->getPlayerPlay();
		}
	}
	_suggestedPlay = playPair(-1, -1);
	_activatedHelp = false;
	_loggedStat = true;
	_iaPlay = false;

	_board = (*it)._board;
	delete _player1;
	_player1 = new Player((*it)._p1);
	_player1->setName((*it)._p1->getName());

	delete _player2;
	_player2 = new Player((*it)._p2);
	_player2->setName((*it)._p2->getName());

	_playerTurn = (*it)._pTurn == (*it)._p1 ? _player1 : _player2;
	_infoBlock->setPlayer(_player1);
	_infoBlock->setPlayer(_player2);
	_infoBlock->setPlayerTurn(_playerTurn);
	_ia->setPlayers(_player1, _player2);
	_rule->emptyWarning();
	_infoBlock->emptyWarning();
	_rule->emptyError();
	_infoBlock->emptyError();
	if (_autoPlay)
		this->autoPlay();
	//if (_iaPlay && _playerTurn == _player2)
	//	this->playIA();
}

void	GameBlock::loadPrevState(void)
{
	gameStateList::iterator		it = _gameState.begin();
	int							i;

	if (_ia->isLocked())
		return ;
	i = 0;
	_gameStateIndex++;
	while (i < _gameStateIndex && it != _gameState.end())
	{
		it++;
		i++;
	}
	if (it ==_gameState.end())
	{
		_gameStateIndex--;
		return ;
	}
	if (_board.getWinner() > 0)
		static_cast<GameInterface *>(_graph->getMenu(GOMOKU_GAME_INTERFACE))->unsetWinner();
	this->loadState(it);
	_logBlock->addLog("Reloaded previous move");
}

void	GameBlock::loadNextState(void)
{
	gameStateList::iterator		it = _gameState.begin();
	int							i;

	if (_ia->isLocked())
		return ;
	if (!_gameStateIndex)
		return ;
	_gameStateIndex--;
	i = 0;
	while (i < _gameStateIndex && it != _gameState.end())
	{
		it++;
		i++;
	}
	if (it ==_gameState.end())
	{
		_gameStateIndex++;
		return ;
	}
	this->loadState(it);
	if (_board.getWinner() > 0)
		static_cast<GameInterface *>(_graph->getMenu(GOMOKU_GAME_INTERFACE))->setWinner(_board.getWinner() > 0);
	_logBlock->addLog("Reloaded next move");
}

void	GameBlock::deleteStates(void)
{
	int							i;
	int							until;

	if (_ia->isLocked())
		return ;
	until = _gameStateIndex;
	i = 0;
	while (i < until)
	{
		_gameState.pop_front();
		i++;
		_gameStateIndex--;
	}
}

void	GameBlock::logIaStats(void)
{
	t_iaStats			stat;
	std::string			s;
	std::ostringstream	stream;

	if (_ia->isLocked() || _loggedStat)
		return ;
	_ia->getStats(&stat);
	stream << "Total Moves: "
		<< stat.nMoves
		<< " ( "
		<< stat.erasedMoves
		<< " erased)\n"
		<< "    "
		<< stat.nNodes
		<< " got to the end\n"
		<< "    "
		<< stat.cutNodes
		<< " cutted nodes with "
		<< stat.cutOffs
		<< " alphaBeta cutoffs\n"
		<< "    "
		<< stat.percentCutOffs
		<< " % of cutted nodes";
	s = stream.str();
	if (_logBlock)
		_logBlock->addLog(s);
	_loggedStat = true;
}

void	GameBlock::logPlay(int x, int y)
{
	std::string		s;

	if (x >= 0 && y >= 0)
	{
		s = _playerTurn->getName() + std::string(" played at x: ");
		s += to_string(x) + std::string(", y: ") + to_string(y);
		if ((_iaPlay && _playerTurn == _player2) || (_autoPlay))
		{
			std::ostringstream	stream;

			stream << " (Played in: " << _thinkTime << "s)";
			s += stream.str();
		}
		else
		{
			s += std::string(" (thinked for : ") + to_string(_timeToPlay);
			s += std::string(" seconds)");
		}
	}
	else
		s = _playerTurn->getName() + std::string(" passes his turn");
	if (_logBlock)
		_logBlock->addLog(s);
}

void	GameBlock::play(int x, int y)
{
	if (x >= 0 && y >= 0 && _board.valid(x, y, _playerTurn))
	{
		_board.playNoVerif(x, y, _playerTurn);
		time_t t = time(0);
		_timeToPlay = difftime(t, _lastClock);
		this->logPlay(x, y);
		this->changePlayerTurn();
		this->deleteStates();
		this->addState();
		_lastClock = t;
	}
	else if ((_autoPlay || (_iaPlay && _playerTurn == _player2)) && (x < 0 && y < 0))
	{
		this->logPlay(x, y);
		this->changePlayerTurn();
	}
	if (_board.getWinner() > 0)
		static_cast<GameInterface *>(_graph->getMenu(GOMOKU_GAME_INTERFACE))->setWinner(_board.getWinner());
	if (_rule->isError())
	{
		_infoBlock->setError(_rule->getError());
		_logBlock->addLog(_rule->getError());
	}
	else
		_infoBlock->emptyError();
	if (_rule->isWarning())
	{
		_infoBlock->setWarning(_rule->getWarning());
		_logBlock->addLog(_rule->getWarning());
	}
	else
		_infoBlock->emptyWarning();
	if (_rule->isInfo())
		_logBlock->addLog(_rule->getInfo());
	/*printf("%s played at x:%d, y:%d\n", _playerTurn->getName().c_str(), x, y);
	printPuzzle(_board.getBoard());
	std::cout << "Board value for P1: " << _board.getBoardValueP1() << std::endl;
	std::cout << "Board value for P2: " << _board.getBoardValueP2() << std::endl;
	*/
}

bool	GameBlock::action(int x, int y)
{
	int		board_x;
	int		board_y;

	if (_autoPlay || (_iaPlay && _playerTurn == _player2))
		return (false);
	if (x < _start_x - _blockSize || y < _start_y - _blockSize
			|| x > _end_x + _blockSize  || y > _end_y + _blockSize)
		return (false);
	this->getBoardPos(x, y, &board_x, &board_y);
	//printf("Clicked at board x = %d and y = %d\n", board_x, board_y);
	this->play(board_x, board_y);
	if (_iaPlay && _playerTurn == _player2)
		this->playIA();
	return (true);
}

playPair	GameBlock::getPlayIA()
{
	if (_iaThread.joinable())
		_iaThread.join();

	playPair	play = _ia->getPlayerPlay();
	clock_t		end = clock();

	_infoBlock->setPlayerThinking(_playerTurn, false);
	if (_playerTurn->getNum() == 1)
		_thinkTime = double(end - _playerOneClock) / CLOCKS_PER_SEC;
	if (_playerTurn->getNum() == 2)
		_thinkTime = double(end - _playerTwoClock) / CLOCKS_PER_SEC;
	_infoBlock->setPlayerThinkTime(_playerTurn, _thinkTime);
	_loggedStat = false;
	return (play);
}

void		GameBlock::activateHelp(int depth)
{
	if (_suggestedPlay.first < 0)
	{
		_activatedHelp = true;
		this->playDepthIA(depth);
	}
}

void		GameBlock::playDepthIA(int depth)
{
	if (!_board.getWinner() && _ia->isLocked() == false)
	{
		if (_iaThread.joinable())
			_iaThread.join();
		if (_playerTurn->getNum() == 1)
			_playerOneClock = clock();
		else if (_playerTurn->getNum() == 2)
			_playerTwoClock = clock();
		_iaThread = std::thread(&IA::thinkDepth, _ia, _playerTurn, &_board, depth);
		_infoBlock->setPlayerThinking(_playerTurn, true);
		usleep(500);
	}
}

void		GameBlock::playIA()
{
	if (!_board.getWinner() && _ia->isLocked() == false)
	{
		if (_iaThread.joinable())
			_iaThread.join();
		if (_playerTurn->getNum() == 1)
			_playerOneClock = clock();
		else if (_playerTurn->getNum() == 2)
			_playerTwoClock = clock();
		_iaThread = std::thread(&IA::think, _ia, _playerTurn, &_board);
		_infoBlock->setPlayerThinking(_playerTurn, true);
		usleep(500);
	}
}

void	GameBlock::draw()
{
	int				y;
	int				x;
	t_matrix		board = _board.getBoard();
	int				printX;
	int				printY;

	this->getPlayerPalys();
	SDL_RenderCopy(_graph->getRenderer(), _backgroundTexture, NULL, &_backgroundRect);
	y = 0;	
	while (y < 19)
	{
		x = 0;
		while (x < 19)
		{
			this->printBoardNums(y, x);
			if (board[y][x] > 0)
			{
				this->getRealPos(x, y, &printX, &printY);
				_pawnRect.x = printX - _pawnRect.w / 2 + _scrollX;
				_pawnRect.y = printY - _pawnRect.h / 2 + _scrollY;
				if (board[y][x] == 2)
					SDL_RenderCopy(_graph->getRenderer(), _whitePawnTexture, NULL, &_pawnRect);
				else if (board[y][x] == 1)
					SDL_RenderCopy(_graph->getRenderer(), _blackPawnTexture, NULL, &_pawnRect);
			}
			x++;
		}
		y++;
	}
	if (_suggestedPlay.first >= 0)
	{
		this->getRealPos(_suggestedPlay.first, _suggestedPlay.second, &printX, &printY);
		_pawnRect.x = printX - _pawnRect.w / 2 + _scrollX;
		_pawnRect.y = printY - _pawnRect.h / 2 + _scrollY;
		if (_playerTurn == _player1)
			SDL_RenderCopy(_graph->getRenderer(), _suggestedBlackPawnTexture, NULL, &_pawnRect);
		else
			SDL_RenderCopy(_graph->getRenderer(), _suggestedWhitePawnTexture, NULL, &_pawnRect);
	}
}

void	GameBlock::getPlayerPalys(void)
{
	if (_iaPlay && _playerTurn == _player2 && !_board.getWinner() && _ia->isLocked() == false)
	{
		playPair	play = this->getPlayIA();

		//std::cout << "Alpha Gad play : x: " << play.first << ", y: " << play.second << std::endl;
		this->play(play.first, play.second);
		if (_playerTurn == _player2)
			this->changePlayerTurn();
	}
	else if ((!_iaPlay || (_iaPlay && _playerTurn == _player1)) &&
				_activatedHelp && !_board.getWinner() && _ia->isLocked() == false)
	{
		_suggestedPlay = this->getPlayIA();

		//printf("Got suggested play : x:%d, y:%d\n", _suggestedPlay.first, _suggestedPlay.second);
		_activatedHelp = false;
		if (_autoPlay && _suggestedPlay.first >= 0)
		{
			this->play(_suggestedPlay.first, _suggestedPlay.second);
			_activatedHelp = true;
			this->playIA();
		}
	}
}

void	GameBlock::changePlayerTurn(void)
{
	_playerTurn = _playerTurn == _player1 ? _player2 : _player1;
	if (_infoBlock)
		this->_infoBlock->setPlayerTurn(_playerTurn);
	_suggestedPlay = playPair(-1, -1);
	_activatedHelp = false;
}

void		GameBlock::activateIA(void)
{
	if (_ia->isLocked())
		return ;
	if (time(0) - _lastTime < 1)
		return ;
	_iaPlay = _iaPlay == true ? false : true;
	if (_iaPlay)
		_logBlock->addLog("Activated IA.");
	else
		_logBlock->addLog("Deactivated IA.");
	if (_iaPlay && _playerTurn == _player2)
		this->playIA();
	_lastTime = time(0);
}

void	GameBlock::autoPlay(void)
{
	if (time(0) - _lastTime < 1)
		return ;
	_autoPlay = _autoPlay == true ? false : true;
	_iaPlay = false;
	if (_autoPlay)
	{
		_logBlock->addLog("Activated auto play.");
		_activatedHelp = true;
		this->playIA();
	}
	else
	{
		_logBlock->addLog("Deactivated auto play.");
		//if (_iaThread.joinable())
		//	_iaThread.join();
		_infoBlock->setPlayerThinking(_playerTurn, false);
		_activatedHelp = false;
		_suggestedPlay = playPair(-1, -1);
	}
	_lastTime = time(0);
}

void	GameBlock::setBoardNums(void)
{
	textureMatrix	boardNums(19);
	int				i;
	std::string		num;
	SDL_Color		black = {0, 0, 0, 0};

	i = 0;
	while (i < (int)boardNums.size())
	{
		num = to_string(i);
		boardNums[i] = NULL;
		this->setMessage(&boardNums[i], num, _font, black);
		i++;
	}
	_boardNums = boardNums;
}

void	GameBlock::setInfoBlock(InfoBlock *block)
{
	_infoBlock = block;
}

void	GameBlock::setLogBlock(LogBlock *block)
{
	_logBlock = block;
}

Player	*GameBlock::getPlayer(int num)
{
	if (num == 1)
		return (_player1);
	else if (num == 2)
		return (_player2);
	return (NULL);
}

Player	*GameBlock::getPlayerTurn(void)
{
	return (_playerTurn);
}

void	GameBlock::setPlayerName(int num, std::string name)
{
	size_t	first;
	size_t	last;

	if (name.empty())
		return ;
	first = name.find_first_not_of(' ');
	last = name.find_last_not_of(' ');
	name = name.substr(first, (last - first + 1));
	if (name.empty())
		return ;
	if (name.empty())
		return ;
	if (num == 1)
		_player1->setName(name);
	else if (num == 2)
		_player2->setName(name);
}

void	GameBlock::scrollUp(void)
{
	int		y;

	y = 10;
	if (_scrollY < 0)
	{
		y = MIN(-_scrollY, y);
		_scrollY += y;
		_backgroundRect.y += y;
	}
}

void	GameBlock::scrollDown(void)
{
	int		y;

	y = 10;
	if (_logBlock->getBackgroundRect().y + _logBlock->getBackgroundRect().h > _graph->getH())
	{
		y = MIN(_logBlock->getBackgroundRect().y + _logBlock->getBackgroundRect().h - (_graph->getH()), y);
		_scrollY -= y;
		_backgroundRect.y -= y;
	}
}

void	GameBlock::scrollLeft(void)
{
	int		x;

	x = 10;
	if (_scrollX < 0)
	{
		x = MIN(-_scrollX, x);
		_scrollX += x;
		_backgroundRect.x += x;
	}
}

void	GameBlock::scrollRight(void)
{
	int		x;

	x = 10;
	if (_infoBlock->getBackgroundRect().x + _infoBlock->getBackgroundRect().w > _graph->getW() - 40)
	{
		x = MIN(_infoBlock->getBackgroundRect().x + _infoBlock->getBackgroundRect().w - (_graph->getW() - 40), x);
		_scrollX -= x;
		_backgroundRect.x -= x;
	}
}

void	GameBlock::getBoardPos(int x, int y, int *bx, int *by)
{
	int		bx_start;
	int		bx_end;
	int		by_start;
	int		by_end;

	x = x - _start_x - _scrollX;
	y = y - _start_y - _scrollY;
	*bx = (x + _blockSize) / _interBlocks;
	*by = (y + _blockSize) / _interBlocks;
	bx_start = *bx * _interBlocks - _blockSize;
	bx_end = *bx * _interBlocks + _blockSize;
	by_start = *by * _interBlocks - _blockSize;
	by_end = *by * _interBlocks + _blockSize;
	if (x < bx_start || x > bx_end || y < by_start || y > by_end)
	{
		*bx = -1;
		*by = -1;
	}
}

void	GameBlock::setBackgroundRect(SDL_Rect rect)
{
	_backgroundRect.x = rect.x;
	_backgroundRect.y = rect.y;
	_backgroundRect.w = _background->w;
	_backgroundRect.h = _background->h;
}

void	GameBlock::getRealPos(int x, int y, int *rx, int *ry)
{
	x = (x * _interBlocks);
	y = (y * _interBlocks);
	*rx = x + _start_x;
	*ry = y + _start_y;
}

void	GameBlock::printBoardNums(int y, int x)
{
	SDL_Rect	rect;
	std::string	s;

	if (!y && !x)
	{
		s = to_string(0);
		this->setMessageFontRect(s, _font, &rect);
		rect.x = _start_x + _scrollX - rect.w / 2;
		rect.y = _start_y + _scrollY - rect.h - _pawnRect.h / 2 + 2;
		SDL_RenderCopy(_graph->getRenderer(), _boardNums[0], NULL, &rect);
		rect.x = _start_x + _scrollX - rect.w - _pawnRect.w / 2;
		rect.y = _start_y + _scrollY - rect.h / 2;
		SDL_RenderCopy(_graph->getRenderer(), _boardNums[0], NULL, &rect);
	}
	else if (!y && x)
	{
		s = to_string(x);
		this->setMessageFontRect(s, _font, &rect);
		rect.x = _start_x + _scrollX + (_interBlocks * x) - rect.w / 2;
		rect.y = _start_y + _scrollY - rect.h - _pawnRect.h / 2 + 2;
		SDL_RenderCopy(_graph->getRenderer(), _boardNums[x], NULL, &rect);
	}
	else if (y && !x)
	{
		s = to_string(y);
		this->setMessageFontRect(s, _font, &rect);
		rect.x = _start_x + _scrollX - rect.w - _pawnRect.w / 2;
		rect.y = _start_y + _scrollY + (_interBlocks * y) - rect.h / 2;
		SDL_RenderCopy(_graph->getRenderer(), _boardNums[y], NULL, &rect);
	}
}
