/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputBlock.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTBLOCK_CLASS_HPP
# define INPUTBLOCK_CLASS_HPP

# include "ABlock.class.hpp"

class	Graph;

class	InputBlock: public ABlock
{
	public:
		InputBlock(Graph *graph,
					SDL_Rect & blockDef);
		InputBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string background);
		virtual ~InputBlock(void);

		InputBlock		*operator=(InputBlock *rhs);

		bool	action(int x, int y);
		bool	hoovered();
		void	draw();
		void	recalc_draw();

		int		selected(void);
		void	unselect(void);

		void		backDel(void);
		void		addText(std::string text);
		std::string	getInput(void);

	private:
		std::string		_inputText;
		SDL_Rect		_inputRect;
		SDL_Texture		*_inputTextTexture;

};
#endif
