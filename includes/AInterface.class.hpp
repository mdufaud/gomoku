/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AInterface.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 18:28:14 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/17 15:02:02 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AINTERFACE_CLASS_HPP
# define AINTERFACE_CLASS_HPP

# include "gomoku.hpp"
# include "ABlock.class.hpp"
# include <vector>

typedef std::vector<ABlock *>	Blocklist;

class	Graph;

class	AInterface
{
	public:
		AInterface(Graph *graph, int type);
		virtual ~AInterface(void);

		AInterface		*operator=(AInterface *rhs);

		Graph			*getGraph(void) const;
		Blocklist		*getBlocks(void) const;
		ABlock			*getBlockName(std::string name) const;
		ABlock			*getBlockID(int id) const;
		int				getType(void) const;

		virtual bool	click(int x, int y);
		virtual bool	hoover(int x, int y);

		virtual void	draw();
		virtual void	deleteBlocks();

		virtual void	recalc_draw() = 0;
		virtual void	parseKey(SDL_Event e);

		virtual void	keyDownEvent(SDL_Event e);
		virtual void	keyRight(SDL_Event e);
		virtual void	keyDown(SDL_Event e);
		virtual void	keyLeft(SDL_Event e);
		virtual void	keyUp(SDL_Event e);
		virtual void	keyBackspace(SDL_Event e);
		virtual void	keyReturn(SDL_Event e);
		virtual void	resetSelectedBlocks(void);

	protected:
		int					_type;
		int					_selectedBlockID;
		int					_hooveredBlockID;
		Blocklist			*_blocks;
		Graph				*_graph;
};

#endif
