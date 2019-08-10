/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PlayerSelect.class.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2016/04/28 16:56:57 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYERSELECT_CLASS_HPP
# define PLAYERSELECT_CLASS_HPP

# include "AInterface.class.hpp"

class Graph;
class Player;
class InputBlock;
class BoolBlock;

class PlayerSelect: public AInterface
{
	public:
		PlayerSelect(Graph *graph);
		virtual ~PlayerSelect(void);
	
		void		recalc_draw();
		void		generateBlocks();
		void		keyReturn(SDL_Event e);

		bool		click(int x, int y);

	private:
		std::string		p1;
		std::string		p2;
		InputBlock		*_playerOneInput;
		InputBlock		*_playerTwoInput;
		BoolBlock		*_easy;
		BoolBlock		*_medium;
		BoolBlock		*_hard;
};

#endif
