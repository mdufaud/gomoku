/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AlignRule.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 15:51:52 by rcherik           #+#    #+#             */
/*   Updated: 2016/03/23 15:59:39 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIGNRULE_CLASS_HPP
# define ALIGNRULE_CLASS_HPP

# include "Rules.class.hpp"
# include <iostream>
# include <math.h>
# include <map>

typedef std::vector< std::vector<int> > t_matrix;
typedef std::vector<int>				t_matrixLine;

class Coup;

class AlignRule : public Rules
{
	public:

		AlignRule(void);
		~AlignRule(void);

		bool		gameOver(Player *player, t_matrix & board, Coup & coup);
		bool		validPlay(int x, int y, t_matrix & board);
		bool		validPlay(int x, int y, t_matrix & board, Player *player);
		int		heuristic(Board *board, int xPlay, int yPlay, Player *player);

	private:
		bool			_checkWinAround(int x, int y, t_matrix & board);
		bool			_checkWinDirection(int x, int y, int xAdd, int yAdd, t_matrix & board);
		void			_checkD1FT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems);
		void			_checkD2FT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems);
		void			_checkHFT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems);
		void			_checkVFT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems);
		void			_checkFT(int x, int y, t_matrix & board, int playerNum, std::map<std::pair<int, int>, int> & elems);
		bool			_checkDFT(int x, int y, t_matrix & board, int playerNum);


		t_matrix		_board;
		int			_playerNum;
		int			_otherPlayerNum;
};

#endif
