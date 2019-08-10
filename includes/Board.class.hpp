/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Board.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:00:34 by rcherik           #+#    #+#             */
/*   Updated: 2016/04/28 17:13:09 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_CLASS_HPP
# define BOARD_CLASS_HPP

# include <vector>
# include <iostream>
# include "Player.class.hpp"
# include "Rules.class.hpp"

class Rules;

typedef std::vector< std::vector<int> > t_matrix;
typedef std::vector<int>				t_matrixLine;
typedef std::pair<int, int>				playPair;

class Board
{
	public:
		Board(Rules *rule);
		Board(Board & board);
		Board(void);
		~Board(void);

		int				calcHeur(int x, int y, Player *player);
		t_matrix		getBoard(void);
		t_matrix &		getBoard(int i);
		void			setBoard(t_matrix & board);
		bool			play(int x, int y, Player *player);
		bool			playNoVerif(int x, int y, Player *player);
		bool			valid(int x, int y, Player *player);
		bool			gameOver(Player *player);
		void			setRule(Rules *rule);
		void			setHeuristic(int h);
		int				calcHeuristic(int xPlay, int yPlay, Player *player);
		void			setWinner(int winner);

		Board			operator=(Board *board);
		Board &			operator=(Board & rhs);
		Board &			operator=(Board const & rhs);
		playPair		getLastPlayP1(void);
		playPair		getLastPlayP2(void);
		playPair		getLastPlayP(int n);
		int				getBoardValueP1(void);
		int				getBoardValueP2(void);
		int				getHeuristic(void);
		Rules			*getRule(void);
		int				getWinner();
		int				getBoardValueP(int n);

		playPair		getLastPlayP1(void) const;
		playPair		getLastPlayP2(void) const;
		playPair		getLastPlayP(int n) const;
		int				getBoardValueP1(void) const;
		int				getBoardValueP2(void) const;
		int				getHeuristic(void) const;
		Rules			*getRule(void) const;
		int				getWinner() const;
		bool			getClear(void) const;
		int				getBoardValueP(int n) const;
		t_matrix		getBoard(void) const;
		int				getPawns(void);

		void			removePawns(int n);

	private:
		t_matrix		_board;
		Rules			*_rule;
		int				_win;
		int				_nPawns;
		bool			_clear;

		int				_playerNum;
		int				_otherPlayerNum;
		playPair		_lastPlayP1;
		playPair		_lastPlayP2;
		int				_boardValueP1;
		int				_boardValueP2;
		int				_heuristic;

		bool			_feed(int x, int y, Player *player);
		bool			_checkFull(void);
};

#endif
