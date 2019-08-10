/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigMenu.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGMENU_CLASS_HPP
# define CONFIGMENU_CLASS_HPP

# include "AInterface.class.hpp"

class Graph;
class BoolBlock;

class ConfigMenu: public AInterface
{
	public:
		ConfigMenu(Graph *graph);
		virtual ~ConfigMenu(void);
	
		void	recalc_draw();
		void	generateBlocks();

		int		getRule();
		bool	click(int x, int y);
		void	keyReturn(SDL_Event e);

	private:
		BoolBlock	*_classicRule;
		BoolBlock	*_alignRule;
};

#endif
