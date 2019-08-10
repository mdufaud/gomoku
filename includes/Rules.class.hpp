/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rules.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 15:45:45 by rcherik           #+#    #+#             */
/*   Updated: 2016/04/28 17:35:10 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RULES_CLASS_HPP
# define RULES_CLASS_HPP

# include "Player.class.hpp"
# include "Coup.class.hpp"
# include <vector>
# include <string>

typedef std::vector< std::vector<int> > t_matrix;
typedef std::vector<int>				t_matrixLine;

class Player;
class Board;

class Rules
{
	public:
		virtual ~Rules(void);
		Rules(void);
		virtual bool	gameOver(Player *player, t_matrix & board, Coup & coup) = 0;
		virtual bool	validPlay(int x, int y, t_matrix & board, Player *player) = 0;
		virtual int		heuristic(Board *board, int xPlay, int yPlay, Player *player) = 0;

		void			setInfo(std::string info);
		void			emptyInfo();
		bool			isInfo();
		std::string		getInfo();

		void			setWarning(std::string warning);
		void			emptyWarning();
		bool			isWarning();
		std::string		getWarning();

		void			setError(std::string error);
		void			emptyError();
		bool			isError();
		std::string		getError();

	protected:
		bool			_isInfo;
		bool			_isError;
		bool			_isWarning;
		std::string		_info;
		std::string		_warning;
		std::string		_error;
};

#endif
