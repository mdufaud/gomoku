/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameBlock.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 17:31:15 by mdufaud           #+#    #+#             */
/*   Updated: 2016/04/28 17:58:27 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEBLOCK_CLASS_HPP
# define GAMEBLOCK_CLASS_HPP

# include "ABlock.class.hpp"
# include <ctime>
# include <vector>
# include <list>
# include <thread>

class	Graph;
class	InfoBlock;
class	LogBlock;
class	Board;
class	Rules;
class	Player;
class	IA;
class	GameState;

typedef std::vector<SDL_Texture *>	textureMatrix;
typedef std::list<GameState>		gameStateList;

class	GameBlock: public ABlock
{
	public:
		GameBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string text,
					std::string background);
		virtual ~GameBlock(void);

		void		play(int x, int y);
		bool		action(int x, int y);
		bool		hoovered();
		void		draw();
		void		recalc_draw();
		void		getRealPos(int x, int y, int *rx, int *ry);
		void		getBoardPos(int x, int y, int *bx, int *by);
		void		setBackgroundRect(SDL_Rect rect);
		void		setPlayerName(int num, std::string name);
		Player		*getPlayer(int num);
		Player		*getPlayerTurn(void);
		void		setInfoBlock(InfoBlock *block);
		void		setLogBlock(LogBlock *block);
		void		changePlayerTurn(void);
		void		printBoardNums(int y, int x);
		void		setBoardNums(void);

		void		init(std::string p1, std::string p2);
		void		start(bool ia);
		void		scrollDown(void);
		void		scrollUp(void);
		void		scrollLeft(void);
		void		scrollRight(void);


		void		playIA(void);
		void		playDepthIA(int depth);
		playPair	getPlayIA(void);
		void		activateIA(void);
		void		activateHelp(int depth);
		void		getPlayerPalys(void);
		void		autoPlay(void);
		void		logPlay(int x, int y);

		void		addState(void);
		void		loadPrevState(void);
		void		loadNextState(void);
		void		deleteStates(void);
		void		loadState(gameStateList::iterator it);

		void		setRule(int rule);
		void		setIaDepth(int depth);
		void		logIaStats(void);

	private:
		IA				*_ia;
		bool			_iaPlay;
		Player			*_player1;
		Player			*_player2;
		Player			*_playerTurn;
		Board			_board;
		Rules			*_rule;

		std::thread		_iaThread;
		double			_thinkTime;
		clock_t			_playerOneClock;
		clock_t			_playerTwoClock;

		InfoBlock		*_infoBlock;
		LogBlock		*_logBlock;
		int				_blockSize;
		int				_interBlocks;
		int				_scrollY;
		int				_scrollX;
		int				_start_x;
		int				_start_y;
		int				_end_x;
		int				_end_y;
		SDL_Rect		_pawnRect;
		SDL_Texture		*_whitePawnTexture;
		SDL_Texture		*_blackPawnTexture;
		SDL_Texture		*_suggestedWhitePawnTexture;
		SDL_Texture		*_suggestedBlackPawnTexture;
		textureMatrix	_boardNums;

		playPair		_suggestedPlay;
		bool			_activatedHelp;
		int				_lastTime;
		bool			_autoPlay;
		time_t			_lastClock;
		int				_timeToPlay;

		gameStateList	_gameState;
		int				_gameStateIndex;
		bool			_loggedStat;
};
#endif
