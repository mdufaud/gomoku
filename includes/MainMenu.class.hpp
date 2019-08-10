/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MainMenu.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:26:03 by mdufaud           #+#    #+#             */
/*   Updated: 2016/03/15 18:02:32 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAINMENU_CLASS_HPP
# define MAINMENU_CLASS_HPP

# include "AInterface.class.hpp"

class Graph;

class MainMenu: public AInterface
{
	public:
		MainMenu(Graph *graph);
		virtual ~MainMenu(void);
	
		void	recalc_draw();
		void	generateBlocks();
};

#endif
