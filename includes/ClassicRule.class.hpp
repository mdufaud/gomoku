/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassicRule.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 15:51:52 by rcherik           #+#    #+#             */
/*   Updated: 2016/04/28 17:30:29 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSICRULE_CLASS_HPP
# define CLASSICRULE_CLASS_HPP

# include "Rules.class.hpp"
# include <iostream>
# include <math.h>
# include <map>

typedef std::vector< std::vector<int> > t_matrix;
typedef std::vector<int>		t_matrixLine;

class Coup;

class ClassicRule : public Rules
{
	public:

		ClassicRule(void);
		~ClassicRule(void);

		bool		gameOver(Player *player, t_matrix & board, Coup & coup);
		bool		validPlay(int x, int y, t_matrix & board, int playerNum);
		bool		validPlay(int x, int y, t_matrix & board, Player *player);
		int			heuristic(Board *board, int xPlay, int yPlay, Player *player);
		int			checkCapture(int x, int y, Player *player, t_matrix & board);

	private:
		void			infoCap(int x1, int y1, int x2, int y2, Player *player);
		bool			_canBeTakenMessage(int x, int y, int player, int err);
		bool			_checkHFeed(int x, int y, t_matrix & board, int playerNum);
		bool			_checkVFeed(int x, int y, t_matrix & board, int playerNum);
		bool			_checkDFeed(int x, int y, t_matrix & board, int playerNum);
		bool			_feed(int x, int y, t_matrix & board, int playerNum);
		bool			_canBeTaken(int x, int y, t_matrix & board);
		bool			_checkIfCantBeTaken(t_matrix & board, Coup & coup);
		bool			_checkIfCaptureWin(t_matrix & board, Coup & coup);
		bool			_checkCaptureWin(int x1, int y1, int x2, int y2, t_matrix & board);
		bool			_checkTaken(int x, int y, int xAdd, int yAdd, t_matrix & board);
		bool			_checkWinAround(int x, int y, t_matrix & board);
		bool			_checkWinDirection(int x, int y, int xAdd, int yAdd, t_matrix & board);
		bool			_checkCapturable(int x, int y, t_matrix & board);
		bool			_checkCaptureDirection(int x, int y, int xAdd, int yAdd, t_matrix & board);
		bool			_checkIfUndoCapture(t_matrix & board, Coup & coup);
		bool			_checkImmune(int y, int x, t_matrix & board);
		void			_checkD1FT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems);
		void			_checkD2FT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems);
		void			_checkHFT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems);
		void			_checkVFT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems);
		void			_checkFT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems);
		bool			_checkDFT(int x, int y, t_matrix & board, int playerNum);

		int				_checkHCapture(int x, int y, Player *player, t_matrix & board);
		int				_checkVCapture(int x, int y, Player *player, t_matrix & board);
		int				_checkDCapture(int x, int y, Player *player, t_matrix & board);



		t_matrix		_board;
		int				_playerNum;
		int				_otherPlayerNum;
		int				_canBeTakenImmuneX;
		int				_canBeTakenImmuneY;
};

#endif
