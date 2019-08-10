/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameInterface.class.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 16:15:03 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/16 16:16:13 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEINTERFACE_CLASS_HPP
# define GAMEINTERFACE_CLASS_HPP

# include "AInterface.class.hpp"

class Graph;
class GameBlock;
class InfoBlock;
class TextBlock;
class MenuBlock;
class LogBlock;

class GameInterface: public AInterface
{
	public:
		GameInterface(Graph *graph);
		virtual ~GameInterface(void);
	
		bool		click(int x, int y);
		void		recalc_draw();
		void		generateBlocks();
		GameBlock	*getGameBlock(void);
		void		startGame(std::string playerOne, std::string playerTwo, bool ia);
		void		setIA(bool easy, bool medium, bool hard);
		void		setWinner(int winner);
		void		unsetWinner(void);

		void		keyLeft(SDL_Event e);
		void		keyRight(SDL_Event e);
		void		keyDown(SDL_Event e);
		void		keyUp(SDL_Event e);
		void		keyDownEvent(SDL_Event e);
		void		keyBackspace(SDL_Event e);

		void		hideWin(void);
		void		loadScenario(int n);

	private:
		GameBlock	*_gameBlock;
		InfoBlock	*_infoBlock;
		TextBlock	*_winBlock;
		MenuBlock	*_retBlock;
		LogBlock	*_logBlock;

		int			_winTimer;
};

#endif
