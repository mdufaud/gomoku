/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InfoBlock.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:57:27 by mdufaud           #+#    #+#             */
/*   Updated: 2016/04/28 18:09:28 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFOBLOCK_CLASS_HPP
# define INFOBLOCK_CLASS_HPP

# include "ABlock.class.hpp"
# include <time.h>

class	Graph;
class	Board;
class	Player;
class	LogBlock;

class	InfoBlock: public ABlock
{
	public:
		InfoBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string name,
					std::string background);
		virtual ~InfoBlock(void);

		InfoBlock		*operator=(InfoBlock *rhs);

		bool			action(int x, int y);
		void			draw();

		void			scrollDown(void);
		void			scrollUp(void);
		void			scrollLeft(void);
		void			scrollRight(void);
		void			setPlayer(Player *player);

		void			setInfosPlace(void);
		void			startInfos(Player *player1,
									Player *player2,
									Player *playerTurn);
		void			setTime(void);
		void			setBegin(time_t start);
		void			setCaps(Player *player);
		void			setCoups(Player *player);
		void			setPlayerTurn(Player *player);

		void			setWarning(std::string warning);
		void			emptyWarning(void);
		void			setError(std::string error);
		void			emptyError(void);
		void			stopTime(void);
		void			startTime(void);
		void			setPlayerThinking(Player *player, bool b);
		void			setPlayerThinkTime(Player *player, double d);
		void			playerThinkDot(void);
		void			setLogBlock(LogBlock *log);

	private:
		Player			*_player1;
		Player			*_player2;
		Player			*_playerTurn;

		time_t			_start;
		bool			_countTime;

		SDL_Rect		_backRect;

		SDL_Texture		*_blackPawnTexture;
		SDL_Texture		*_whitePawnTexture;
		SDL_Rect		_pawnRect;

		SDL_Texture		*_warningTexture;
		SDL_Rect		_warningRect;
		SDL_Texture		*_errorTexture;
		SDL_Rect		_errorRect;

		SDL_Rect		_playerOneRect;
		SDL_Rect		_playerTwoRect;

		SDL_Texture		*_turnTexture;
		SDL_Rect		_turnRect;
		SDL_Texture		*_timeTexture;
		SDL_Rect		_timeRect;
		SDL_Texture		*_playerOneNameTexture;
		SDL_Rect		_playerOneNameRect;
		SDL_Texture		*_playerTwoNameTexture;
		SDL_Rect		_playerTwoNameRect;
		SDL_Texture		*_playerOneCoupsTexture;
		SDL_Rect		_playerOneCoupsRect;
		SDL_Texture		*_playerTwoCoupsTexture;
		SDL_Rect		_playerTwoCoupsRect;
		SDL_Texture		*_playerOneCapsTexture;
		SDL_Rect		_playerOneCapsRect;
		SDL_Texture		*_playerTwoCapsTexture;
		SDL_Rect		_playerTwoCapsRect;

		SDL_Texture		*_playerTwoThinkingTexture;
		SDL_Rect		_playerTwoThinkingRect;
		SDL_Texture		*_playerOneThinkingTexture;
		SDL_Rect		_playerOneThinkingRect;
		bool			_playerOneThinking;
		bool			_playerTwoThinking;
		int				_playerThinkDot;

		SDL_Texture		*_playerTwoThinkTimeTexture;
		SDL_Rect		_playerTwoThinkTimeRect;
		SDL_Texture		*_playerOneThinkTimeTexture;
		SDL_Rect		_playerOneThinkTimeRect;

		int				_scrollY;
		int				_scrollX;
		LogBlock		*_logBlock;
};
#endif
