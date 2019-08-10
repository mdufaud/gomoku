/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameState.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 17:31:15 by mdufaud           #+#    #+#             */
/*   Updated: 2016/04/28 17:58:27 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMESTATE_CLASS_HPP
# define GAMESTATE_CLASS_HPP

# include "Board.class.hpp"

class Player;

class GameState
{
	public:
		GameState();
		GameState(GameState const & rhs);
		GameState(Player *p1, Player *p2, Player *pTurn, Board & board);
		~GameState();
	
		GameState &		operator=(GameState const & rhs);

		Player		*_p1;
		Player		*_p2;
		Player		*_pTurn;
		Board		_board;

	private:

	protected:
};
#endif
