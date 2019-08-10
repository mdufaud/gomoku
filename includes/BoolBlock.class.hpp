/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOOLBLOCK_CLASS_HPP
# define BOOLBLOCK_CLASS_HPP

# include "ABlock.class.hpp"

class	Graph;

class	BoolBlock: public ABlock
{
	public:
		BoolBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string & text);
		BoolBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string & text,
					std::string background);
		virtual ~BoolBlock(void);

		BoolBlock		*operator=(BoolBlock *rhs);

		bool	action(int x, int y);
		bool	hoovered();
		void	draw();
		void	recalc_draw();

		int		selected(void);
		void	unselect(void);

		bool	getBool(void);
		void	setBool(void);
		void	setBool(bool b);

	private:
		bool			_bool;
		SDL_Rect		_boolRect;
		SDL_Texture		*_boolTexture;

};
#endif
