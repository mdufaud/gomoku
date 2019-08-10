/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextBlock.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:57:27 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/17 19:12:04 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTBLOCK_CLASS_HPP
# define TEXTBLOCK_CLASS_HPP

# include "ABlock.class.hpp"

class	Graph;

class	TextBlock: public ABlock
{
	public:
		TextBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string text);
		TextBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string text,
					SDL_Rect & messageDef);
		TextBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string text,
					std::string background);
		virtual ~TextBlock(void);

		TextBlock		*operator=(TextBlock *rhs);

		bool	action(int x, int y);
		bool	hoovered();
		void	draw();
		void	recalc_draw();

};
#endif
