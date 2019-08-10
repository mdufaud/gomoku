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

#ifndef COUP_CLASS_HPP
# define COUP_CLASS_HPP

# include "Player.class.hpp"
# include <vector>
# include <stdio.h>
# include <math.h>
# include <queue>

# define MODIFIER_V 3
# define MODIFIER_H 4
# define MODIFIER_D1 5
# define MODIFIER_D2 6
# define MODIFIER_CAP 15000
# define MODIFIER_TRY_CAP 2000
# define MODIFIER_PRE_CAP 100

typedef std::vector< std::vector<int> > t_matrix;
typedef std::vector<int>				t_matrixLine;

class Coup
{
	public:
		Coup(void);
		Coup(int x, int y, t_matrix & board, Player *player);
		Coup(int x, int y, t_matrix & board);
		~Coup(void);

		bool		operator()(const Coup left, const Coup right);
		void		printState(void);
		int			getValue(void);
		void		calcValue(void);
		void		calcAlignValue(void);
		void		tryAlign(void);
		void		tryCapture(void);
		void		checkCapture(void);
		bool		isValid(void);

		int			_alignH;
		int			_spaceLeftH;
		int			_spaceRightH;

		int			_alignV;
		int			_spaceLeftV;
		int			_spaceRightV;

		int			_alignD1;
		int			_spaceLeftD1;
		int			_spaceRightD1;

		int			_alignD2;
		int			_spaceLeftD2;
		int			_spaceRightD2;

		int			_capV;
		int			_capH;
		int			_capD1;
		int			_capD2;

		int			_x;
		int			_y;
		int			_p;
		int			_value;

	private:

		t_matrix	_board;
		Player		*_player;
		int			_playerNum;
		int			_otherPlayerNum;
	
		int			_tmpX;
		int			_tmpY;

		void		_tryVAlign(void);
		void		_tryHAlign(void);
		void		_tryD1Align(void);
		void		_tryD2Align(void);

		void		_checkVCapture(void);
		void		_checkHCapture(void);
		void		_checkDCapture(void);
		void		_checkCapture(void);

		void		_tryHCapture(void);
		void		_tryVCapture(void);
		void		_tryD1Capture(void);
		void		_tryD2Capture(void);

		void		_checkSpace(int left, int right, int align);
		void		_checkAlignSpace(int left, int right, int align);

		void		_calcPreValue(void);
		void		_preCap(void);
		void		_preVAlign(void);
		void		_preHAlign(void);
		void		_preD1Align(void);
		void		_preD2Align(void);
};

#endif
