/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MenuBlock.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:34:54 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/17 19:11:58 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENUBLOCK_CLASS_HPP
# define MENUBLOCK_CLASS_HPP

# include "ABlock.class.hpp"

class MenuBlock: public ABlock
{
	public:
		MenuBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string title,
					int interfaceNumChange);
		MenuBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string title,
					SDL_Rect & messageDef,
					int interfaceNumChange);
		MenuBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string title,
					std::string background,
					int interfaceNumChange);
		MenuBlock(Graph *graph,
					SDL_Rect & blockDef,
					std::string title,
					SDL_Rect & messageDef,
					std::string background,
					int interfaceNumChange);
		virtual ~MenuBlock(void);

		MenuBlock		*operator=(MenuBlock *rhs);

		int			getInterfaceNum(void) const;
		bool		action(int x, int y);
		bool		hoovered();
		void		draw();

	private:
		int		_interfaceNumChange;
};

#endif
