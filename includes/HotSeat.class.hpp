/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HotSeat.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTSEAT_CLASS_HPP
# define HOTSEAT_CLASS_HPP

# include "AInterface.class.hpp"

class Graph;
class Player;
class InputBlock;

class HotSeat: public AInterface
{
	public:
		HotSeat(Graph *graph);
		virtual ~HotSeat(void);
	
		void		recalc_draw();
		void		generateBlocks();
		void		keyReturn(SDL_Event e);

		bool		click(int x, int y);

	private:
		std::string		p1;
		std::string		p2;
		InputBlock		*_playerOneInput;
		InputBlock		*_playerTwoInput;
};

#endif
